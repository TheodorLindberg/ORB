#pragma once








class Storage
{
	enum DataType
	{
		Char,
		Short,
		Int,
		Long,
		UnsignedChar,
		UnsignedShort,
		UnsignedInt,
		UnsignedLong,
		Float,
		Double,
		Bool,
	};

	struct StorageType
	{
	public:
		StorageType(DataType type, int count = 1)
			: m_Type(type), m_Count(count)
		{}

		DataType m_Type;
		int m_Count; // -1 represent dynamic array
	};



};

int main2()
{

	{

	}
	
}