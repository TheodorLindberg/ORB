#pragma once


namespace Orb
{
	namespace IO
	{
		class InputStream
		{
		public:
			virtual int read(void* buffer, int size) = 0;
			virtual int available() = 0;
		};

		class OutputStream
		{
			virtual int write(void* data, int size) = 0;
			virtual void flush() = 0;
		};


		class File
		{
		private:
			Input* m_Input;
			Output* m_Output;
		};

	}
}