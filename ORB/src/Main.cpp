//ORB, 20-12-13 14:23
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <string>

#include "ORB.h"

//Serchable object

Orb::ORB* orb = nullptr;

struct Nodes
{

	struct Value
	{
		struct Digits
		{
			Orb::NodeRef _0;
			Orb::NodeRef _1;
			Orb::NodeRef _2;
			Orb::NodeRef _3;
			Orb::NodeRef _4;
			Orb::NodeRef _5;
			Orb::NodeRef _6;
			Orb::NodeRef _7;
			Orb::NodeRef _8;
			Orb::NodeRef _9;

			Orb::NodeRef digit(unsigned int digit) { return *(&_0 + digit); }
		} digits;
		Orb::NodeRef digit;
		
		struct DigitPlace
		{
			static constexpr int max_place = 18;
			static constexpr int min_place = 18;
			
			Orb::NodeRef _n18;//10^n
			Orb::NodeRef _n17;
			Orb::NodeRef _n16;
			Orb::NodeRef _n15;
			Orb::NodeRef _n14;
			Orb::NodeRef _n13;
			Orb::NodeRef _n12;
			Orb::NodeRef _n11;
			Orb::NodeRef _n10;
			Orb::NodeRef _n9;
			Orb::NodeRef _n8;
			Orb::NodeRef _n7;
			Orb::NodeRef _n6;
			Orb::NodeRef _n5;
			Orb::NodeRef _n4;
			Orb::NodeRef _n3;
			Orb::NodeRef _n2;
			Orb::NodeRef _n1;

			Orb::NodeRef _0;
			
			Orb::NodeRef _1; 
			Orb::NodeRef _2;
			Orb::NodeRef _3;
			Orb::NodeRef _4;
			Orb::NodeRef _5;
			Orb::NodeRef _6;
			Orb::NodeRef _7;
			Orb::NodeRef _8;
			Orb::NodeRef _9;
			Orb::NodeRef _10;
			Orb::NodeRef _11;
			Orb::NodeRef _12;
			Orb::NodeRef _13;
			Orb::NodeRef _14;
			Orb::NodeRef _15;
			Orb::NodeRef _16;
			Orb::NodeRef _17;
			Orb::NodeRef _18;
			
			Orb::NodeRef place(int place) { return *(&_0 + place); }
			
		} digit_positions;
		Orb::NodeRef digit_position;

		Orb::NodeRef property;
		Orb::NodeRef value;

		
		Orb::NodeRef value_number;
		Orb::NodeRef value_text;
	} value;
} nodes;



Orb::NodeRef createNumberValue(const std::string& strValue)
{
	//Index of .
	std::size_t find = strValue.find('.');

	std::string data = strValue;
	
	const int digit_place_start = (find == std::string::npos) ? data.size() - 1  : find - 1;

	if(find != std::string::npos)
		data.erase(find, 1);

	auto value = orb->createNode();

	for(int i = 0; i < data.size(); i++)
	{
		int position = digit_place_start - i;
		char c = data[i];
		int digit = c - '0';

		auto digit_node = nodes.value.digits.digit(digit);
		auto position_node = nodes.value.digit_positions.place(position);

		auto con = orb->createConnection(value, position_node);
		con->addValue(digit_node);
	}
	orb->createConnection(value, nodes.value.value_number);
	return value;
}

std::string readNumberValue(Orb::NodeRef value)
{
	auto digitNodes = value->getConnectionsConnectedTo(nodes.value.digit_position);
	
	double ret = 0;
	for(auto digit : digitNodes)
	{
		auto d = orb->debugName(digit);
		d.erase(d.begin(), d.begin() + d.find_last_of('_') + 1);
		int num = std::stoi(d.c_str());

		double position_power = std::pow(10, num);

		auto digit_node = value->getConnectionTo(digit)->getValues().front();

		auto digit_debug = orb->debugName(digit_node);
		digit_debug.erase(digit_debug.begin(), digit_debug.begin() + digit_debug.find_last_of('_') + 1);
		double digit_value = std::stod(digit_debug);
		ret += digit_value * position_power;
		
	}
	return std::to_string(ret);
}

int main()
{
	std::cout << "ORB" << std::endl;
	
	orb = new Orb::ORB();
	

	{
		nodes.value.value = orb->createNode("value");
		nodes.value.value_number = orb->createNode("value_number");
		nodes.value.value_text= orb->createNode("value_text");
		
		nodes.value.property = orb->createNode("property");
		
		nodes.value.digit = orb->createNode("digit");
		nodes.value.digit_position = orb->createNode("digit_position");
		
		for(int i = 0; i < 10; i++)
		{
			(&nodes.value.digits._0)[i] = orb->createNode(std::string("digit_") + std::to_string(i));
			orb->createConnection((&nodes.value.digits._0)[i], nodes.value.digit);
		}
		
		for (int i = 0; i < 18 + 18 +1; i++)
		{
			(&nodes.value.digit_positions._n18)[i] = orb->createNode(std::string("digit_position_") + std::to_string(i - 18));
			orb->createConnection((&nodes.value.digit_positions._n18)[i], nodes.value.digit_position);
		}
	}
	std::string str;
	while(std::getline(std::cin, str))
	{
		auto val = createNumberValue(str);
		std::cout << readNumberValue(val) << std::endl;

	}
	
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