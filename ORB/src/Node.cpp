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
