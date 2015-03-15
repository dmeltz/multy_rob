/*
 * Nav_class.h
 *
 *  Created on: Mar 8, 2015
 *      Author: dany
 */

#ifndef NAV_CLASS_H_
#define NAV_CLASS_H_

#include <string>

class BobTeam_Nav {
	private :
		std::string Nav_name;
		std::string Rob_name;
		int Nav_WP_permission;
		std::string next_Nav_name;
	public :

		BobTeam_Nav();
		inline BobTeam_Nav(std::string NavName, std::string robName, int NavWPpermission,  std::string NextNavName) {
			Nav_name = NavName;
			Rob_name = robName;
			Nav_WP_permission = NavWPpermission;
			next_Nav_name = NextNavName;
		}

		~BobTeam_Nav();


		inline std::string get_NavName() {
			return Nav_name;
		}

		inline std::string get_RobName() {
			return Rob_name;
		}

		inline int get_NavWPpermission() {
			return Nav_WP_permission;
		}

		inline std::string get_NextNavName() {
			return next_Nav_name;
		}
};





#endif /* NAV_CLASS_H_ */
