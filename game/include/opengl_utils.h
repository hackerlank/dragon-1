#include <stdio.h>
#include "dg_config.h"

#if !defined(OPENGL_UTILS)
#define OPENGL_UTILS


typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    GLubyte* data;
} AUX_RGBImageRec;


inline AUX_RGBImageRec* auxDIBImageLoad(char* fileName){
	FILE* pFile = fopen(fileName, "rb");
	if(!pFile)
        return NULL;

    GLint imgWidth;
    GLint imgHeight;

    fseek(pFile, 0x0012, SEEK_SET);
	fread(&imgWidth, sizeof(imgWidth), 1, pFile);
	fread(&imgHeight, sizeof(imgHeight), 1, pFile);

    GLint pixelLength = imgWidth * 3;
	while(pixelLength % 4 != 0)
		++pixelLength;

	pixelLength *= imgHeight;

	GLubyte* pixelData = (GLubyte*)malloc(pixelLength);
	if(!pixelData)
		return NULL;

	fseek(pFile, 54, SEEK_SET);
	fread(pixelData, pixelLength, 1, pFile);

    fclose(pFile);

	AUX_RGBImageRec* rec = new AUX_RGBImageRec();
	rec->sizeX = imgWidth;
	rec->sizeY = imgHeight;
	rec->data = pixelData;

    return rec;
}

//����λͼ
inline AUX_RGBImageRec* loadBMP(char* fileName) {
	FILE* file = NULL;

	if (!fileName) {
		return NULL;
	}

	file = fopen(fileName, "r");
	if (file) {
		return auxDIBImageLoad(fileName);
	}

	return NULL;
}

inline int loadGLTexture(char* textureFile, GLuint* target) {
	int status = FALSE;

	AUX_RGBImageRec* textureImages[1];
	memset(textureImages, 0, sizeof(void*) * 1);

	if (textureImages[0] = loadBMP(textureFile)) {
		status = TRUE;

		glGenTextures(1, target); //����һ����������

		glBindTexture(GL_TEXTURE_2D, *target); //������󶨵�2D
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImages[0]->sizeX, textureImages[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImages[0]->data);

	}

	if (textureImages[0]) {
		if (textureImages[0]->data) {
			free(textureImages[0]->data);
		}

		free(textureImages[0]);
	}

	return status;
}

//  ���ļ��д�������
inline void dgCreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	AUX_RGBImageRec *pBitmap = NULL;

	if(!strFileName)									// ����޴��ļ�����ֱ�ӷ���
		return;

	pBitmap = auxDIBImageLoad(strFileName);				// װ��λͼ������������

	if(pBitmap == NULL)									// ���װ��λͼʧ�ܣ����˳�
		exit(0);

	// ��������
	glGenTextures(1, &textureArray[textureID]);

	// �������ض����ʽ
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, pBitmap->sizeX, pBitmap->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pBitmap->data);


	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	if (pBitmap)										// �ͷ�λͼռ�õ���Դ
	{
		if (pBitmap->data)
		{
			free(pBitmap->data);
		}

		free(pBitmap);
	}
}

#endif
