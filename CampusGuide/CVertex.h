#pragma once
class CVertex
{
private:
	double pos_x, pos_y;
	int scenery_level;
	CString name, Description;
	int type;
public:
	CVertex();
	CVertex(double x, double y, int l, CString s, CString Des, int t);
	~CVertex();
	void DrawTitle(CDC* pDc, COLORREF Col, UINT FontSize);
};

