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


#include <dragon/lang/String.h>
#include <dragon/lang/Integer.h>
#include <dragon/lang/reflect/Type.h>

Import dragon::lang;
Import dragon::lang::reflect;

const Type* Integer::TYPE = TypeOf<Integer>();
const Type* Integer::INNER_TYPE = TypeOf<int>();

/**
 * All possible dg_chars for representing a number as a String
 */
const char Integer::digits[] = {
	'0' , '1' , '2' , '3' , '4' , '5' ,
	'6' , '7' , '8' , '9' , 'a' , 'b' ,
	'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
	'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
	'o' , 'p' , 'q' , 'r' , 's' , 't' ,
	'u' , 'v' , 'w' , 'x' , 'y' , 'z'
};

const char Integer::DigitTens[] = {
	'0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
	'1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
	'2', '2', '2', '2', '2', '2', '2', '2', '2', '2',
	'3', '3', '3', '3', '3', '3', '3', '3', '3', '3',
	'4', '4', '4', '4', '4', '4', '4', '4', '4', '4',
	'5', '5', '5', '5', '5', '5', '5', '5', '5', '5',
	'6', '6', '6', '6', '6', '6', '6', '6', '6', '6',
	'7', '7', '7', '7', '7', '7', '7', '7', '7', '7',
	'8', '8', '8', '8', '8', '8', '8', '8', '8', '8',
	'9', '9', '9', '9', '9', '9', '9', '9', '9', '9',
} ; 

const char Integer::DigitOnes[] = { 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
} ;

void Integer::getChars(int i, int index, dg_char* buf) {
    int q, r;
    int dg_charPos = index;
    dg_char sign = 0;
    unsigned int k = 0; //TODO fix int

    if (i < 0) { 
        sign = '-';
        i = -i;
    }

    k = i;

    // Generate two digits per iteration
    while (k >= 65536) {
        q = k / 100;
    	// really: r = k - (q * 100);
        r = k - ((q << 6) + (q << 5) + (q << 2));
        k = q;
        buf [--dg_charPos] = DigitOnes[r];
        buf [--dg_charPos] = DigitTens[r];
    }

    // Fall thru to fast mode for smaller numbers
    // assert(k <= 65536, k);
    for (;;) { 
        q = (k * 52429) >> (16+3);
        r = k - ((q << 3) + (q << 1));  // r = k-(q*10) ...
        buf [--dg_charPos] = digits [r];
        k = q;
        if (k == 0) break;
    }

    if (sign != 0) {
        buf [--dg_charPos] = sign;
    }
}

static int sizeTable[] = { 9, 99, 999, 9999, 99999, 999999, 9999999,
                                  99999999, 999999999, Integer::MAX_VALUE };

// Requires positive x
static int stringSize(int x) {
    for (int i=0; ; i++)
        if (x <= sizeTable[i])
            return i+1;
}

String* Integer::toString(int i) {
    if (i == Integer::MIN_VALUE)
        return new String("-2147483648");
    int size = (i < 0) ? stringSize(-i) + 1 : stringSize(i);
    dg_char* buf = new dg_char[size];
    getChars(i, size, buf);
    String* result = new String(buf, 0, size);
    SafeDeleteArray(buf);

    return result;
}
// member method

Integer::Integer() 
    :value(0) {
   
}

Integer::Integer(int val) 
    :value(val) {

}

Integer::~Integer() {

}


String* Integer::toString() const {
    return Integer::toString(this->value);
}


Integer* Integer::parseInt(const String& str) throw(NumberFormatException*) {
    if (!str.matches("-?\\d+")) {
        throw new NumberFormatException();
    }

    const Array<byte> data = str.getBytes("UTF-8");
    const char* num = data.raw();
    int value = atoi(num);
    return new Integer(value);
}

//--------- Implements dragon::lang::Number --------------
int Integer::intValue() {
    return this->value;
}

dg_long Integer::longValue() {
    return (dg_long)intValue();
}

float Integer::floatValue() {
    return (float)intValue();
}

double Integer::doubleValue() {
    return (double)intValue();
}

