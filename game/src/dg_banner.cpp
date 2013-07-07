#include "dg_banner.h"
#include <math.h>

DGBanner::DGBanner(void)
{
}


DGBanner::~DGBanner(void)
{
}

void DGBanner::start(){
	wiggle_count = 0;

	//��������
	if (!loadGLTexture("Assets/Textures/Tim.bmp", &texture[0])) {
		throw new DGException("yramid texture load faild!");
	}

	glPolygonMode(GL_BACK, GL_FILL); // �������ȫ���
	glPolygonMode(GL_FRONT, GL_LINE); // ǰ����ʹ����������

	//��ʼ�������ϵĵ�
	for (int x=0; x<45; x++) {
		for (int y=0; y<45; y++) {
			this->points[x][y].x = x/5.0f - 4.5f;
			this->points[x][y].y = y/5.0f - 4.5f;
			this->points[x][y].z = sin((((x/5.0f)*40.0f)/360.0f)* DGMathf::PI *2.0f);
		}
	}

	this->transform->position = DGVector3(0, 2.0f, 4.0f);
	this->transform->rotation = DGQuaternion(90.0f, 0, 0, 0);
}

void DGBanner::update(DGContext* ctx){
	if( wiggle_count == 2 ){
		for(int y = 0; y < 45; y++ )			// ��Yƽ��ѭ��
		{
			hold = points[0][y].z;			// �洢��ǰ��ನ��ֵ
			for(int x = 0; x < 44; x++)		// ��Xƽ��ѭ��
			{
				// ��ǰ����ֵ�������Ҳ�Ĳ���ֵ
				points[x][y].z = points[x+1][y].z;
			}
			points[44][y].z=hold;			// �ղŵ�ֵ��Ϊ�����Ĳ���ֵ
		}

		wiggle_count = 0;				// ����������
	}

	wiggle_count++;
}

void DGBanner::draw(DGContext* ctx){
	DGGameObject::draw(ctx);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	int x, y;	
	float float_x, float_y, float_xb, float_yb;

	glBegin(GL_QUADS);

	for (int x=0; x<44; x++) {
		for (int y=0; y<44; y++) {
			float_x = float(x)/44.0f;		// ����X����ֵ
			float_y = float(y)/44.0f;		// ����Y����ֵ
			float_xb = float(x+1)/44.0f;		// X����ֵ+0.0227f
			float_yb = float(y+1)/44.0f;		// Y����ֵ+0.0227f

			glTexCoord2f(float_x, float_y);	// ��һ���������� (���½�)
			glVertex3f(points[x][y].x, points[x][y].y, points[x][y].z);

			glTexCoord2f(float_x, float_yb);	// �ڶ����������� (���Ͻ�)
			glVertex3f(points[x][y+1].x, points[x][y+1].y, points[x][y+1].z);

			glTexCoord2f( float_xb, float_yb);	// �������������� (���Ͻ�)
			glVertex3f(points[x+1][y+1].x, points[x+1][y+1].y, points[x+1][y+1].z);

			glTexCoord2f( float_xb, float_y);	// ���ĸ��������� (���½�)
			glVertex3f(points[x+1][y].x, points[x+1][y].y, points[x+1][y].z);
		}
	}

	glEnd();
}
