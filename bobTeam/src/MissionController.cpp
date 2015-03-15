/*
 * MissionControl.cpp

 *
 *  Created on: Mar 8, 2015
 *      Author: dany
 */

#include "ros/ros.h"
#include <string>
#include <vector>

#include "std_msgs/Int8.h"

#include "TeamMission.h"
#include "Nav_class.h"
#include <boost/thread/mutex.hpp>


std::string rob1_name = "bobRob1"; // "UGV1"; //
std::string rob2_name = "bobRob2"; // "UGV2"; //


int rob1_mission_status = 0;
boost::mutex rob1_mission_status_mutex;
void rob1_mission_status_callback(const std_msgs::Int8 mission_status)
{
	rob1_mission_status_mutex.lock();
		rob1_mission_status = mission_status.data;
	rob1_mission_status_mutex.unlock();
}


int rob2_mission_status = 0;
boost::mutex rob2_mission_status_mutex;
void rob2_mission_status_callback(const std_msgs::Int8 mission_status)
{
	rob2_mission_status_mutex.lock();
		rob2_mission_status = mission_status.data;
	rob2_mission_status_mutex.unlock();
}



std::vector<BobTeam_Nav *> * TeamNavVec;
BobTeam_Nav * curent_Nav;


BobTeam_Nav * find_Nav(std::string NavName)
{
	for(BobTeam_Nav * Nav_it : * TeamNavVec)
	{
		if(Nav_it->get_NavName() == NavName)
			{ return(Nav_it);}
	}
	return(0);
}


ros::Publisher rob1_command_pub;
ros::Publisher rob2_command_pub;
void team_controler_callback(const ros::TimerEvent&)
{
	ROS_INFO("I am 1");

	std::cout << "curent_Nav->get_NavName() = " << curent_Nav->get_NavName() << std::endl;
	std::cout << "curent_Nav->get_NextNavName() = " << curent_Nav->get_NextNavName() << std::endl;

	std::cout << "curent_Nav->get_RobName() = " << curent_Nav->get_RobName() << "   rob1_name = " << rob1_name  << std::endl;
	std::cout << "curent_Nav->get_NavWPpermission() = " << curent_Nav->get_NavWPpermission() << "   rob1_mission_status = " << rob1_mission_status  << std::endl;

	std::cout << "curent_Nav->get_RobName() = " << curent_Nav->get_RobName() << "   rob2_name = " << rob2_name  << std::endl;
	std::cout << "curent_Nav->get_NavWPpermission() = " << curent_Nav->get_NavWPpermission() << "   rob2_mission_status = " << rob2_mission_status  << std::endl;

	if ( ((curent_Nav->get_RobName() == rob1_name) && (rob1_mission_status == curent_Nav->get_NavWPpermission() )) ||
         ((curent_Nav->get_RobName() == rob2_name) && (rob2_mission_status == curent_Nav->get_NavWPpermission() )) )
	   {
		ROS_INFO("I am 2");
		curent_Nav = find_Nav(curent_Nav->get_NextNavName());
	   }

	if (curent_Nav==0)
		{
		ROS_INFO("No next team mission");
		}
	else
		{
		std_msgs::Int8 WP_permission_msg;
		WP_permission_msg.data = curent_Nav->get_NavWPpermission();

		if (curent_Nav->get_RobName() == rob1_name )
			{
			rob1_command_pub.publish(WP_permission_msg);
			}
		else if (curent_Nav->get_RobName() == rob2_name )
			{
			rob2_command_pub.publish(WP_permission_msg);
			}
		}
}



int main(int argc, char **argv)
{
/**/
	TeamMission bobTeamMission;
	bobTeamMission.ParsTeamMissionFromFile("/home/dany/multy_rob_ws/src/bobTeam/mission/MissionControl01.xml");
	TeamNavVec = bobTeamMission.get_MissionNavVec();

/*
	TeamNavVec = new std::vector<BobTeam_Nav *>;
	TeamNavVec->push_back(new BobTeam_Nav("Nav01","bobRob1",2,"Nav03"));
	TeamNavVec->push_back(new BobTeam_Nav("Nav03","bobRob2",2,"Nav02"));
	TeamNavVec->push_back(new BobTeam_Nav("Nav02","bobRob1",4,""));
*/
	curent_Nav = TeamNavVec->front();


	ros::init(argc, argv,"MissionControl");

	ros::NodeHandle n;


	ros::Subscriber rob1_mission_status = n.subscribe(rob1_name+"/mission_status", 100, rob1_mission_status_callback);
	ros::Subscriber rob2_mission_status = n.subscribe(rob2_name+"/mission_status", 100, rob2_mission_status_callback);

	ros::Timer team_controler_timer = n.createTimer(ros::Duration(1), team_controler_callback);

	rob1_command_pub = n.advertise<std_msgs::Int8>(rob1_name+"/WP_permission", 100);
	rob2_command_pub = n.advertise<std_msgs::Int8>(rob2_name+"/WP_permission", 100);

	  ros::spin();

	  return 0;


}
