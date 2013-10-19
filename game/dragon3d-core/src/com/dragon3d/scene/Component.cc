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
#include <com/dragon3d/scene/GameObject.h>
 
Import com::dragon3d::scene;

const Type Component::TYPE = Type(typeid(Component), sizeof(Component));

Component::Component() 
    :active(true) {

}

Component::~Component() {

}

void Component::update(Input* input, ReadOnlyTimer* timer) {

}

bool Component::isTypeOf(const Type& type) {
    if (Component::TYPE.equals(&type)) {
        return true;
    }
}

String* Component::getName() {
    if (this->gameObject != null) {
        return this->gameObject->name;
    }

    return null;
}