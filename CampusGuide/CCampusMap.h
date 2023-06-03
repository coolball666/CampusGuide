#pragma once
#include "CEdge.h"
#include "CVertex.h"
#include <map>
#include <string>
#include "rapidjson/document.h"
class CCampusMap
{
	static const int MaxType = 1024, MaxTrans = 1024;
	static const int MAXV = 1024;
	static const int MAXE = MAXV;
private:
	int NodeCnt, EdgeCnt;
	CVertex Node[MAXV];
	CEdge Edge[MAXE];
	std::map<std::string, int> Trans2Num, Type2Num;
	std::map<CString, int> Location2Num;
	std::string Num2Trans[MaxTrans], Num2Type[MaxType];
public:
	CCampusMap();
	CCampusMap(rapidjson::Document &document);
	~CCampusMap();
	void DrawEdge(CDC* pDC, CEdge& e, COLORREF Col);
};

