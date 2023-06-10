#include "pch.h"
#include "CCampusMap.h"

void UTF8toANSI(CString& strUTF8)
{
	//获取转换为多字节后需要的缓冲区大小，创建多字节缓冲区
	UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8, -1, NULL, NULL);
	WCHAR* wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;

	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR* szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;
	strUTF8 = szBuffer;
	//清理内存
	delete[]szBuffer;
	delete[]wszBuffer;
}

CCampusMap::CCampusMap()
{
	EdgeCnt = 0, NodeCnt = 0, scale = 1.0, TransCnt = 0, TypeCnt = 0;
}

CCampusMap::CCampusMap(rapidjson::Document &document)
{
	//TODO: Don't forget to set scale ratio of graph
	int cntLocation = 0, cntEdge = 0;
	double min_x = 0.0, min_y = 0.0, max_x = 800.0, max_y = 800.0;

	// Handle of Header
	TransCnt = document[0]["Transports"].Size();
	for (int i = 0; i < TransCnt; i++)
	{
		std::string trans = document[0]["Transports"][i].GetString();
		Trans2Num[trans] = i;
		Num2Trans[i] = trans;
	}
	TypeCnt = document[0]["LocationType"].Size();
	for (int i = 0; i < TypeCnt; i++)
	{
		std::string type = document[0]["LocationType"][i].GetString();
		Type2Num[type] = i;
		Num2Type[i] = type;
	}

	// Handle of Vertexs
	for (int i = 1; i < document.Size(); i++)
	{
		CString name(document[i]["location"].GetString());
		UTF8toANSI(name);
		if (Location2Num[name] == 0)
			Location2Num[name] = cntLocation;
		cntLocation++;
		CString description(document[i]["description"].GetString());
		UTF8toANSI(description);
		int l = document[i]["level"].GetInt();
		int t[64];
		for (int j = 0; j < document[i]["type"].Size(); j++)
		{
			t[j] = Type2Num[document[i]["type"][j].GetString()];
		}
		double pos_x = document[i]["pos"][0].GetDouble(), pos_y = document[i]["pos"][1].GetDouble();
		min_x = min(min_x, pos_x), min_y = min(min_y, pos_y), max_x = max(max_x, pos_x), max_y = max(max_y, pos_y);
		CVertex Tmp(pos_x, pos_y, l, name, description, t, document[i]["type"].Size());
		Node.emplace_back(Tmp);
	}
	NodeCnt = cntLocation;

	// Handle of Edges
	for (int i = 1; i < document.Size(); i++)
	{
		CString from(document[i]["location"].GetString());
		UTF8toANSI(from);
		int f = Location2Num[from];
		for (int j = 0; j < document[i]["edges"].Size(); j++)
		{
			CString to(document[i]["edges"][j]["to"].GetString());
			UTF8toANSI(to);
			int t = Location2Num[to];
			for (int k = 0; k < document[i]["edges"][j]["method"].Size(); k++)
			{
				cntEdge++;
				std::string k_trans = document[i]["edges"][j]["method"][k].GetString();
				double len = document[i]["edges"][j]["length"][k].GetDouble();
				CEdge Tmp(f, t, len, Trans2Num[k_trans]);
				Edge.emplace_back(Tmp);
				Graph[i - 1].emplace_back(SEdge{ t, len, Trans2Num[k_trans] });
			}
		}
	}
	EdgeCnt = cntEdge;

	// Handle of scale
	scale = 770.0 / (max(max_x - min_x, max_y - min_y));
	for (int i = 0; i < NodeCnt; i++)
		Node[i].changeXY(-min_x, -min_y);
}

CCampusMap::~CCampusMap()
{
}

int CCampusMap::getVertexCnt()
{
	return NodeCnt;
}

CVertex& CCampusMap::getVertex(int i)
{
	return Node[i];
}

int CCampusMap::getEdgeCnt()
{
	return EdgeCnt;
}

CEdge& CCampusMap::getEdge(int i)
{
	return Edge[i];
}

double CCampusMap::getScale()
{
	return scale;
}

int CCampusMap::getTypeCnt()
{
	return TypeCnt;
}

