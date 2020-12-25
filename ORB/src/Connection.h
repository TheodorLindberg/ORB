#pragma once
#include "Core/Core.h"

namespace Orb
{
	class Connection
	{
	public:
		~Connection() = default;

		NodeRef addValue(NodeRef val) { m_Values.push_back(val); return val; }

		bool connected(NodeRef node) const { if(m_First == node || m_Second == node) { return true;}}
		NodeRef other(NodeRef other) const { if (m_First == other) return m_Second; else if (m_Second == other) return m_First; else return NodeRef(null, m_First.getORB()); }

		const std::vector<NodeRef>& getValues() const { return m_Values; }
		
	private:
		Connection(NodeRef first, NodeRef second, ConnectionId id)
			: m_First(first), m_Second(second), m_Id(id)
		{}

		
		NodeRef m_First;
		NodeRef m_Second;
		ConnectionId m_Id;
		//The values this connection represents
		std::vector<NodeRef> m_Values;
		friend class ORB;
	};
}
