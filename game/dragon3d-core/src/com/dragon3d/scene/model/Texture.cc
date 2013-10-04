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


#include <com/dragon3d/scene/model/Texture.h>
#include <dragon/util/logging/Logger.h>

Import dragon::util::logging;
Import com::dragon3d::scene::model;

static Logger* logger = Logger::getLogger("com::dragon3d::scene::model::Texture", INFO);

Texture::Texture(const char* textureFile) : isInit(false) {
	size_t p_size = strlen(textureFile);
	char* buf = (char*)malloc(p_size + 1);
	strcpy(buf, textureFile);
	this->textureFile = buf;
}

Texture::~Texture(void){

}

int Texture::getNativeTextureID(){
	return this->nativeTextureID;
}