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
 * Created:     2013/07/13
 **********************************************************************/

#include <windows.h>

#include <gtest/gtest.h>

#include <dragon.h>
#include <dragon/lang/internal/platform.h>

#include <typeinfo>

Import dragon::lang::internal;

/*
TEST(Dragon_Lang_Internal_SymbolManglingTest, queryPrefixSymbol) {
	EXPECT_EQ("_ZN", query_prefix_symbol());
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, queryNameEndSymbol) {
	EXPECT_EQ("E", query_name_end_symbol());
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, queryBasicTypeSymbol) {
	EXPECT_EQ("c", query_byte_symbol());
	EXPECT_EQ("s", query_short_symbol());
	EXPECT_EQ("i", query_int_symbol());
	EXPECT_EQ("x", query_long_symbol());
	EXPECT_EQ("f", query_float_symbol());
	EXPECT_EQ("d", query_double_symbol());
	EXPECT_EQ("j", query_char_symbol());
	EXPECT_EQ("b", query_boolean_symbol());
	EXPECT_EQ("v", query_void_symbol());
}
*/

/*
TEST(Dragon_Lang_Internal_SymbolManglingTest, mangling_byte) {
	EXPECT_EQ("_ZN6dragon4lang8internal11SymTestBean4testEc", Mangling("dragon::lang::internal::SymTestBean::test(dg_byte)"));
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, mangling_void) {
	EXPECT_EQ("_ZN6dragon4lang8internal11SymTestBean4testEv", Mangling("dragon::lang::internal::SymTestBean::test()"));
}

TEST(Dragon_Lang_Internal_SymbolManglingTest, mangling_CC) {
	EXPECT_EQ("_ZN6dragon4lang8internal11SymTestBeanC1Ev", Mangling("dragon::lang::internal::SymTestBean::SymTestBean()"));
}


TEST(Dragon_Lang_Internal_platformTest, Demanle) {
	char* cc = Demangle("_ZN6dragon4lang8internal11SymTestBean4testEc");
	EXPECT_STREQ("dragon::lang::internal::SymTestBean::test(char)", cc);
	free(cc);
}

TEST(Dragon_Lang_Internal_platformTest, Demanle_CC) {
	char* cc = Demangle("_ZN6dragon4lang8internal11SymTestBeanC1Ev");
	EXPECT_STREQ("dragon::lang::internal::SymTestBean::SymTestBean()", cc);
	free(cc);
}
*/

/*
TEST(Dragon_Lang_Internal_platformTest, Invoke_Class_Size_Check1) {
	void* tb_mem = malloc(2000);

	void* defaultConstructorPtr = GetFuncAddress("dragon::lang::internal::SymTestBean::SymTestBean()");
	void* tb = Invoke<void*>(tb_mem, defaultConstructorPtr);

	free(tb_mem);
}
*/

class SymTestBean2{
public:
	SymTestBean2():data1(100){
		dg_int a = 1 + 3;
		this->data1=a;
	}

private:
	dg_int data1;
	dg_int data2[1024];
};

TEST(Dragon_Lang_Internal_platformTest, Invoke_Class_Size_Check2) {
	SymTestBean2* stb = new SymTestBean2();
	dg_int size = sizeof(*stb);
	SafeDelete(stb);
}

