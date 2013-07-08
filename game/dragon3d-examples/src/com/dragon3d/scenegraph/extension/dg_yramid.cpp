#include "dg_yramid.h"
#include "dg_exception.h"

DGYramid::DGYramid(void)
{
}


DGYramid::~DGYramid(void)
{
}


void DGYramid::start(){
	//��������
	if (!loadGLTexture("Assets/Data/texture_desktop.bmp", &texture[0])) {
		throw new DGException("yramid texture load faild!");
	}

	//��ʼ�����
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	rotTriangle = 0.0f;

	blend = FALSE;
	bp = FALSE;

    this->transform->position = DGVector3(0, -2.0f, 2.0f);

	DGGameObject::start();
}

void DGYramid::draw(DGContext* ctx){
	glTranslatef(0.0f, 0.0f, -6.0f);

	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(rotTriangle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);

		//��1
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);


		//��2
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);


		//��3
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		//��4
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	rotTriangle+=0.05f;
}

void DGYramid::update(DGContext* ctx){
	DGInput* input = ctx->getInput();

	if (input->getKey('B') && !bp)				// B ��������bpΪ FALSEô?
	{
		bp=TRUE;				// ���ǣ� bp ��Ϊ TRUE
		blend = !blend;				// �л����ѡ��� TRUE / FALSE

		if(blend)				// ��ϴ���ô?
		{
			glEnable(GL_BLEND);		// �򿪻��
			glDisable(GL_DEPTH_TEST);	// �ر���Ȳ���
		}
		else					// ����
		{
			glDisable(GL_BLEND);		// �رջ��
			glEnable(GL_DEPTH_TEST);	// ����Ȳ���
		}
	}

	if (!input->getKey('B'))		//  B ���ɿ���ô?
	{
		bp=FALSE;				// ���ǣ� bp��Ϊ FALSE
	}
}
