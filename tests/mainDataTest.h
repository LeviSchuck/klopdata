/*
 * File:   mainDataTest.h
 * Author: kloplop321
 *
 * Created on Jun 30, 2011, 12:10:55 PM
 */

#ifndef MAINDATATEST_H
#define	MAINDATATEST_H

#include <cppunit/extensions/HelperMacros.h>

class mainDataTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(mainDataTest);

    CPPUNIT_TEST(testData);
    CPPUNIT_TEST(testData2);
    CPPUNIT_TEST(testData3);
    CPPUNIT_TEST(testData4);
    CPPUNIT_TEST(testData5);
    CPPUNIT_TEST(testData6);
    CPPUNIT_TEST(testData7);
    CPPUNIT_TEST(testData8);
    CPPUNIT_TEST(testData9);
    CPPUNIT_TEST(testData10);
    CPPUNIT_TEST(testAddChild);
    CPPUNIT_TEST(testAddChild2);
    CPPUNIT_TEST(testAddChild3);
    CPPUNIT_TEST(testAddChild4);//*/
    CPPUNIT_TEST(testArrayType);
    CPPUNIT_TEST(testAsCString);
    CPPUNIT_TEST(testAsDouble);
    CPPUNIT_TEST(testAsInt);
    CPPUNIT_TEST(testAsLInt);
    CPPUNIT_TEST(testAsString);
    CPPUNIT_TEST(testAsUInt);
    CPPUNIT_TEST(testAsULInt);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST(testCompare);
    CPPUNIT_TEST(testDataType);
    CPPUNIT_TEST(testIsBool);
    CPPUNIT_TEST(testIsData);
    CPPUNIT_TEST(testIsDouble);
    CPPUNIT_TEST(testIsEmpty);
    CPPUNIT_TEST(testIsInt);
    CPPUNIT_TEST(testIsLInt);
    CPPUNIT_TEST(testIsNull);
    CPPUNIT_TEST(testIsNumeric);
    CPPUNIT_TEST(testIsString);
    CPPUNIT_TEST(testIsUInt);
    CPPUNIT_TEST(testIsULInt);
    CPPUNIT_TEST(testReset);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testToAssoc);
    CPPUNIT_TEST(testToList);
    CPPUNIT_TEST(testOperators);
    CPPUNIT_TEST(testOperators2);
    CPPUNIT_TEST(testIterators);
    CPPUNIT_TEST(testIterators2);

    CPPUNIT_TEST_SUITE_END();

public:
    mainDataTest();
    virtual ~mainDataTest();
    void setUp();
    void tearDown();

private:
    void testData();
    void testData2();
    void testData3();
    void testData4();
    void testData5();
    void testData6();
    void testData7();
    void testData8();
    void testData9();
    void testData10();
    void testAddChild();
    void testAddChild2();
    void testAddChild3();
    void testAddChild4();
    void testArrayType();
    void testAsCString();
    void testAsDouble();
    void testAsInt();
    void testAsLInt();
    void testAsString();
    void testAsUInt();
    void testAsULInt();
    void testClear();
    void testCompare();
    void testDataType();
    void testIsBool();
    void testIsData();
    void testIsDouble();
    void testIsEmpty();
    void testIsInt();
    void testIsLInt();
    void testIsNull();
    void testIsNumeric();
    void testIsString();
    void testIsUInt();
    void testIsULInt();
    void testReset();
    void testSize();
    void testToAssoc();
    void testToList();
    void testOperators();
    void testOperators2();
    
    void testIterators();
    void testIterators2();
};

#endif	/* MAINDATATEST_H */

