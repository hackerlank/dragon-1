#pragma once

#include "dg_transform.h"
#include "dg_component.h"

#include <vector>
using std::vector;

#if !defined(DG_GAME_OBJECT)
#define DG_GAME_OBJECT

class DGGameObject
{
protected:
	//����
	typedef struct tagVERTEX {
		DGfloat x, y, z;
		DGfloat u, v;
	} VERTEX;

	//������
	typedef struct tagTRIANGLE {
		VERTEX vertexs[3];
	} TRIANGLE;

	//����
	typedef struct tagSECTOR {
		int numTriangles;
		TRIANGLE* triangle;
	} SECTOR;

public:
	DGGameObject(void);

	DGGameObject(DGTransform* transform);

	virtual ~DGGameObject(void);

public:
	virtual void init(DGContext* ctx);
	virtual void update(DGContext* ctx);
	virtual void draw(DGContext* ctx);
	virtual void destroy();

	virtual void addChild(DGGameObject* child);
	virtual void addComponent(DGComponent* component);

	virtual DGComponent* findComponent(const char* name);


public:
	DGTransform* transform; //λ�á���������

private:
	vector<DGGameObject*> children; //���Ӷ���
	vector<DGComponent*> components; //���
};

#endif