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
 * Created:     2014/02/11
 **********************************************************************/

#include <dragon/lang/System.h>
#include <dragon/io/File.h>
#include <dragon/io/FileInputStream.h>

#include <dragon/util/logging/Logger.h>

#include <com/dragon3d/util/assets/Resource.h>
#include <com/dragon3d/util/assets/AssetsManager.h>

Import dragon::lang;
Import dragon::io;

Import com::dragon3d::util::assets;
Import dragon::util::logging;

const Type* Resource::TYPE = TypeOf<Resource>();
static Logger* logger = Logger::getLogger(Resource::TYPE, ERROR);

Resource::Resource(const String& uri) {
    this->uri = new String(uri);
}

Resource::~Resource() {
    SafeDelete(this->uri);
}

InputStream* Resource::getInputStream() {
    File* file = new File(this->uri);
    FileInputStream* fis = new FileInputStream(file);
    SafeDelete(file);

    return fis;
}