#pragma once
#include <map>
#include <string>
#include <iostream>

class CEdge
{
private:
	int From, To;
	double length;
	int method;
public:
	CEdge();
	CEdge(int f, int t, double l, int m);
	~CEdge();
	bool operator< (const CEdge& e) const;
};