int CCampusMap::getIDFromLoc(CString Loc)
{
	return Location2Num[Loc];
}

int CCampusMap::getIDFromeType(std::string tp)
{
	return Type2Num[tp];
}

int CCampusMap::getTransCnt()
{
	return TransCnt;
}

std::string CCampusMap::getTransFromID(int id)
{
	return Num2Trans[id];
}

std::string CCampusMap::getType(int i)
{
	return Num2Type[i];
}

std::pair<std::list<int>, double> CCampusMap::ShortestPath(int s, int e, int method)
{
	double dis[MAXV];
	bool vis[MAXV];
	int pre[MAXV];
	std::priority_queue<SNode, std::vector<SNode>, std::greater<SNode> > pq;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < NodeCnt; i++)
		pre[i] = i, dis[i] = 1000000009.0;
	dis[s] = 0.0;
	pq.push(SNode{ 0.0, s });
	while (!pq.empty())
	{
		int u = pq.top().u;
		pq.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto e : Graph[u])
		{
			if (e.method != method) continue;
			int v = e.to;
			double w = e.cost;
			if (dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				pq.push(SNode{ dis[v], v });
				pre[v] = u;
			}
		}
	}
	std::list<int> path;
	double ans = dis[e];
	path.emplace_front(e);
	for (; pre[e] != e; e = pre[e])
		path.emplace_front(pre[e]);
	return std::make_pair(path, ans);
}

std::vector<std::list<int>> CCampusMap::AllPaths(int s, int e, int method)
{
	std::vector<std::list<int>> sol;
	bool vis[MAXV];
	memset(vis, 0, sizeof(vis));
	std::list<int> path_list;
	vis[s] = 1;
	dfs(s, e, vis, path_list, sol, method);
	return sol;
}

void CCampusMap::dfs(int now, int end, bool* vis, std::list<int>& p, std::vector<std::list<int>>& sol, int method)
{
	p.emplace_back(now);
	if (now == end)
	{
		sol.emplace_back(p);
		p.pop_back();
		return;
	}
	for (auto e : Graph[now])
	{
		if (e.method != method) continue;
		int t = e.to;
		if (vis[t]) continue;
		vis[t] = 1;
		dfs(t, end, vis, p, sol, method);
		vis[t] = 0;
	}
	p.pop_back();
}

std::list<int> CCampusMap::BestPath(int s)
{
	int now = s;
	int iter = 0;
	std::list<int> sol;
	bool vis[MAXV];
	memset(vis, 0, sizeof(vis));
	int visCnt = 1;
	sol.emplace_back(s);
	vis[s] = true;
	auto it = sol.rbegin();
	while (visCnt < NodeCnt)
	{
		iter++;
		bool isUpdate = false;
		for (int i = 0; i < Graph[now].size(); i++)
		{
			SEdge e = Graph[now][i];
			CString out;
			out.Format("%d", now);
			// AfxMessageBox(out);
			int tmp = e.to;
			if (!vis[tmp])
			{
				vis[tmp] = true;
				sol.emplace_back(tmp);
				it = sol.rbegin();
				visCnt++;
				isUpdate = true;
				break;
			}
		}
		if (!isUpdate)
		{
			now = *(++it);
			sol.emplace_back(now);
		}
		else
		{
			now = *it;
		}
		if (iter > 1e7)
			break;
		/*
		bool isAllVis = true;
		for (int i = 0; i < NodeCnt; i++)
		{
			if (!vis[i]) isAllVis = false;
		}
		if (isAllVis)
		{
			sol = std::list<int>();
			break;
		}
		*/
	}
	return sol;
}

std::list<int> CCampusMap::getAdjacent(int s)
{
	// TODO: 在此处插入 return 语句
	std::list<int> adj;
	int pre = Graph[s].begin()->to;
	adj.emplace_back(pre);
	for (auto e : Graph[s])
		if (e.to != pre)
		{
			adj.emplace_back(e.to);
			pre = e.to;
		}
	return adj;
}

std::list<int> CCampusMap::getSameType(int s)
{
	std::list<int> collection;
	for (int i = 0; i < NodeCnt; i++)
	{
		if (Node[i].isType(s))
			collection.emplace_back(i);
	}
	return collection;
}
