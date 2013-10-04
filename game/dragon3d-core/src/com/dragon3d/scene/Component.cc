/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/


#include <com/dragon3d/scene/Component.h>

Import com::dragon3d::scene;

Component::Component() {

}

Component::~Component() {

}

void Component::update(Input* input, ReadOnlyTimer* timer) {

}

/*

#include "dg_component.h"
#include "dg_game_object.h"

DGComponent::DGComponent(void){
	this->name = "DGComponent";
	this->active = true;
}

DGComponent::DGComponent(const char* name){
	this->name = name;
}

DGComponent::~DGComponent(void){

}

string DGComponent::getName(){
	return this->name;
}

DGboolean DGComponent::isActive(){
	return this->active;
}

void DGComponent::setActive(DGboolean active){
	this->active = active;
}


void DGComponent::init(DGGameObject* gameObject, DGContext* ctx){
    this->gameObject = gameObject;
    this->transform = gameObject->transform;
}

void DGComponent::update(DGContext* ctx){

}

void DGComponent::draw(DGContext* ctx){

}

void DGComponent::destroy(){

}



 */