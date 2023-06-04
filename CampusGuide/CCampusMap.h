#pragma once
#include "CEdge.h"
#include "CVertex.h"
#include <map>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include "rapidjson/document.h"

struct SEdge
{
	int to;
	double cost;
	int method;
};

struct SNode
{
	double dis;
	int u;
	bool operator> (const SNode& n) const
	{
		return dis > n.dis;
	}
};

class CCampusMap
{
	static const int MaxType = 1024, MaxTrans = 1024;
	static const int MAXV = 1024;
	static const int MAXE = MAXV;
private:
	int NodeCnt, EdgeCnt, TransCnt, TypeCnt;
	std::vector<CVertex> Node;
	std::vector<CEdge> Edge;
	std::map<std::string, int> Trans2Num, Type2Num; // Index start from 0
	std::map<CString, int> Location2Num; // Index start from 0
	std::string Num2Trans[MaxTrans], Num2Type[MaxType];
	std::vector<SEdge> Graph[MAXV];
	double scale;
	void dfs(int now, int end, bool* vis, std::list<int>& p, std::vector<std::list<int>>& sol, int method);
public:
	CCampusMap();
	CCampusMap(rapidjson::Document &document);
	~CCampusMap();
	int getVertexCnt();
	CVertex& getVertex(int i);
	int getEdgeCnt();
	CEdge& getEdge(int i);
	int getScale();
	int getTypeCnt();
	std::string getType(int i);
	std::pair<std::list<int>, double>& ShortestPath(int s, int e, int method);
	std::vector<std::list<int>>& AllPaths(int s, int e, int method);
	std::list<int>& BestPath(int s);
};

