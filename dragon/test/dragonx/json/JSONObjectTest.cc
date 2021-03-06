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
 * Created:     2013/12/16
 **********************************************************************/


#include <gtest/gtest.h>
#include <dragonx/json/JSONArray.h>
#include <dragonx/json/JSONObject.h>
#include <dragonx/json/JSONException.h>

#include <gtest/gtest.h>

#include <dragon/io/FileReader.h>
#include <dragon/io/FileWriter.h>

#include <dragon/lang/Integer.h>
#include <dragon/lang/Float.h>
#include <dragon/lang/Long.h>
#include <dragon/lang/System.h>
#include <dragon/io/File.h>
#include <dragon/util/logging/Logger.h>
#include <dragon/lang/gc/Reference.h>

Import dragon::lang;
Import dragon::io;
Import dragon::util::logging;
Import dragon::lang::gc;
Import dragonx::json;

static Logger* logger = Logger::getLogger("dragonx::json::JSONObject", DEBUG);

TEST(Dragonx_Json_JSONObjectTest, testParseJson) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/json_test/json_01.txt");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    String* myWriteStr = new String(L"{\"abc\":123, \"bcd\":123.33}");

    FileWriter* o = new FileWriter(file, false);
    o->append(myWriteStr);
    SafeDelete(o);


    wchar_u buf[512];

    Reader* o2 = new FileReader(file);

    int readSize = o2->read(buf, 512);
    String* myReadStr = new String(buf, 0, readSize);
    EXPECT_TRUE(myReadStr->equals(myWriteStr));

    SafeDelete(o2);


    SafeDelete(file);
    SafeDelete(filePath);

    try {
        JSONObject* jsonObj = JSONObject::parse(myWriteStr);

        int value = jsonObj->getInt("abc");
        EXPECT_EQ(123, value);

        float v2 = jsonObj->getFloat("bcd");
        ASSERT_FLOAT_EQ(123.33f, v2);

        SafeRelease(jsonObj);
    } catch(JSONException* e) {
        String* msg = e->getMessage();

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }   
    
    SafeRelease(myReadStr);
    SafeDelete(o);
    SafeRelease(myWriteStr);
}

