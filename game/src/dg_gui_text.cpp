#include <stdio.h>
#include "dg_gui_text.h"

DGGUIText::DGGUIText() {
	base = 0;
}


DGGUIText::~DGGUIText(void)
{
}


void DGGUIText::init(DGScreen* screen){
	this->screen = screen;

	base = 0;

	HFONT	newFont;												// ���Ա����µ��������
	HFONT	oldFont;												// ���Ա���ԭ�������

	base = glGenLists(256);											// �洢256���ַ�

	newFont = CreateFont(-14,									// ����ĸ߶�
							0,										// ����Ŀ��
							0,										// ��ת�ĽǶ�
							0,										// ��λ�Ƕ�
							FW_THIN,								// ����Ĵ�ϸ
							FALSE,									// б��?
							FALSE,									// �»���?
							FALSE,									// ɾ����?
							ANSI_CHARSET,							// �ַ���
							OUT_TT_PRECIS,							// �������
							CLIP_DEFAULT_PRECIS,					// �ü�����
							ANTIALIASED_QUALITY,					// �������
							FF_DONTCARE|DEFAULT_PITCH,				// ����������
							"Courier New");							// ��������

	oldFont = (HFONT)SelectObject(wglGetCurrentDC(), newFont); 		// ѡ���豸������
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, base);				// ����256���ַ�
	SelectObject(wglGetCurrentDC(), oldFont);							// �ָ��豸������
	DeleteObject(newFont);											// ɾ��������
}

void DGGUIText::print(GLint x, GLint y, const char *fmt, ...){
	va_list		ap;

	va_start(ap, fmt);												// �����ַ��������ұ���
	    this->print(x, y, DGColor::white, fmt, ap);
	va_end(ap);
}

void DGGUIText::print(GLint x, GLint y, DGColor color, const char *fmt, ...) {
	char		text[256];											// ���Ա����ʽ������ַ���
	va_list		ap;													// ָ������б��ָ��

	if (fmt == NULL)												// û�п�������ַ���
		return;														// ����

	va_start(ap, fmt);												// �����ַ��������ұ���
	    vsprintf(text, fmt, ap);									// ������ת��Ϊ��ʾ������
	va_end(ap);														// ���������text��

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glOrtho(0, 640, 0, 480, -1, 1);
	glOrtho(0, screen->getWidth(), 0, screen->getHeight(), -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslated(x, y, 0);

	glRasterPos3f(-0.54f, 0.39f, -1.0f);
	glColor3f(color.r, color.g, color.b);

	glPushAttrib(GL_LIST_BIT);										// ��ʾ��״̬��ջ
	glListBase(base);												// ��ʾ��ƫ����
	glCallLists((int)strlen(text), GL_UNSIGNED_BYTE, text);			// �����ַ���
	glPopAttrib();													// ��ʾ��״̬��ջ

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void DGGUIText::destroy(){
	glDeleteLists(base, 256);
}

