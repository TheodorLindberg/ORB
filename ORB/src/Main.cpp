//ORB, 20-12-13 14:23
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <string>

#include "ORB.h"

//Serchable object



int main()
{
	std::cout << "ORB" << std::endl;

	Orb::ORB* orb = new Orb::ORB();
	
	std::multimap<std::string, Orb::NodeRef> map;
	
	auto property  = orb->createNode();
	auto value = orb->createNode();
	map.insert({ "value", value });
 
	auto object = orb->createNode();
	map.insert({ "object", object});

	auto objectValue = orb->createNode();
	map.insert({ "theodor", objectValue });

	auto objectValue2 = orb->createNode();
	map.insert({ "hello2", objectValue2 });


	auto object_objectValue = orb->createConnection(object, value);
	object_objectValue->addValue(objectValue);
	object_objectValue->addValue(objectValue2);



	auto con1 = orb->createConnection(objectValue2, value);
	con1->addValue(objectValue);
	
	auto worldObject = orb->createNode();





	map.insert({ "object", object });
	

	std::string cmd;
	std::cout <<  ">";
	while(std::getline(std::cin, cmd))
	{
		std::cout << "ORB: " << cmd << std::endl;
		
		std::cout << ">";

		std::vector<std::string> nodes;
		std::istringstream iss(cmd);
		
		for (std::string s; iss >> s; )
			nodes.push_back(s);


		auto node = map.find(nodes.front())->second;
		for (auto it = nodes.begin() + 1, end = nodes.end() - 1; it != end; ++it)
		{
			node = node->getConnectionTo(map.find(*it)->second)->other(node);
		}

		
		auto valueNode = Orb::NodeRef(Orb::null, orb);

		for (auto it = map.lower_bound(nodes.back()), end = map.upper_bound(nodes.back()); it != end; ++it)
		{
			if(node->getConnectionTo(it->second))
			{
				valueNode = it->second;
			}
		}
		if (valueNode.getId() == Orb::null)
			std::cout << "Error";
		else
		{
			for(Orb::NodeRef val : node->getConnectionTo(valueNode)->getValues())
			{
				for (auto it = map.begin(), end = map.end(); it != end; ++it)
				{
					Orb::NodeRef t = it->second;
					if(it->second == val)
					{
						std::cout << "\t" << it->first << std::endl;
						break;
					}
				}
			}
		}

		
	}

	
	delete orb;
	return 0;
}