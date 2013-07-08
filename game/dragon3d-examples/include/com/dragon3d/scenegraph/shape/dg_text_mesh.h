#pragma once

#include "dg_game.h"
#include "dg_component.h"
#include "dg_game_object.h"

#if !defined(DG_TEXT_MESH)
#define DG_TEXT_MESH

class DGTextMesh :
	public DGComponent
{
public:
	DGTextMesh(void);

	DGTextMesh(const char *text);
	DGTextMesh(const char *text, DGColor color);

	virtual ~DGTextMesh(void);

public:
	virtual void start();
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

public:
	const char *text;
	DGColor color;

private:
	GLuint base; // �����������ʾ�б�Ŀ�ʼλ��
	GLYPHMETRICSFLOAT gmf[256];	// ��¼256���ַ�����Ϣ
};

#endif
