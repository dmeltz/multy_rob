/*
 * TeamMission.h
 *
 *  Created on: Mar 9, 2015
 *      Author: dany
 */

#ifndef TEAMMISSION_H_
#define TEAMMISSION_H_

#include <vector>
#include <string>
#include "Nav_class.h"

class TeamMission{

private:
	std::string file_path;
	std::vector<BobTeam_Nav *> * mission_nav_vec;

public:
	inline TeamMission() {
		 mission_nav_vec = new std::vector<BobTeam_Nav *>;
		};

	inline std::vector<BobTeam_Nav *> * get_MissionNavVec() {
		 return(mission_nav_vec);
		};


	void ParsTeamMissionFromFile(std::string file);
};







#endif /* TEAMMISSION_H_ */
