#pragma once
#include <vector>

#include "Core/Core.h"


namespace Orb
{
	class Node
	{
	public:
		void addConnection(ConnectionRef connection) { m_Connections.push_back(connection); }


		ConnectionRef getConnectionTo(NodeRef to);

		const std::vector<ConnectionRef>& getConnections() const;


		std::vector<NodeRef> getConnectionsConnectedTo(NodeRef node);
		
		std::string debug_name = "";
	private:
		Node(NodeId id)
			: m_Id(id)
		{}

		
		NodeId m_Id;
		std::vector<ConnectionRef> m_Connections;
		friend class ORB;
	};
}