#pragma once
#include <map>
#include <string>
#include <iostream>

class CEdge
{
private:
	int From, To; // Store the ID of nodes
	double length;
	int method;
public:
	CEdge();
	CEdge(int f, int t, double l, int m);
	~CEdge();
	bool operator< (const CEdge& e) const;
	int getFrom();
	int getTo();
	double getLength() const;
};

