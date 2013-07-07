#include "dg_obj_loader.h"


DGObjLoader::DGObjLoader(void)
{
}


DGObjLoader::~DGObjLoader(void)
{
}


//  ����ĺ����Ĺ����ǽ�obj�ļ�����Ϣ����ָ����ģ����
bool DGObjLoader::importModel(t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};				// ������ʾ������Ϣ

	// �ж��Ƿ���һ���Ϸ���ģ�ͺ��ļ�����
	if(!pModel || !strFileName) return false;

	// ��ֻ����ʽ���ļ��������ļ�ָ��
	m_FilePointer = fopen(strFileName, "r");

	// �ж��ļ�ָ���Ƿ���ȷ
	if(!m_FilePointer) {
		// ����ļ�ָ�벻��ȷ������ʾ������Ϣ
		sprintf(strMessage, "Unable to find or open the file: %s", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// �����ļ���Ϣ
	ReadObjFile(pModel);

	//��ģ���ƹ̶�����ת��������ģ�͵�һ��Z������С�ĵ���ת��
	//��Ҫ�����СZ���꣬Ȼ���ģ�����е�Z���궼ƽ��һ�£�����ת����
		

	// ���㶥��ķ����������ڹ���
	ComputeNormals(pModel);

	// �رմ򿪵��ļ�
	fclose(m_FilePointer);

	return true;
}


//  ����obj�ļ��еĶ���ģ����
void DGObjLoader::ReadObjFile(t3DModel *pModel)
{
	char strLine[255]		= {0};
	char ch					= 0;

	while(!feof(m_FilePointer))
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;

		// ���obj�ļ��еĵ�ǰ�еĵ�һ���ַ�
		ch = fgetc(m_FilePointer);
		switch(ch)
		{
		case 'v':						// �������'v' (���������ݿ����Ƕ���/������/��������)
			
			// �����ǰ������������У���ô���ڽ��������һ����������ڶ�����һ������֮ǰ��
			//  ��Ҫ�������������д�뵽ģ�ͽṹ����
			if(m_bJustReadAFace) 
			{
				// �����������Ϣ���浽ģ�ͽṹ��
				FillInObjectInfo(pModel);
			}

			// ��������Ϣ��Ҫ���ֶ��� ("v")�������� ("vn")���������� ("vt")
			ReadVertexInfo();
			break;

		case 'f':						// �������'f'
			
			//  ���������Ϣ
			ReadFaceInfo();
			break;

		default:

			// �Թ����е�����
			fgets(strLine, 100, m_FilePointer);
			break;
		}
	}

	// ����������Ķ���
	FillInObjectInfo(pModel);
}


//  ����ĺ������붥����Ϣ('v'��ָ���㣬'vt'ָUV����)
void DGObjLoader::ReadVertexInfo()
{
	CVector3 vNewVertex		= {0};
	CVector2 vNewTexCoord	= {0};
	char strLine[255]		= {0};
	char ch = 0;

	// �����һ���ַ����ж϶�����Ƿ񶥵�/������/UV����
	ch = fgetc(m_FilePointer);

	if(ch == ' ')				// ����ǿո�����Ƕ���("v")
	{
		// ���붥�����꣬��ʽ��"v x y z"
		fscanf(m_FilePointer, "%f %f %f", &vNewVertex.x, &vNewVertex.y, &vNewVertex.z);

		// ������������µ����ݣ����ļ�ָ�뵽��һ��
		fgets(strLine, 100, m_FilePointer);

		// ���һ���µĶ��㵽����������
		m_pVertices.push_back(vNewVertex);
	}
	else if(ch == 't')			// �����'t'����ض�����������("vt")
	{
		// �����������꣬��ʽ��"vt u v"
		fscanf(m_FilePointer, "%f %f", &vNewTexCoord.x, &vNewTexCoord.y);

		// ����������µ����ݣ����ļ�ָ��ָ����һ��
		fgets(strLine, 100, m_FilePointer);

		// ���һ���µ��������굽������
		m_pTextureCoords.push_back(vNewTexCoord);
		m_bObjectHasUV = true;
	}
	else						// ��������Ƿ�����("vn")
	{
		// ���������������ķ��������������Թ�
		fgets(strLine, 100, m_FilePointer);
	}
}


