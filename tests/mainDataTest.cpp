/*
 * File:   mainDataTest.cpp
 * Author: kloplop321
 *
 * Created on Jun 30, 2011, 12:10:55 PM
 */
/*
 Copyright (c) <2011> <Levi (kloplop321.com)>

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
 */
#include "mainDataTest.h"
#include "data.h"


CPPUNIT_TEST_SUITE_REGISTRATION(mainDataTest);

mainDataTest::mainDataTest() {
    /*klop::Data data(3);
    data.testSelf();*/
}

mainDataTest::~mainDataTest() {
}

void mainDataTest::setUp() {
}

void mainDataTest::tearDown() {
}

void mainDataTest::testData() {
    klop::Data data;
    if(data.dataType() == klop::kinds::nullData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData2() {
    const int p0 = -4;
    klop::Data data(p0); 
    if(data.dataType() == klop::kinds::intData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData3() {
    const long int p0 = -2147483646;
    klop::Data data(p0);
    if(data.dataType() == klop::kinds::lintData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData4() {
    const unsigned int p0 = 6;
    klop::Data data(p0);
    if(data.dataType() == klop::kinds::uintData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData5() {
    const unsigned long int p0 = 4294967294;
    klop::Data data(p0);
    if(data.dataType() == klop::kinds::ulintData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData6() {
    const double p0 = 8.9;
    klop::Data data(p0);
    if(data.dataType() == klop::kinds::doubleData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData7() {
    const bool p0 = true;
    klop::Data data(p0);
    if(data.dataType() == klop::kinds::boolData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData8() {
    const char* p0 = "Hello";
    klop::Data data(p0);
    if(data.dataType() == klop::kinds::stringData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testData9() {
    const std::string& val = "World";
    klop::Data data(val);
    if(data.dataType() == klop::kinds::stringData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}
void mainDataTest::testData10() {
    klop::Data data;
    //prepare the structure
    klop::Data* child1 = new klop::Data;
    klop::Data* child2 = new klop::Data;
    klop::Data* schild1 = new klop::Data("s1");
    klop::Data* schild2 = new klop::Data("s2");
    data.toAssoc();
    child1->toAssoc();
    child2->toAssoc();
    child1->addChild((std::string)"J",schild1);
    child2->addChild((std::string)"L",schild2);
    data.addChild((std::string)"J", child1);
    data.addChild((std::string)"B", child2);
    CPPUNIT_ASSERT(data.isMember("J"));
    CPPUNIT_ASSERT(data.isMember("B"));
    CPPUNIT_ASSERT(data["J"].isMember("J"));
    CPPUNIT_ASSERT(data["J"]["J"] == "s1");
    CPPUNIT_ASSERT(data["B"].isMember("L"));
    CPPUNIT_ASSERT(data["B"]["L"] == "s2");
    klop::Data data2(data);
    //Time to see if it copied right.
    CPPUNIT_ASSERT(data2.isMember("J"));
    CPPUNIT_ASSERT(data2.isMember("B"));
    CPPUNIT_ASSERT(data2["J"].isMember("J"));
    CPPUNIT_ASSERT(data2["J"]["J"] == "s1");
    CPPUNIT_ASSERT(data2["B"].isMember("L"));
    CPPUNIT_ASSERT(data2["B"]["L"] == "s2");
    
    //Need to test being able to copy a 2 level tree.
}
void mainDataTest::testAddChild() {
    unsigned long int index = 0;
    klop::Data* data2 = new klop::Data(40938);
    klop::Data data;
    data.toList();
    data.addChild(data2);
    if(data.isMember(index)) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAddChild2() {
    std::string p0 = "Hi";
    klop::Data* data2 = new klop::Data("Arggg");
    klop::Data data;
    data.toAssoc();
    data.addChild(p0, data2);
    if(data.isMember(p0)) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAddChild3() {
    const char* p0 = "Union";
    klop::Data* data2 = new klop::Data(509863.3f);
    klop::Data data;
    data.toAssoc();
    data.addChild(p0, data2);
    if(data.isMember(p0)) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAddChild4() {
    unsigned long int index = 0;
    klop::Data* data2 = new klop::Data(-309);
    klop::Data data;
    data.toList();
    data.addChild(data2);
    CPPUNIT_ASSERT(data.isMember(index));
}

void mainDataTest::testArrayType() {
    klop::Data data = klop::Data();
    data.setArrayType(klop::kinds::byIndex);
    klop::kinds::ArrayType result = data.arrayType();
    if(result == klop::kinds::byIndex) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsCString() {
    klop::Data data("Hello");
    const char* result = data.asCString();
    if(strcmp("Hello", result) == 0) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsDouble() {
    klop::Data data(3.20f);
    const double result = data.asDouble();
    if(result == 3.2f) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsInt() {
    klop::Data data(3);
    const int result = data.asInt();
    if(result == 3) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsLInt() {
    const long int desired = -345098342;
    klop::Data data(desired);
    const long int result = data.asLInt();
    if(result == desired) {
        CPPUNIT_ASSERT(true);
    }else{
        //printf("Result faled. desired: %d, got: %d",desired, result);
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsString() {
    klop::Data data("World");
    const std::string result = data.asString();
    if(strcmp(result.c_str(), "World") == 0) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsUInt() {
    const unsigned int desired = 209;
    klop::Data data(desired);
    const unsigned int result = data.asUInt();
    if(desired == result) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testAsULInt() {
    const unsigned long int desired = 450983456097;
    klop::Data data(desired);
    const unsigned long int result = data.asULInt();
    if(desired == result) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testClear() {
    klop::Data data;
    data.toList();
    data.addChild(new klop::Data(1));
    data.clear();
    if(data.size() == 0) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testCompare() {
    klop::Data data = klop::Data(11);
    const klop::Data p0 = klop::Data(10);
    //printf("_%d vs %d_",data.dataType(), p0.dataType());
    int result = data.compare(&p0);
    //printf(" %d ",result);
    if(result == 1) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testDataType() {
    klop::Data data = klop::Data(32.3f);
    klop::kinds::DataType result = data.dataType();
    if(result == klop::kinds::doubleData) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testIsBool() {
    klop::Data data(true);
    bool result = data.isBool();
    if(result) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testIsData() {
    klop::Data data(4);
    bool result = data.isData();
    CPPUNIT_ASSERT(!result);
    data.reset();
    data.toAssoc();
    result = data.isData();
    if(result) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testIsDouble() {
    klop::Data data(3);
    bool result = data.isDouble();
    CPPUNIT_ASSERT(!result);
    klop::Data data2(3.0f);
    result = data2.isDouble();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testIsEmpty() {
    klop::Data data;
    data.toAssoc();
    bool result = data.isEmpty();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testIsInt() {
    klop::Data data(3);
    bool result = data.isInt();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testIsLInt() {
    const long int p0 = 409438902;
    klop::Data data(p0);
    bool result = data.isLInt();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testIsNull() {
    klop::Data data;
    bool result = data.isNull();
    CPPUNIT_ASSERT(result);
    klop::Data data2("Eggs");
    result = data2.isNull();
    CPPUNIT_ASSERT(!result);
}

void mainDataTest::testIsNumeric() {
    klop::Data data(3);
    bool result = data.isNumeric();
    CPPUNIT_ASSERT(result);
    klop::Data data2("Eggs");
    result = data2.isNumeric();
    CPPUNIT_ASSERT(!result);
}
void mainDataTest::testIsString() {
    klop::Data data("Eggs");
    bool result = data.isString();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testIsUInt() {
    unsigned int p0 = 40983;
    klop::Data data(p0);
    bool result = data.isUInt();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testIsULInt() {
    unsigned long int p0 = 430984309580298;
    klop::Data data(p0);
    bool result = data.isULInt();
    CPPUNIT_ASSERT(result);
}

void mainDataTest::testReset() {
    klop::Data data;
    data.reset();
    CPPUNIT_ASSERT(data.isNull() && data.size() == 0);
}

void mainDataTest::testSetArrayType() {
    klop::kinds::ArrayType p0 = klop::kinds::byAssociation;
    klop::Data data;
    data.setArrayType(p0);
    if(data.arrayType() == klop::kinds::byAssociation) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testSize() {
    klop::Data data;
    klop::Data* data2 = new klop::Data(40938);
    data.toList();
    CPPUNIT_ASSERT(data.size() == 0);
    data.addChild(data2);
    unsigned long int result = data.size();
    if(result == 1) {
        CPPUNIT_ASSERT(true);
    }else{
        CPPUNIT_ASSERT(false);
    }
}

void mainDataTest::testToAssoc() {
    klop::Data data;
    data.toAssoc();
    CPPUNIT_ASSERT(data.arrayType() == klop::kinds::byAssociation);
}

void mainDataTest::testToList() {
    klop::Data data;
    data.toList();
    CPPUNIT_ASSERT(data.arrayType() == klop::kinds::byIndex);
}
void mainDataTest::testOperators(){
    klop::Data data;
    data.toList();
    klop::Data* data2 = new klop::Data(3);
    klop::Data* data3 = new klop::Data("Eggs");
    klop::Data* data4 = new klop::Data(3.14159);
    data.addChild(data2);
    CPPUNIT_ASSERT(data.size() == 1);
    data.addChild(data3);
    CPPUNIT_ASSERT(data.size() == 2);
    data.addChild(data4);
    CPPUNIT_ASSERT(data.size() == 3);
    data.reset();
    data.toAssoc();
    //By reseting, all the pointers are freed, so we must recreate our reference data.
    data2 = new klop::Data(3);
    data3 = new klop::Data("Eggs");
    data4 = new klop::Data(3.14159);
    CPPUNIT_ASSERT(data.size() == 0);
    data.addChild((std::string)"three",data2);
    data.addChild((std::string)"3d", data3);
    data.addChild((std::string)"pi", data4);
    CPPUNIT_ASSERT(data.size() == 3);
    CPPUNIT_ASSERT(data.isMember("three"));
    CPPUNIT_ASSERT(data.isMember("3d"));
    CPPUNIT_ASSERT(data.isMember("pi"));
    //printf("-_%f_-", data["pi"].asDouble());
}
void mainDataTest::testOperators2(){
    klop::Data data;
    CPPUNIT_ASSERT(data.dataType() == klop::kinds::nullData);
    CPPUNIT_ASSERT(!data);
    klop::Data data2(4);
    klop::Data data3(5);
    klop::Data data4(4);
    CPPUNIT_ASSERT(data2 < data3);
    CPPUNIT_ASSERT(data3 > data2);
    CPPUNIT_ASSERT(data2 <= data4);
    CPPUNIT_ASSERT(data2 >= data4);
    CPPUNIT_ASSERT(data2 == data4);
    CPPUNIT_ASSERT(data2 != data3);
    CPPUNIT_ASSERT(!(data2 != data4));
    data.toList();
    data.addChild(data2);
    CPPUNIT_ASSERT(data.size()>0);
    CPPUNIT_ASSERT(data[0] == data2);
}
void mainDataTest::testIterators(){
    //This tests the list iterators.
    klop::Data data;
    data.toList();
    klop::Data data2(4);
    klop::Data data3(5);
    klop::Data data4(6);
    data.addChild(data2);
    data.addChild(data3);
    data.addChild(data4);
    int x = 4;
    klop::Data::list_iterator it;
    for(it = data.list_begin(); it != data.list_end(); it++){
        CPPUNIT_ASSERT(it->second->asInt() == x);
        x++;
    }
}
void mainDataTest::testIterators2(){
    //This tests the map iterator.
    klop::Data data;
    data.toAssoc();
    klop::Data data2(4);
    klop::Data data3(5);
    klop::Data data4(6);
    std::string names[] = { "Erg","Org","Urg"};//maps ordered in alphabetical Red black.
    data.addChild(names[0],data2);
    data.addChild(names[1],data3);
    data.addChild(names[2],data4);
    int x = 4;
    int y = 0;
    klop::Data::map_iterator it;
    for(it = data.map_begin(); it != data.map_end(); it++){
        CPPUNIT_ASSERT(it->first == names[y]);
        CPPUNIT_ASSERT(it->second->asInt() == x);
        x++;y++;
    }
    
    CPPUNIT_ASSERT(y == names->length());
}