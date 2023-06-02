#pragma once
class CVertex
{
private:
	double pos_x, pos_y;
	CString name;
	double radius = 1.0;
public:
	CVertex(double x, double y, CString s);
	~CVertex();
	void SetRadius(double new_r);
};

