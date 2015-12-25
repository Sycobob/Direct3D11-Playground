#include "stdafx.h"

#include <fstream>
#include <memory>

#include "Utility.h"

using namespace std;

namespace Utility
{
	bool LoadFile(const wstring fileName, unique_ptr<char[]> &data, SIZE_T &dataSize)
	{
		ifstream inFile(fileName, ios::binary | ios::ate);
		if ( !inFile.is_open() )
		{
			LOG_ERROR(L"Failed to open file: " + fileName);
			return false;
		}

		dataSize = (SIZE_T) inFile.tellg();
		data = make_unique<char[]>(dataSize);

		inFile.seekg(0);
		inFile.read(data.get(), dataSize);

		if ( inFile.bad() )
		{
			dataSize = 0;
			data = nullptr;

			LOG_ERROR(L"Failed to read file: " + fileName);
			return false;
		}

		return true;
	}
}