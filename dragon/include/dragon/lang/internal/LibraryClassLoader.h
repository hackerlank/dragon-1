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
 * Created:     2013/07/26
 **********************************************************************/


#ifndef LibraryClassLoader_Internal_Lang_Dragon_H
#define LibraryClassLoader_Internal_Lang_Dragon_H

#include <dragon/config.h>
#include <dragon/lang/ClassLoader.h>
#include <dragon/lang/internal/Library.h>

#include <vector>

BeginPackage3(dragon, lang, internal)

Import dragon::lang;
Import std;

class _DragonExport LibraryClassLoader 
	extends(ClassLoader) {
public:
	typedef vector<Library*> LibraryList;
	typedef LibraryList::iterator Iterator;

public:
	LibraryClassLoader();
	LibraryClassLoader(const char* libPath);
	virtual ~LibraryClassLoader();

protected: //Override ClassLoader
	virtual Library* findLibrary(const char* libPath);
	virtual Class* findClass(const char* name);

public:
	virtual void load(const char* libPath);

protected:
	virtual Class* defineClass(const char* name, Library::NameSpace* space);

protected:
	LibraryList* librarys;	
};//LibraryClassLoader

EndPackage3 //(dragon, lang, internal)

#endif //LibraryClassLoader_Internal_Lang_Dragon_H
