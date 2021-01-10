#pragma once
#include <type_traits>
#include <cstdint>

namespace Orb
{
	class Node;
	class Connection;
	class ORB;

	using id_type = std::uint32_t;

	enum class NodeId : id_type{};
	enum class ConnectionId : id_type{};


	Node* getORBReference(ORB* orb, NodeId node);
	Connection* getORBReference(ORB* orb, ConnectionId node);



	template<typename, typename = void>
	struct id_traits;


	template<typename Type>
	struct id_traits<Type, std::enable_if_t<std::is_enum_v<Type>>>
		: id_traits<std::underlying_type_t<Type>>
	{

		using underlaying_type = Type;
	};

	template<>
	struct id_traits<std::uint32_t> {
		using id_type = std::uint32_t;
		using version_type = std::uint16_t;

		static constexpr id_type id_mask = 0xFFFFF;
		static constexpr id_type version_mask = 0xFFF;
		static constexpr std::size_t id_shift = 20u;
	};
	template<>
	struct id_traits<std::uint64_t> {
		using id_type = std::uint32_t;
		using version_type = std::uint32_t;

		static constexpr id_type id_mask = 0xFFFFFFFF;
		static constexpr id_type version_mask = 0xFFFFFFFF;
		static constexpr std::size_t id_shift = 32u;
	};

	template<typename Id>
	[[nodiscard]] constexpr auto to_integral(const Id entity) {
		return static_cast<typename id_traits<Id>::id_type>(entity);
	}

	struct null_t {
		template<typename Id>
		[[nodiscard]] constexpr operator Id() const {
			return Id{ id_traits<Id>::id_mask };
		}

		[[nodiscard]] constexpr bool operator==(const null_t&) const {
			return true;
		}
		[[nodiscard]] constexpr bool operator!=(const null_t&) const {
			return false;
		}

		template<typename Id>
		[[nodiscard]] constexpr bool operator==(const Id& id) const {
			return (to_integral(id) & id_traits<Id>::id_mask) == to_integral(static_cast<Id>(*this));
		}

		template<typename Id>
		[[nodiscard]] constexpr bool operator!=(const Id& id) const {
			return !(id == *this);
		}
	};


	template<typename Id>
	[[nodiscard]] constexpr bool operator==(const Id& id, const null_t& other) {
		return other.operator==(id);
	}

	template<typename Id>
	[[nodiscard]] constexpr bool operator!=(const Id& id, const null_t& other) {
		return !(other == id);
	}
	inline constexpr null_t null{};
	
	template<typename T, typename Id>
	class Ref
	{
	private:
		Id m_Id;
		ORB* m_ORB;
		T* ref;
	public:
		using ref_type = Ref<T, Id>;
		Ref()
			:m_Id(null), m_ORB(nullptr)
		{}
		Ref(Id id, ORB* orb)
			: m_Id(id), m_ORB(orb)
		{
			if(m_Id != null)
				ref = getRef();
		}
		
		operator Id() const { return m_Id; }
		operator T* () const { return getRef(); }

		ORB* getORB() const { return m_ORB; }
		Id getId() const { return m_Id; }
		T* getRef() const { return getORBReference(m_ORB, m_Id); }

		T* operator->() { return getRef(); }

		bool valid() { return m_Id != null && m_ORB != nullptr; }
		operator bool() { return valid(); }

		bool operator==(ref_type& rhs) const
		{
			return m_Id == rhs.m_Id && m_ORB == rhs.m_ORB;
		}
		bool operator!=(ref_type& rhs) const
		{
			return !(*this == rhs);
		}
	};

	

	using NodeRef = Ref<Node, NodeId>;
	using ConnectionRef = Ref<Connection, ConnectionId>;

}