#ifndef RENDER_H
#define RENDER_H

#include "visualsort.h"
#include "util.h"

class CVisualsort;


class CRender
{
	CVisualsort *m_pMain;

public:
	CRender(CVisualsort *pMain) : m_pMain(pMain) { }

	void Color(vec4 color);
	void DoRect(Rect &r);
	void DoRect(Rect &r, vec4 color);
};

#endif /* RENDER_H */
