#pragma once

#include "dg_config.h"
#include "dg_model.h"
#include "dg_model_loader.h"

#include <vector>
using std::vector;

#if !defined(DG_OBJ_LOADER)
#define DG_OBJ_LOADER

class DGObjLoader :public DGModelLoader
{
public:
	DGObjLoader(void);
	virtual ~DGObjLoader(void);

public:
	//  ��obj�ļ��е���Ϣ���뵽ģ����
	virtual bool importModel(t3DModel *pModel, char *strFileName);

private:
	// ���������ImportObj()�н����øú���
	void ReadObjFile(t3DModel *pModel);

	// ���붥����Ϣ����ReadObjFile()�е��øú���
	void ReadVertexInfo();

	// ��������Ϣ����ReadObjFile()�е��øú���
	void ReadFaceInfo();

	// �������Ϣ�Ķ���֮����øú���
	void FillInObjectInfo(t3DModel *pModel);

	// ���㶥��ķ�����
	void ComputeNormals(t3DModel *pModel);

	// ������obj�ļ���û������/�������ƣ�ֻ���ֶ�����
	// materialID����ģ�Ͳ����б��е�������
	void SetObjectMaterial(t3DModel *pModel, int whichObject, int materialID);

	//  ��Ӳ���
	void AddMaterial(t3DModel *pModel, char *strName, char *strFile, 
					 int r = 255,      int g = 255,   int b = 255);

private:

	// ��Ҫ������ļ�ָ��
	FILE *m_FilePointer;

	// ��������
	vector<CVector3>  m_pVertices;

	// ������
	vector<tFace> m_pFaces;

	// UV��������
	vector<CVector2>  m_pTextureCoords;

	// ��ǰ�����Ƿ������������
	bool m_bObjectHasUV;

	// ��ǰ����Ķ����Ƿ�����
	bool m_bJustReadAFace;
};

#endif