#pragma once
#include <unordered_map>

#include "Core/Core.h"
#include "Node.h"
#include "Connection.h"

namespace Orb
{
	class ORB
	{
	private:
		using size_type = std::size_t;
		using node_traits_type = id_traits<NodeId>;
		using connection_traits_type = id_traits<ConnectionId>;
		
		std::vector<std::pair<Node*, NodeId>> m_Nodes;
		std::vector< std::pair<Connection*, ConnectionId>> m_Connections;
		
		std::unordered_map<NodeId, std::string> m_DebugNames;
	public:
		Node* node(NodeId id) { ORB_ASSERT(valid(id), "trying to get node with invalid id"); return m_Nodes[getPos(id)].first; }
		Node* tryNode(NodeId id) { if (valid(id)) { return m_Nodes[getPos(id)].first; } else { return nullptr; } }
		Connection* connection(ConnectionId id) { ORB_ASSERT(valid(id), "trying to get connection with invalid id"); return m_Connections[getPos(id)].first; }
		Connection* tryConnection(ConnectionId id) { if (valid(id)) { return m_Connections[getPos(id)].first; } else { return nullptr; } }

		NodeRef createNode();
		NodeRef createNode(const std::string& debug);
		ConnectionRef createConnection(NodeRef first, NodeRef second);

		const std::string& debugName(NodeId id);
		


		[[nodiscard]] bool valid(const NodeId entity) const
		{
			const auto pos = size_type(to_integral(entity) & node_traits_type::id_mask);
			return (pos < m_Nodes.size() && m_Nodes[pos].second == entity);
		}
		[[nodiscard]] bool valid(const ConnectionId entity) const
		{
			const auto pos = size_type(to_integral(entity) & connection_traits_type::id_mask);
			return (pos < m_Connections.size() && m_Connections[pos].second == entity);
		}
		
	private:
		template<typename Id>
		size_type getPos(Id id)
		{
			return to_integral(id) & id_traits<Id>::id_mask;
		}
	};
	
}