//---------------------------------------------------------------
// int test
void* invoke_test01() {
	int a = 1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test02(int a1) {
	int a = a1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test03(int a1, int b1) {
	int a = a1 + b1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test04(int a1, int b1, int c1) {
	int a = a1 + b1 + c1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test05(int a1, int b1, int c1, int d1) {
	int a = a1 + b1 + c1 + d1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test06(int a1, int b1, int c1, int d1, int e1) {
	int a = a1 + b1 + c1 + d1 + e1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test07(int a1, int b1, int c1, int d1, int e1, int f1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test08(int a1, int b1, int c1, int d1, int e1, int f1, int g1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test09(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test10(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test11(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test12(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1, int k1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test13(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1, int k1, int l1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1;
	int* pa = &a;
	return (void*)pa;
}

void* invoke_test14(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int h1, int i1, int j1, int k1, int l1, int m1) {
	int a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	int* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args) {
	int a1 = 1;
	int b1 = 2;
	int c1 = 3;
	int d1 = 4;
	int e1 = 5;
	int f1 = 6;
	int g1 = 7;
	int h1 = 8;
	int i1 = 9;
	int j1 = 10;
	int k1 = 11;
	int l1 = 12;
	int m1 = 13;

	invoke_test01();
	invoke_test02(a1);
	invoke_test03(a1, b1);
	invoke_test04(a1, b1, c1);
	invoke_test05(a1, b1, c1, d1);
	invoke_test06(a1, b1, c1, d1, e1);
	invoke_test07(a1, b1, c1, d1, e1, f1);
	invoke_test08(a1, b1, c1, d1, e1, f1, g1);
	invoke_test09(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test10(a1, b1, c1, d1, e1, f1, g1, h1, i1);
	invoke_test11(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1);
	invoke_test12(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1);
	invoke_test13(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1);
	invoke_test14(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// short test
void* invoke_test_short_01(short a1, short b1, short c1, short d1, short e1, short f1, short g1, short h1, short i1, short j1, short k1, short l1, short m1) {
	short a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	short* pa = &a;
	return (void*)pa;
}

void* invoke_test_short_02(short a1, short b1, short c1, short d1, short e1, short f1, short g1, short h1) {
	short a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	short* pa = &a;
	return (void*)pa;
}

void* invoke_test_short_03(short a1, short b1, short c1, short d1, short e1, short f1) {
	short a = a1 + b1 + c1 + d1 + e1 + f1;
	short* pa = &a;
	return (void*)pa;
}

void* invoke_test_short_04(short a1, short b1, short c1, short d1) {
	short a = a1 + b1 + c1 + d1;
	short* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_short) {
	short a1 = 1;
	short b1 = 2;
	short c1 = 3;
	short d1 = 4;
	short e1 = 5;
	short f1 = 6;
	short g1 = 7;
	short h1 = 8;
	short i1 = 9;
	short j1 = 10;
	short k1 = 11;
	short l1 = 12;
	short m1 = 13;

	invoke_test_short_04(a1, b1, c1, d1);
	invoke_test_short_03(a1, b1, c1, d1, e1, f1);
	invoke_test_short_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_short_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}


//----------------------------------------------------------
// size_t test
void* invoke_test_size_t_01(size_t a1, size_t b1, size_t c1, size_t d1, size_t e1, size_t f1, size_t g1, size_t h1, size_t i1, size_t j1, size_t k1, size_t l1, size_t m1) {
	size_t a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_size_t_02(size_t a1, size_t b1, size_t c1, size_t d1, size_t e1, size_t f1, size_t g1, size_t h1) {
	size_t a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_size_t_03(size_t a1, size_t b1, size_t c1, size_t d1, size_t e1, size_t f1) {
	size_t a = a1 + b1 + c1 + d1 + e1 + f1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_size_t_04(size_t a1, size_t b1, size_t c1, size_t d1) {
	size_t a = a1 + b1 + c1 + d1;
	size_t* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_size_t) {
	size_t a1 = 1;
	size_t b1 = 2;
	size_t c1 = 3;
	size_t d1 = 4;
	size_t e1 = 5;
	size_t f1 = 6;
	size_t g1 = 7;
	size_t h1 = 8;
	size_t i1 = 9;
	size_t j1 = 10;
	size_t k1 = 11;
	size_t l1 = 12;
	size_t m1 = 13;

	invoke_test_size_t_04(a1, b1, c1, d1);
	invoke_test_size_t_03(a1, b1, c1, d1, e1, f1);
	invoke_test_size_t_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_size_t_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// char test
void* invoke_test_char_01(char a1, char b1, char c1, char d1, char e1, char f1, char g1, char h1, char i1, char j1, char k1, char l1, char m1) {
	char a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	char* pa = &a;
	return (void*)pa;
}

void* invoke_test_char_02(char a1, char b1, char c1, char d1, char e1, char f1, char g1, char h1) {
	char a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	char* pa = &a;
	return (void*)pa;
}

void* invoke_test_char_03(char a1, char b1, char c1, char d1, char e1, char f1) {
	char a = a1 + b1 + c1 + d1 + e1 + f1;
	char* pa = &a;
	return (void*)pa;
}

void* invoke_test_char_04(char a1, char b1, char c1, char d1) {
	char a = a1 + b1 + c1 + d1;
	char* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_char) {
	char a1 = 1;
	char b1 = 2;
	char c1 = 3;
	char d1 = 4;
	char e1 = 5;
	char f1 = 6;
	char g1 = 7;
	char h1 = 8;
	char i1 = 9;
	char j1 = 10;
	char k1 = 11;
	char l1 = 12;
	char m1 = 13;

	invoke_test_char_04(a1, b1, c1, d1);
	invoke_test_char_03(a1, b1, c1, d1, e1, f1);
	invoke_test_char_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_char_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// float test
void* invoke_test_float_01(float a1, float b1, float c1, float d1, float e1, float f1, float g1, float h1, float i1, float j1, float k1, float l1, float m1) {
	float a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	float* pa = &a;
	return (void*)pa;
}

void* invoke_test_float_02(float a1, float b1, float c1, float d1, float e1, float f1, float g1, float h1) {
	float a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	float* pa = &a;
	return (void*)pa;
}

void* invoke_test_float_03(float a1, float b1, float c1, float d1, float e1, float f1) {
	float a = a1 + b1 + c1 + d1 + e1 + f1;
	float* pa = &a;
	return (void*)pa;
}

void* invoke_test_float_04(float a1, float b1, float c1, float d1) {
	float a = a1 + b1 + c1 + d1;
	float* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_float) {
	float a1 = 1;
	float b1 = 2;
	float c1 = 3;
	float d1 = 4;
	float e1 = 5;
	float f1 = 6;
	float g1 = 7;
	float h1 = 8;
	float i1 = 9;
	float j1 = 10;
	float k1 = 11;
	float l1 = 12;
	float m1 = 13;

	invoke_test_float_04(a1, b1, c1, d1);
	invoke_test_float_03(a1, b1, c1, d1, e1, f1);
	invoke_test_float_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_float_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}

//----------------------------------------------------------
// double test
void* invoke_test_double_01(double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_double_02(double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_double_03(double a1, double b1, double c1, double d1, double e1, double f1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_double_04(double a1, double b1, double c1, double d1) {
	double a = a1 + b1 + c1 + d1;
	double* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_double) {
	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;

	invoke_test_double_04(a1, b1, c1, d1);
	invoke_test_double_03(a1, b1, c1, d1, e1, f1);
	invoke_test_double_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_double_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
}


//----------------------------------------------------------
// mix type test
void* invoke_test_mixtype_01(char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_02(char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_03(char a1, short b1, int c1, size_t d1, double e1, double f1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1;
	double* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_04(char a1, short b1, int c1, size_t d1) {
	size_t a = a1 + b1 + c1 + d1;
	size_t* pa = &a;
	return (void*)pa;
}

void* invoke_test_mixtype_05(char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1, void* p1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	double* pa = &a;
	return (void*)pa;
}

struct mix {
	char a1;
	short b1;
	int c1;
	size_t d1;
	double e1;
	double f1;
};

void* invoke_test_mixtype_06(mix m, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1, void* p1) {
	int aa = 1 + 2;
	double a = m.a1 
		+ m.b1 
		+ m.c1 
		+ m.d1 
		+ m.e1 
		+ m.f1 
		+ g1 
		+ h1 
		+ i1 
		+ j1 
		+ k1 
		+ l1 
		+ m1 + aa;
	double* pa = &a;
	return (void*)pa;
}

struct mix2 {
  char a1;
  short b1;
  int c1;
  size_t d1;
  double e1;
  double f1;
};

void* invoke_test_mixtype_07(mix2 m, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1, void* p1) {
	int aa = 1 + 2;
	double a = m.a1 
		+ m.b1 
		+ m.c1 
		+ m.d1 
		+ m.e1 
		+ m.f1 
		+ g1 
		+ h1 
		+ i1 
		+ j1 
		+ k1 
		+ l1 
		+ m1 + aa;
	double* pa = &a;
	return (void*)pa;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mixtype) {
	char a1 = 1;
	short b1 = 2;
	int c1 = 3;
	size_t d1 = 4;

	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	size_t m1 = 13;

	int max_l = sizeof(long);
	int max_ll = sizeof(long long);
	int max_void_p = sizeof(void*);
	int max_float = sizeof(float);
	int max_double = sizeof(double);

	mix m;
	mix2 m2;

	memset(&m, 0, sizeof(mix));
	memset(&m2, 0, sizeof(mix2));

	invoke_test_mixtype_04(a1, b1, c1, d1);
	invoke_test_mixtype_03(a1, b1, c1, d1, e1, f1);
	invoke_test_mixtype_02(a1, b1, c1, d1, e1, f1, g1, h1);
	invoke_test_mixtype_01(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);
	invoke_test_mixtype_05(a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1, (void*)(&m1));
	invoke_test_mixtype_06(m, g1, h1, i1, j1, k1, l1, m1, (void*)(&m1));
	invoke_test_mixtype_07(m2, g1, h1, i1, j1, k1, l1, m1, (void*)(&m1));
}

// ----------------------------------------------------------------------
// mix invoke test
// 
void* invoke_test_mixtype_dd_05(void* pthis, char a1, short b1, int c1, size_t d1, double e1, double f1, double g1, double h1, 
	double i1, double j1, double k1, double l1, size_t m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return cast_void<double>(a);
}

void InvokeTest(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	DWORD result = 0;
	double sse_result = 0.0;

	size_t sum_size = 0;

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo arg = argv[i];
		size_t arg_size = arg.size;
		void* value = arg.value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		if (word_count == 1) {
			value = &arg.value;
		}

		__asm {
			sub         esp, t_size;

			mov         ecx, word_count;
			mov         esi, value;
			mov         edi, esp;
			rep movs    dword ptr es:[edi], dword ptr [esi];
		}
	}

	sum_size += sizeof(void*);

	__asm {
		mov eax, pthis;
		push eax;
	}

	//call object p's method func
	__asm {
		call		func;
		mov         result, eax;
		fstp        sse_result;
	}

	// restore the statck
	__asm {
		mov			eax, sum_size;
		add         esp, eax;
	}		
 
	if (ret->category == CATEGORY_INTEGER) {
		ret->value = (void*)result;
	} else if (ret->category == CATEGORY_SSE) {
		ret->setValue(sse_result);
	}
}
	

void* InvokeTest(void* pthis, void* func, ParamInfo *argv, int argc) {
	ReturnInfo ret("void*");
	InvokeTest(pthis, func, &ret, argv, argc);
	return ret.getValue<void*>();
}

void InvokeMethod(void* pthis, void* func, ReturnInfo* ret, ParamInfo *argv, int argc) {
	DWORD result = 0;
	double sse_result = 0.0;

	size_t sum_size = 0;

	// push param to the statck
	for(int i=argc-1; i>=0; i--){
		ParamInfo arg = argv[i];
		size_t arg_size = arg.size;
		void* value = arg.value;

		size_t word_count = ((arg_size - 1) / CPU_BYTE_LEN + 1);
		size_t t_size = word_count * CPU_BYTE_LEN;
		sum_size += t_size;

		if (word_count == 1) {
			value = &arg.value;
		}

		__asm {
			sub         esp, t_size;

			mov         ecx, word_count;
			mov         esi, value;
			mov         edi, esp;
			rep movs    dword ptr es:[edi], dword ptr [esi];
		}
	}

	//call object p's method func
	__asm {
		mov			ecx, pthis; 
		call		func;
		mov         result, eax;
		fstp        sse_result;
	}

	// restore the statck
	__asm {
		mov			eax, sum_size;
		add         esp, eax;
	}		
 
	if (ret->category == CATEGORY_INTEGER) {
		ret->value = (void*)result;
	} else if (ret->category == CATEGORY_SSE) {
		ret->value = cast_void<double>(sse_result);
	}
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mixtype_22) {
	char a1 = 1;
	short b1 = 2;
	int c1 = 3;
	size_t d1 = 4;

	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	size_t m1 = 13;

    void* pthis = (void*)(&m1);
    void* dd1 = invoke_test_mixtype_dd_05(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

    ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);

    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);

    params[12] = ParamInfo(m1);

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_mixtype_dd_05), params, 13);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeFree(params);
}

//------------------------------------------------------------
// double invoke test
// 
void* invoke_test_double_invoke_01(void* pthis, double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return cast_void<double>(a);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_double_invoke) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;

	void* dd1 = invoke_test_double_invoke_01(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);
    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);
    params[12] = ParamInfo(m1);

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_double_invoke_01), params, 13);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeFree(params);

}

//------------------------------------------------------------
// mix struct invoke test
// 
/* Can not support this
struct mix3 {
  double a1;
  double b1;
  double c1;
  double d1;
  double e1;
  double f1;
};

void* invoke_test_mixtype_struct_invoke_07(void* pthis, mix3 m, double g1, double h1, 
	double i1, double j1, double k1, double l1, double m1) {
	double a = m.a1 
		+ m.b1 
		+ m.c1 
		+ m.d1 
		+ m.e1 
		+ m.f1 
		+ g1 
		+ h1 
		+ i1 
		+ j1 
		+ k1 
		+ l1 
  		+ m1;
	return cast_void<double>(a);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mix_struct_invoke_01) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;


	mix3 m;

	m.a1 = a1;
	m.b1 = b1;
	m.c1 = c1;
	m.d1 = d1;
	m.e1 = e1;
	m.f1 = f1;

	mix3* addr = &m;
	void* dd1 = invoke_test_mixtype_struct_invoke_07(pthis, m, g1, h1, i1, j1, k1, l1, m1);

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 8); 
    params[0] = ParamInfo(m);
    params[1] = ParamInfo(g1);
    params[2] = ParamInfo(h1);
    params[3] = ParamInfo(i1);
    params[4] = ParamInfo(j1);
    params[5] = ParamInfo(k1);
    params[6] = ParamInfo(l1);
    params[7] = ParamInfo(m1);

    size_t sc = 0;
    size_t w_ss = params[0].size / sizeof(void*);
    mix3* mm3 = (mix3*)params[0].value;
    void* val = params[0].value;

    void* mm4 = (void*)malloc(params[0].size);
    memcpy(mm4, val, params[0].size);

	void** stack_args = (void**)realloc(NULL, sizeof(void*) * (sc + w_ss));
	memcpy(stack_args + sc, val, params[0].size);
	mix3* mm5 = (mix3*)stack_args;

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_mixtype_struct_invoke_07), params, 8);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

}


//------------------------------------------------------------
// mix struct invoke test 02
// 

struct mix4 {
  char a1;
  char b1;
  char c1;
  char d1;
  char e1;
  int f1;
};

void* invoke_test_mixtype_struct_invoke_08(void* pthis, mix4 m, double g1, double h1, 
	double i1, double j1, double k1, double l1, double m1) {
	double a = m.a1 
		+ m.b1 
		+ m.c1 
		+ m.d1 
		+ m.e1 
		+ m.f1 
		+ g1 
		+ h1 
		+ i1 
		+ j1 
		+ k1 
		+ l1 
  		+ m1;
	return cast_void<double>(a);
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_mix_struct_invoke_02) {
	void* pthis = (void*)(8888);

	char a1 = 1;
	char b1 = 2;
	char c1 = 3;
	char d1 = 4;
	char e1 = 5;
	int f1 = 600000;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;


	mix4 m;

	size_t size_mix4 = sizeof(mix4);
	size_t size_f1 = sizeof(m.f1);
	void* ddd1 = (void*)&m.d1;
	void* dde1 = (void*)&m.e1;
	void* ddf1 = (void*)&m.f1;

	m.a1 = a1;
	m.b1 = b1;
	m.c1 = c1;
	m.d1 = d1;
	m.e1 = e1;
	m.f1 = f1;

	void* dd1 = invoke_test_mixtype_struct_invoke_08(pthis, m, g1, h1, i1, j1, k1, l1, m1);

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 8); 
    params[0] = ParamInfo(m);
    params[1] = ParamInfo(g1);
    params[2] = ParamInfo(h1);
    params[3] = ParamInfo(i1);
    params[4] = ParamInfo(j1);
    params[5] = ParamInfo(k1);
    params[6] = ParamInfo(l1);
    params[7] = ParamInfo(m1);

	void* dd2 = InvokeTest(pthis, (void*)(&invoke_test_mixtype_struct_invoke_08), params, 8);

	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);
}
*/


//------------------------------------------------------------
// double return invoke test
// 
double invoke_test_double_ret_invoke_01(void* pthis, double a1, double b1, double c1, double d1, double e1, double f1, double g1, double h1, double i1, double j1, double k1, double l1, double m1) {
	double a = a1 + b1 + c1 + d1 + e1 + f1 + g1 + h1 + i1 + j1 + k1 + l1 + m1;
	return a;
}

TEST(Dragon_Lang_Internal_platformTest, Invoke_Multi_Args_double_ret_invoke) {
	void* pthis = (void*)(8888);

	double a1 = 1;
	double b1 = 2;
	double c1 = 3;
	double d1 = 4;
	double e1 = 5;
	double f1 = 6;
	double g1 = 7;
	double h1 = 8;
	double i1 = 9;
	double j1 = 10;
	double k1 = 11;
	double l1 = 12;
	double m1 = 13;

	double dd1 = invoke_test_double_ret_invoke_01(pthis, a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, m1);

	ReturnInfo* ret = new ReturnInfo("double");

	ParamInfo* params = (ParamInfo*)malloc(sizeof(ParamInfo) * 13); 
    params[0] = ParamInfo(a1);
    params[1] = ParamInfo(b1);
    params[2] = ParamInfo(c1);
    params[3] = ParamInfo(d1);
    params[4] = ParamInfo(e1);
    params[5] = ParamInfo(f1);
    params[6] = ParamInfo(g1);
    params[7] = ParamInfo(h1);
    params[8] = ParamInfo(i1);
    params[9] = ParamInfo(j1);
    params[10] = ParamInfo(k1);
    params[11] = ParamInfo(l1);
    params[12] = ParamInfo(m1);

	InvokeTest(pthis, (void*)(&invoke_test_double_ret_invoke_01), ret, params, 13);

	double dd2 = ret->getValue<double>();
	dg_boolean is_true = (dd1 == dd2);
	EXPECT_EQ(dg_true, is_true);

	SafeDelete(ret);
	SafeFree(params);
}