TEST(Dragonx_Json_JSONObjectTest, testParseJson2) {
    String* myWriteStr = new String(L"{\"abc\": {\"ddd\":123}}");

    try {
        JSONObject* jsonObj = JSONObject::parse(myWriteStr);

        JSONObject* v2 = jsonObj->getJSONObject("abc");
        ASSERT_TRUE(v2 != null);


        int value = v2->getInt("ddd");
        EXPECT_EQ(123, value);
        SafeRelease(v2);
        
        SafeRelease(jsonObj);
    } catch(JSONException* e) {
        String* msg = e->getMessage();

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeRelease(myWriteStr);
}

TEST(Dragonx_Json_JSONObjectTest, testParseJson3) {
    String* myWriteStr = new String(L"{\"abc\": [{\"ddd\":123}]}");

    try {
        JSONObject* jsonObj = JSONObject::parse(myWriteStr);

        JSONArray* jsonArray = jsonObj->getJSONArray("abc");
        ASSERT_TRUE(jsonArray != null);

        JSONObject* v2 = jsonArray->get(0);
        int value = v2->getInt("ddd");
        EXPECT_EQ(123, value);
        SafeRelease(v2);

        SafeRelease(jsonArray);

        SafeRelease(jsonObj);
    } catch(JSONException* e) {
        String* msg = e->getMessage();

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeRelease(myWriteStr);
}

TEST(Dragonx_Json_JSONObjectTest, toString123) {
    JSONObject* jsonObj = new JSONObject();

    Integer* i = new Integer(123);
    jsonObj->put("abc", i);
    SafeRelease(i);

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, toString1234) {
    JSONObject* jsonObj = new JSONObject();

    Integer* i = new Integer(123);
    jsonObj->put("abc", i);
    SafeRelease(i);

    String* json = jsonObj->toString();
    SafeRelease(json);

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, toString) {
    JSONObject* jsonObj = new JSONObject();

    Integer* i = new Integer(123);
    jsonObj->put("abc", i);
    SafeRelease(i);

    try {
        String* json = jsonObj->toString();
        const Array<byte> data = json->getBytes("UTF-8");
        EXPECT_STREQ("{\n\t\"abc\": 123\n}", data.raw());
        SafeRelease(json);
    } catch(JSONException* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, toString2) {
    JSONObject* jsonObj = new JSONObject();

    Integer* a = new Integer(123);
    jsonObj->put("abc", a);
    SafeRelease(a);

    Float* f = new Float(123.22);
    jsonObj->put("bcd", f);
    SafeRelease(f);

    try {
        String* json = jsonObj->toString();
        const Array<byte> data = json->getBytes("UTF-8");
        EXPECT_STREQ("{\n\t\"bcd\": 123.22,\n\t\"abc\": 123\n}", data.raw());
        SafeRelease(json);
    } catch(JSONException* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, toString3) {
    JSONObject* jsonObj = new JSONObject();

    Integer* a = new Integer(123);
    jsonObj->put("abc", a);
    SafeRelease(a);

    Float* f = new Float(123.22);
    jsonObj->put("bcd", f);
    SafeRelease(f);

    String* s = new String("Hello World!");
    jsonObj->put("efg", s);
    SafeRelease(s);

    try {
        String* json = jsonObj->toString();
        const Array<byte> data = json->getBytes("UTF-8");
        EXPECT_STREQ("{\n\t\"efg\": \"Hello World!\",\n\t\"bcd\": 123.22,\n\t\"abc\": 123\n}", data.raw());
        SafeRelease(json);
    } catch(JSONException* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, toString4) {
    JSONObject* jsonObj = new JSONObject();
    
    Integer* i = new Integer(123);
    jsonObj->put("abc", i);
    SafeRelease(i);

    Float* f = new Float(123.22);
    jsonObj->put("bcd", f);
    SafeRelease(f);

    String* s = new String("Hello World!");
    jsonObj->put("efg", s);
    SafeRelease(s);

    JSONObject* subJsonObj = new JSONObject();

    Integer* i2 = new Integer(234);
    subJsonObj->put("bbb", i2);
    SafeRelease(i2);

    jsonObj->put("sub", subJsonObj);

    SafeRelease(subJsonObj);

    try {
        String* json = jsonObj->toString();
        const Array<byte> data = json->getBytes("UTF-8");
        EXPECT_STREQ("{\n\t\"sub\": {\n\t\t\"bbb\": 234\n\t},\n\t\"efg\": \"Hello World!\",\n\t\"bcd\": 123.22,\n\t\"abc\": 123\n}", data.raw());
        SafeRelease(json);
    } catch(JSONException* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeRelease(msg);
        SafeRelease(e);
    }

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, toString5) {
    JSONObject* jsonObj = new JSONObject();
    
    Integer* i = new Integer(123);
    jsonObj->put("abc", i);
    SafeRelease(i);

    Float* f = new Float(123.22);
    jsonObj->put("bcd", f);
    SafeRelease(f);

    String* s = new String("Hello World!");
    jsonObj->put("efg", s);
    SafeRelease(s);

    JSONObject* subJsonObj1 = new JSONObject();
    Integer* i2 = new Integer(234);
    subJsonObj1->put("bbb", i2);
    SafeRelease(i2);

    JSONObject* subJsonObj2 = new JSONObject();
    Float* f2 = new Float(234.33);
    subJsonObj2->put("bbb", f2);
    SafeRelease(f2);

    JSONArray* array = new JSONArray();
    array->add(subJsonObj1);
    SafeRelease(subJsonObj1);

    array->add(subJsonObj2);
    SafeRelease(subJsonObj2);

    jsonObj->put("array", array);
    SafeRelease(array);

    try {
        String* json = jsonObj->toString();
        const Array<byte> data = json->getBytes("UTF-8");
        EXPECT_STREQ("{\n\t\"efg\": \"Hello World!\",\n\t\"bcd\": 123.22,\n\t\"array\": [\n\t\t{\n\t\t\t\"bbb\": 234\n\t\t},\n\t\t{\n\t\t\t\"bbb\": 234.33\n\t\t}\n\t],\n\t\"abc\": 123\n}", data.raw());
        SafeRelease(json);
    } catch(JSONException* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeDelete(msg);
        SafeDelete(e);
    }

    SafeRelease(jsonObj);
}


TEST(Dragonx_Json_JSONObjectTest, toStringSaveAsFile) {
    const String* base = System::getProperty("HOME");
    String* filePath = new String(L"/dragon_test/json_test/save_json_01.txt");

    File* file = new File(base, filePath);

    File* parent = file->getParentFile();

    if (!parent->exists()) {
        parent->mkdirs();
    }

    SafeDelete(parent);

    FileWriter* o = new FileWriter(file, false);
    

    JSONObject* jsonObj = new JSONObject();
    
    Integer* i = new Integer(123);
    jsonObj->put("abc", i);
    SafeRelease(i);

    Float* f = new Float(123.22);
    jsonObj->put("bcd", f);
    SafeRelease(f);

    String* s = new String("Hello World!");
    jsonObj->put("efg", s);
    SafeRelease(s);

    JSONObject* subJsonObj1 = new JSONObject();
    Integer* i2 = new Integer(234);
    subJsonObj1->put("bbb", i2);
    SafeRelease(i2);

    JSONObject* subJsonObj2 = new JSONObject();
    Float* f2 = new Float(234.33);
    subJsonObj2->put("bbb", f2);
    SafeRelease(f2);

    JSONArray* array = new JSONArray();
    array->add(subJsonObj1);
    SafeRelease(subJsonObj1);

    array->add(subJsonObj2);
    SafeRelease(subJsonObj2);

    jsonObj->put("array", array);
    SafeRelease(array);

    try {
        String* json = jsonObj->toString();

        const Array<byte> data = json->getBytes("UTF-8");
        EXPECT_STREQ("{\n\t\"efg\": \"Hello World!\",\n\t\"bcd\": 123.22,\n\t\"array\": [\n\t\t{\n\t\t\t\"bbb\": 234\n\t\t},\n\t\t{\n\t\t\t\"bbb\": 234.33\n\t\t}\n\t],\n\t\"abc\": 123\n}", data.raw());

        o->append(json);

        SafeRelease(json);
    } catch(JSONException* e) {
        String* msg = e->getMessage();
        logger->error(msg->toUTF8String());

        FAIL();

        SafeRelease(msg);
        SafeRelease(e);
    }

    SafeRelease(o);
    SafeRelease(file);
    SafeRelease(filePath);

    SafeRelease(jsonObj);
}

TEST(Dragonx_Json_JSONObjectTest, Release) {
    JSONObject* obj = new JSONObject();
    SafeRelease(obj);
}

