/*
 * TeamMission.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: dany
 */




#include <string>
#include <vector>
#include "tinyxml.h"

#include "TeamMission.h"
#include "Nav_class.h"

#include <iostream>



std::string FindByNameAndGetAtributeValue(TiXmlNode *xml_element, std::string AttrName)
{
	if(xml_element->Type()==1)
	{
		for ( TiXmlAttribute * xml_att = xml_element->ToElement()->FirstAttribute(); xml_att != 0; xml_att = xml_att->Next())
		{
			if ( (xml_att->NameTStr().compare(AttrName)==0) )
			{
				return(xml_att->ValueStr());
			}
		}
	}
	return("");
}


TiXmlNode* GetChildByName(TiXmlNode *xml_element,std::string name)
{
	for (TiXmlNode* pChild = xml_element->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==1 && pChild->ValueStr().compare(name)==0)
				{
			 	 return(pChild);
				}
	}
	return(0);
}


void TeamMission::ParsTeamMissionFromFile(std::string file)
{
	this->file_path = file;  //"/home/dany/multy_rob_ws/src/bobTeam/mission/MissionControl01.xml";

	TiXmlDocument doc(this->file_path);

		if (!doc.LoadFile())
		{
			std::cout << "Failed to load file !!" << std::endl;
		}


		TiXmlNode* xml_OPLscript = doc.FirstChildElement();
/*
		for (TiXmlNode* pChild = doc.FirstChild(); pChild != 0; pChild = pChild->NextSibling())
		{
			if(pChild->Type()==1 && pChild->ValueStr().compare("OPLscript")==0)
					{
				 	 xml_OPLscript = pChild;
					}
		}
*/

		int wp_permission=1;

		TiXmlNode* xml_ThingSentenceSet;
		for (TiXmlNode* pChild = xml_OPLscript->FirstChild() ; pChild != 0; pChild = pChild->NextSibling())
		{
			std::string Nav_name = "0";
			std::string next_Nav_name = "";
			std::string Rob_name = "";

			if(pChild->Type()==1 && pChild->ValueStr().compare("ThingSentenceSet")==0)
					{
					 xml_ThingSentenceSet = pChild;
				   	 if ( FindByNameAndGetAtributeValue(xml_ThingSentenceSet,"transID") == "2" )
				   		{
				   		Nav_name = FindByNameAndGetAtributeValue(xml_ThingSentenceSet,"subjectThingName");

				   		TiXmlNode* xml_ProcessUniDirectionalRelationSentence = GetChildByName(xml_ThingSentenceSet,"ProcessUniDirectionalRelationSentence");
				   		if (xml_ProcessUniDirectionalRelationSentence != 0)
				   		{
				   			TiXmlNode* xml_DestinationName = GetChildByName(xml_ProcessUniDirectionalRelationSentence,"DestinationName");
				   			if (xml_DestinationName != 0)
				   			{
				   				next_Nav_name = xml_DestinationName->FirstChild()->ToText()->ValueStr();
				   			}
				   		}
				   		std::cout << " Nav_name :  " << Nav_name << "            next_Nav_name :  " << next_Nav_name <<std::endl;
				   		}
					}


			 for (TiXmlNode* pChild = xml_OPLscript->FirstChild() ; pChild != 0; pChild = pChild->NextSibling())
			 {
				 if(pChild->Type()==1 && pChild->ValueStr().compare("ThingSentenceSet")==0)
				 					{
				 					 xml_ThingSentenceSet = pChild;
				 				   	 if ( FindByNameAndGetAtributeValue(xml_ThingSentenceSet,"transID") == "0" )
				 				   		{
				 				   		Rob_name = FindByNameAndGetAtributeValue(xml_ThingSentenceSet,"subjectThingName");

								   		TiXmlNode* xml_AgentSentence = GetChildByName(xml_ThingSentenceSet,"AgentSentence");
								   		if (xml_AgentSentence == 0) {continue;}

								   		for (TiXmlNode* pChild = xml_AgentSentence->FirstChild() ; pChild != 0; pChild = pChild->NextSibling())
								   			{
								   			if ( (pChild->Type()==1 && pChild->ValueStr().compare("TriggeredProcessName")==0) &&
								   				 (pChild->FirstChild()->ToText()->ValueStr().compare(Nav_name)==0) )
								   				{
								   				wp_permission = std::stoi(Nav_name.substr(Nav_name.length()-2,2));
								   				mission_nav_vec->push_back(new BobTeam_Nav(Nav_name,Rob_name, wp_permission ,next_Nav_name));
								   				break;
								   				}
								   			}

				 				   		}
				 					}
			 }

		}


		for (BobTeam_Nav * nav : * mission_nav_vec)
		{
			std::cout <<  " name = " << nav->get_NavName() << "    wp = "<< nav->get_NavWPpermission() << "   rob = "<< nav->get_RobName() << "   next = "<< nav->get_NextNavName() << std::endl;
		}

}

