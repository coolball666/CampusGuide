#include "pch.h"
#include "CEdge.h"

CEdge::CEdge()
{
	From = 0, To = 0;
	length = 0;
	method = 0;
}

CEdge::CEdge(int f, int t, double l, int m)
{
	From = f, To = t;
	length = l;
	method = m;
}

CEdge::~CEdge()
{
}

int CEdge::getFrom()
{
	return From;
}

int CEdge::getTo()
{
	return To;
}

double CEdge::getLength() const
{
	return length;
}

bool CEdge::operator< (const CEdge& e) const
{
	return length < e.getLength();
}