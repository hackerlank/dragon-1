#include "dg_game_object.h"
#include "dg_graphics_lib.h"

DGGameObject::DGGameObject(void) {
	this->transform = new DGTransform();
}

DGGameObject::DGGameObject(DGTransform* transform) {
	this->transform = transform;
}

DGGameObject::~DGGameObject(void){

}

void DGGameObject::init(DGContext* ctx){
	//��ʼ�����
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];
        com->init(this, ctx);
	}

	//��ʼ�����ӽڵ�
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];
		child->init(ctx);
	}
}

void DGGameObject::update(DGContext* ctx){
	//�������
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];
		if (com->isActive()) {
			com->update(ctx);
		}
	}

	//���º��ӽڵ�
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];
		child->update(ctx);
	}
}

void DGGameObject::draw(DGContext* ctx){
	DGGraphicsLib* gl = ctx->getGraphicsLib();

	// ��������ϵ�任
	DGTransform* tf = this->transform;
	if (tf) {
		//ƽ�ƶ�
		gl->translate(tf->position.x, tf->position.y, tf->position.z);

		//��ת
		gl->rotate(tf->rotation.x, 1.0f, 0.0f, 0.0f);
		gl->rotate(tf->rotation.y, 0.0f, 1.0f, 0.0f);
		gl->rotate(tf->rotation.z, 0.0f, 0.0f, 1.0f);

		//����
		gl->scale(tf->scale.x, tf->scale.y, tf->scale.z);
	}

	// ��������ϵ�任
	tf = this->transform;
	if (tf) {
		//ƽ�ƶ�
		gl->translate(tf->localPosition.x, tf->localPosition.y, tf->localPosition.z);

		//��ת
		gl->rotate(tf->localRotation.x, 1.0f, 0.0f, 0.0f);
		gl->rotate(tf->localRotation.y, 0.0f, 1.0f, 0.0f);
		gl->rotate(tf->localRotation.z, 0.0f, 0.0f, 1.0f);

		//����
		gl->scale(tf->localScale.x, tf->localScale.y, tf->localScale.z);
	}

	//�������
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];

		if (com->isActive()) {
			gl->pushMatrix();
			com->draw(ctx);
			gl->popMatrix();
		}
	}

	//���ƺ���
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];

		gl->pushMatrix();
		child->draw(ctx);
		gl->popMatrix();
	}
}

void DGGameObject::destroy(){
	//�������
	int csize = components.size();
	for(int i=0; i<csize; i++) {
		DGComponent* com = components[i];
		com->destroy();
	}

	//���ٺ��ӽڵ�
	int size = children.size();
	for(int i=0; i<size; i++) {
		DGGameObject* child = children[i];
		child->destroy();
	}
}

void DGGameObject::addChild(DGGameObject* child) {
	this->children.push_back(child);
}

void DGGameObject::addComponent(DGComponent* component){
	this->components.push_back(component);
}

DGComponent* DGGameObject::findComponent(const char* name){
	int size = children.size();

	for(int i=0; i<size; i++) {
		DGComponent* com = components[i];
		if (com->getName().compare(name) == 0) {
			return com;
		}
	}

	return NULL;
}
