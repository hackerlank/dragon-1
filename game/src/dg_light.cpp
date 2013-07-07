#include "dg_light.h"

GLfloat lightAmbient[] = {0.5, 0.5f, 0.5f, 1.0f}; //������
GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; //�����
GLfloat lightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //��Դλ��

DGLight::DGLight(void)
{

}


DGLight::~DGLight(void)
{
}

void DGLight::start(){
	//��ʼ����Դ
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient); //���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse); //�����
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition); //��Դλ��

	glEnable(GL_LIGHT1);
}

void DGLight::draw(){

}

void DGLight::update(DGContext* ctx){
	DGInput* input = ctx->getInput();

	if (input->getKey('L') && !lp) {
		lp = TRUE;

		light = !light;

		if (!light) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}
	}

	if (!input->getKey('L')) {
		lp = FALSE;
	}
}
