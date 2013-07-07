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

#ifndef DllLibrary_Reflect_Lang_Dragon_H 
#define DllLibrary_Reflect_Lang_Dragon_H

#include <dragon/config.h>
#include "Library.h"

/** 
 * Maintains all dragon operator.
 * @version 0.1.3
 * @since 2010-03-24
 */
BeginPackage3(dragon, lang, reflect)

class _DragonExport DllLibrary:public Object,public Library
{
public:
	DllLibrary();
	DllLibrary(HMODULE hModule);
	DllLibrary(String dllPath) throw(FileNotFoundException);
	virtual ~DllLibrary();

public:
	virtual void load(String libPath) throw(FileNotFoundException);
	virtual void free();

	virtual P<Class<Object>> getClassForName(String className);
	virtual bool updateClass(Class<Object>* clazz);
	virtual bool containsClass(String className);
	virtual int getClassCount();

	virtual FARPROC getClassProc(String methodName);
	virtual P<Method> getClassMethod(String methodName);
	virtual P<Array<P<Method>>> getClassMethods();
	virtual int getMethodCount();

protected:
	virtual bool processLib();
	virtual bool processMethod(String methodSign,FARPROC pfn);

private:
	HMODULE hModule;
	int methodCount;
	P<Map<String,P<Method>>> methodMap;
	P<Map<String,P<Class<Object>>>> classMap;
};

EndPackage3//(dragon, lang, reflect)

#endif//DllLibrary_Reflect_Lang_Dragon_H