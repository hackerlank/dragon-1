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
 * Created:     2013/03/31
 **********************************************************************/

#ifndef Type_Reflect_Lang_Dragon_H 
#define Type_Reflect_Lang_Dragon_H

#include <dragon/config.h>

#include <stdlib.h>
#include <typeinfo>

BeginPackage3(dragon, lang, reflect)

Import std;

class _DragonExport Type
{
public:
	Type(const char* name);
	Type(const char* name, int offset, size_t count);
	Type(const char* name, size_t size);
    Type(const type_info& info, size_t size);
    Type(const Type& type);

    virtual ~Type();

public:
    Type &operator=(const Type& type);

public:
	virtual const char* getName() const;
	virtual size_t getSize() const;
    virtual bool equals(const Type* type) const;	

protected:
	char* name;
	size_t size;
};


template<class T>
inline Type* TypeOf() {
    return new Type(typeid(T), sizeof(T));
}

template<class T>
inline Type* TypeOf(T type) {
    return new Type(typeid(type), sizeof(type));
}

template<class T>
inline Type* TypeOf(T* type) {
    return new Type(typeid(*type), sizeof(*type));
}

EndPackage3//(dragon, lang, reflect)

#endif//Library_Reflect_Lang_Dragon_H