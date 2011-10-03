#pragma once

#include "cBlockEntity.h"
#include "FileDefine.h"

#include <string>

namespace Json
{
	class Value;
}

class cSignEntity : public cBlockEntity
{
public:
	cSignEntity(ENUM_BLOCK_ID a_BlockType, int a_X, int a_Y, int a_Z);
	virtual ~cSignEntity();

	void WriteToFile(FILE* a_File);
	bool LoadFromFile(FILE* a_File);

	bool LoadFromJson( const Json::Value& a_Value );
	void SaveToJson( Json::Value& a_Value );

	void SetLines( const std::string & a_Line1, const std::string & a_Line2, const std::string & a_Line3, const std::string & a_Line4 );
	void SetLine( int a_Index, std::string a_Line );

	std::string GetLine( int a_Index );

	virtual void UsedBy( cPlayer & a_Player );
	virtual void SendTo( cClientHandle* a_Client );
private:
	std::string m_Line[4];
};