//  ����ĺ�����������Ϣ
void DGObjLoader::ReadFaceInfo()
{
	tFace newFace			= {0};
	char strLine[255]		= {0};

	// �ж϶����Ƿ������������
	if(m_bObjectHasUV )
	{
		// �������Ķ��������������������ʽ��"����1/��������1 ����2/��������2 ����3/��������3"
		fscanf(m_FilePointer, "%d/%d %d/%d %d/%d", &newFace.vertIndex[0], &newFace.coordIndex[0],
												   &newFace.vertIndex[1], &newFace.coordIndex[1],
												   &newFace.vertIndex[2], &newFace.coordIndex[2]);				
	}
	else										// ��������������
	{
		// �������Ķ�����������ʽ��"����1 ����2 ����3"
		fscanf(m_FilePointer, "%d %d %d", &newFace.vertIndex[0],
										  &newFace.vertIndex[1],
										  &newFace.vertIndex[2]);				
	}

	// ����������µ����ݣ����ļ�ָ��ָ����һ��
	fgets(strLine, 100, m_FilePointer);
				
	// ���һ�����浽��������
	m_pFaces.push_back(newFace);

	//  ���øղŶ��������
	m_bJustReadAFace = true;
}


//  ����ĺ���������������Ϣд��ģ�ͽṹ����
void DGObjLoader::FillInObjectInfo(t3DModel *pModel)
{
	t3DObject newObject = {0};
	int textureOffset = 0, vertexOffset = 0;
	int i = 0;

	// ģ���ж������������
	pModel->numOfObjects++;

	// ���һ���¶���ģ�͵Ķ���������
	pModel->pObject.push_back(newObject);

	// ��õ�ǰ�����ָ��
	t3DObject *pObject = &(pModel->pObject[pModel->numOfObjects - 1]);

	// ������������������������������������
	pObject->numOfFaces   = m_pFaces.size();
	pObject->numOfVerts   = m_pVertices.size();
	pObject->numTexVertex = m_pTextureCoords.size();

	// �����������
	if(pObject->numOfFaces) 
	{

		// ���䱣����Ĵ洢�ռ�
		pObject->pFaces = new tFace [pObject->numOfFaces];
	}

	// ��������˵�
	if(pObject->numOfVerts) {

		// ���䱣���Ĵ洢�ռ�
		pObject->pVerts = new CVector3 [pObject->numOfVerts];
	}	

	// �����������������
	if(pObject->numTexVertex) {
		pObject->pTexVerts = new CVector2 [pObject->numTexVertex];
		pObject->bHasTexture = true;
	}	

	// �������е���
	for(i = 0; i < pObject->numOfFaces; i++)
	{
		// ������ʱ��������ģ��������
		pObject->pFaces[i] = m_pFaces[i];

		// �ж��Ƿ��Ƕ���ĵ�һ����
		if(i == 0) 
		{
			// �����һ��������1��������Թ���һ������
			if(pObject->pFaces[0].vertIndex[0] != 1) {

				vertexOffset = pObject->pFaces[0].vertIndex[0] - 1;

				// �����������꣬Ҳ����ͬ���Ĳ���
				if(pObject->numTexVertex > 0) {

					// ��ǰ��������ȥ1
					textureOffset = pObject->pFaces[0].coordIndex[0] - 1;
				}
			}					
		}

		for(int j = 0; j < 3; j++)
		{
			//  ����ÿһ�����������뽫���ȥ1
			pObject->pFaces[i].vertIndex[j]  -= 1 + vertexOffset;
			pObject->pFaces[i].coordIndex[j] -= 1 + textureOffset;
		}
	}

	// ���������е����е�
	for(i = 0; i < pObject->numOfVerts; i++)
	{
		// ����ǰ�Ķ������ʱ�����п�����ģ��������
		pObject->pVerts[i] = m_pVertices[i];
	}

	// �������������е���������
	for(i = 0; i < pObject->numTexVertex; i++)
	{
		// ����ǰ�������������ʱ�����п�����ģ��������
		pObject->pTexVerts[i] = m_pTextureCoords[i];
	}

	//  ����OBJ�ļ���û�в��ʣ���˽�materialID����Ϊ-1�������ֶ����ò���
	pObject->materialID = -1;

	//  ������е���ʱ����
	m_pVertices.clear();
	m_pFaces.clear();
	m_pTextureCoords.clear();

	// �������еĲ���ֵΪfalse
	m_bObjectHasUV   = false;
	m_bJustReadAFace = false;
}


