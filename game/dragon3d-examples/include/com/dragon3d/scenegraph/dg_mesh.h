#pragma once

#include "dg_config.h"

#if !defined(DG_MESH)
#define DG_MESH

#include "dg_vector2.h"
#include "dg_vector3.h"
#include "dg_matrix4x4.h"

#include <string>
using std::string;


class DGMesh
{
public:
	DGMesh(void);
	DGMesh(const char* name);
	virtual ~DGMesh(void);

public:
	DGVector3* vertices; //���������
    DGVector2* uv; //������������
    DGVector2* uv2; //����������������
    DGVector3* normals; //����������
	DGuint vertexCount; //���񶥵����


    DGuint* indices; //��������
    DGuint indexCount; //��������

	DGMatrix4x4 matrix; //Transformation matrix for mesh data

private:
	string name;
};

#endif