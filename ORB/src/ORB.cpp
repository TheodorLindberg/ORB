#include "ORB.h"
namespace Orb
{
	
Orb::Node* getORBReference(ORB* orb, NodeId node)
{
	return orb->node(node);
}
Connection* getORBReference(ORB* orb, ConnectionId node)
{
	return orb->connection(node);
}

NodeRef ORB::createNode()
{
	ORB_ASSERT(static_cast<typename node_traits_type::id_type>(m_Nodes.size()) < node_traits_type::id_mask);
	const NodeId id = NodeId{ static_cast<typename node_traits_type::id_type>(m_Nodes.size()) };
	Node* node = new Node(id);
	m_Nodes.emplace_back(node, id);
	return NodeRef(id, this);
}

NodeRef ORB::createNode(const std::string& debug)
{
	auto node = createNode();
	m_DebugNames[node->m_Id] = debug;
	node->debug_name = debug;
	return node;
}

ConnectionRef ORB::createConnection(NodeRef first, NodeRef second)
{
	ORB_ASSERT(static_cast<typename connection_traits_type::id_type>(m_Connections.size()) < connection_traits_type::id_mask);
	const ConnectionId id = ConnectionId{ static_cast<typename connection_traits_type::id_type>(m_Connections.size()) };
	
	Connection* connection = new Connection(first,second,id);
	
	m_Connections.emplace_back(connection, id );

	first->addConnection(ConnectionRef(id, this));
	second->addConnection(ConnectionRef(id, this));
	
	return ConnectionRef(id, this);
}

const std::string& ORB::debugName(NodeId id)
{
	static std::string null = "";
	auto it = m_DebugNames.find(id);
	if (it != m_DebugNames.end())
		return it->second;
	else
		return null;
}
}
