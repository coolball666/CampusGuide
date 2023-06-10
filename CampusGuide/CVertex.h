#pragma once
#include <set>
class CVertex
{
private:
	double pos_x, pos_y;
	int scenery_level;
	CString name, Description;
	std::set<int> type;
public:
	CVertex();
	CVertex(double x, double y, int l, CString s, CString Des, int* t, int t_cnt);
	~CVertex();
	double getX();
	double getY();
	CString getName();
	CString getDes();
	void changeXY(double dx, double dy);
	bool isType(int id);
	int getLevel();
};

