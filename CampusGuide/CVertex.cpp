#include "pch.h"
#include "CVertex.h"

CVertex::CVertex(double x, double y, int l, CString s, CString Des, int *t, int t_cnt)
{
	pos_x = x;
	pos_y = y;
	scenery_level = l;
	name = s;
	Description = Des;
	for (int i = 0; i < t_cnt; i++)
	{
		type.insert(t[i]);
	}
	//TODO: Construction
}

CVertex::CVertex()
{
	pos_x = 0.0;
	pos_y = 0.0;
	scenery_level = 0;
	name = "";
	Description = "";
	type = std::set<int>();
}

CVertex::~CVertex()
{
	//TODO Deconstruction
}


double CVertex::getX()
{
	return pos_x;
}

double CVertex::getY()
{
	return pos_y;
}

CString CVertex::getName()
{
	return name;
}

void CVertex::changeXY(double dx, double dy)
{
	pos_x += dx;
	pos_y += dy;
}

CString CVertex::getDes()
{
	return Description;
}

bool CVertex::isType(int id)
{
	return type.find(id) != type.end();
}
