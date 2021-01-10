#include "Node.h"
#include "Connection.h"

Orb::ConnectionRef Orb::Node::getConnectionTo(NodeRef to)
{
	for (auto& connection : m_Connections)
	{
		if (connection->connected(to))
		{
			return connection;
		}
	}
	return Orb::ConnectionRef(null, to.getORB());
}

std::vector<Orb::NodeRef> Orb::Node::getConnectionsConnectedTo(NodeRef node)
{
	std::vector<NodeRef> ret;
	for(auto con : m_Connections)
	{
		auto connection = con->other({ m_Id, node.getORB() })->getConnectionTo(node);
		
		if (connection)
			ret.push_back(connection->other(node));
	}
	return ret;
}
