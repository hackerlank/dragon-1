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

#include <dragon/lang/Exception.h>

Import dragon::lang;

Exception::Exception(){
	//this->message = new String(L"Exception");
	this->cause = null;
}

Exception::Exception(const String& message){
	//this->message = new String(message);
	this->cause = null;
}

Exception::Exception(Throwable* cause){
	SafeDelete(this->cause);
	this->cause = cause;
}

Exception::Exception(const String& message, Throwable* cause){
	//this->message = new String(message);
	SafeDelete(this->cause);
	this->cause = cause;
} 