//  ����ĺ���Ϊ���������еĶ��������Ĳ���
void DGObjLoader::SetObjectMaterial(t3DModel *pModel, int whichObject, int materialID)
{
	// ȷ��ģ�ͺϷ�
	if(!pModel) return;

	// ȷ������Ϸ�
	if(whichObject >= pModel->numOfObjects) return;

	// �����������ID
	pModel->pObject[whichObject].materialID = materialID;
}


//  ����ĺ�����ģ���ֶ���Ӳ���
void DGObjLoader::AddMaterial(t3DModel *pModel, char *strName, char *strFile, int r, int g, int b)
{
	tMaterialInfo newMaterial = {0};

	// ���ò��ʵ�RGBֵ[0 - RED		1 - GREEN	2 - BLUE]
	newMaterial.color[0] = r; newMaterial.color[1] = g; newMaterial.color[2] = b;

	// ��������ļ����ƣ����俽�������ʽṹ����
	if(strFile) {
		strcpy(newMaterial.strFile, strFile);
	}

	// ������в������ƣ����俽�������ʽṹ����
	if(strName) {
		strcpy(newMaterial.strName, strName);
	}

	//  �����ʼ��뵽ģ��������
	pModel->pMaterials.push_back(newMaterial);

	// ������������
	pModel->numOfMaterials++;
}



//  ����ĺ������ڼ������ķ�����
void DGObjLoader::ComputeNormals(t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// ���ģ����û�ж����򷵻�
	if(pModel->numOfObjects <= 0)
		return;

	// ����ģ�������еĶ���
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		// ��õ�ǰ�Ķ���
		t3DObject *pObject = &(pModel->pObject[index]);

		// ������Ҫ�Ĵ洢�ռ�
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// ���������������
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			// ������ķ�����

			vVector1 = Vector(vPoly[0], vPoly[2]);		// ��ö���ε�ʸ��
			vVector2 = Vector(vPoly[2], vPoly[1]);		// ��ö���εĵڶ���ʸ��

			vNormal  = Cross(vVector1, vVector2);		// �������ʸ���Ĳ��
			pTempNormals[i] = vNormal;					// ����ǹ淶��������
			vNormal  = Normalize(vNormal);				// �淶����õĲ��

			pNormals[i] = vNormal;						// ����������ӵ��������б���
		}

		//  �����󶥵㷨����
		CVector3 vSum = {0.0, 0.0, 0.0};
		CVector3 vZero = vSum;
		int shared=0;
		// �������еĶ���
		for (int i = 0; i < pObject->numOfVerts; i++)			
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// �������е���������
			{												// �жϸõ��Ƿ����������湲��
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum = AddVector(vSum, pTempNormals[j]);
					shared++;								
				}
			}      
			
			pObject->pNormals[i] = DivideVectorByScaler(vSum, float(-shared));

			// �淶�����Ķ��㷨��
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;								
			shared = 0;										
		}
	
		// �ͷŴ洢�ռ䣬��ʼ��һ������
		delete [] pTempNormals;
		delete [] pNormals;
	}
}
