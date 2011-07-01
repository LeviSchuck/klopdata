/* 
 * File:   data.h
 * Author: kloplop321
 *
 * Created on June 28, 2011, 12:56 PM
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

#ifndef DATA_H
#define	DATA_H
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <malloc.h>
#include <list>


namespace klop {
    namespace kinds {
        enum DataType {
            nullData = 0,
            intData,
            uintData,
            lintData,
            ulintData,
            doubleData,
            boolData,
            stringData,
            moreData
        };
        enum ArrayType {
            byNothing = 0,
            byIndex,
            byAssociation//Not an array
        };
    }
    class Data {
    public:
        typedef std::vector<std::string> Members;
        typedef std::map<std::string, Data*> ObjectValues;
        typedef std::map<unsigned long int, Data*> ObjectList;
        typedef ObjectList::iterator list_iterator;
        //typedef ObjectList::const_iterator list_const_iterator;
        typedef ObjectValues::iterator map_iterator;
        //typedef ObjectValues::const_iterator map_const_iterator;
        
        Data();//This is null.
        /*Starting Numbers*/
        Data(const int);
        Data(const long int);
        /**Unsigned Numbers*/
        Data(const unsigned int);
        Data(const unsigned long int);
        /**Floating Numbers*/
        Data(const double);
        /*Ending numbers*/

        Data(const bool);

        Data(const char*);
        Data(const std::string &val);
        Data(const Data& data);
        Data(const Data* data);

        //Time for operators

        //Data &operator =(const Data&);//I have no clue how to return myself like this..
        const bool operator !() const;//Can't seem to get this to work.
        const bool operator <(const Data&) const;
        const bool operator <=(const Data&) const;
        const bool operator >=(const Data&) const;
        const bool operator >(const Data&) const;
        const bool operator ==(const Data&) const;
        const bool operator !=(const Data&) const;
        
        int compare(const Data*) const;
        /*
         Example of what the int index would be used for
         * <list id="happy">
         *      <item>blah</item>
         *      <item>another</item>
         * </list>
         * This does not necessarily mean duplication, but multiple entries.
         * so, it would be accessed like root["list"][0] for blah
         */
        Data& operator[](unsigned long int index);
        //Data& operator[](const char* key);
        Data& operator[](const std::string &key);


        

        const char* asCString() const;
        const std::string asString() const;
        const int asInt() const;
        const long int asLInt() const;
        const unsigned int asUInt() const;
        const unsigned long int asULInt() const;
        const double asDouble() const;

        bool isNull() const;
        bool isBool() const;
        bool isInt() const;
        bool isUInt() const;
        bool isLInt() const;
        bool isULInt() const;
        bool isString() const;
        bool isData() const;
        bool isDouble() const;
        bool isNumeric() const;
        bool isMember(const std::string) const;
        bool isMember(unsigned long int index);

        unsigned long int size() const;
        bool isEmpty() const;
        void clear();
        const kinds::DataType dataType() const;
        const kinds::ArrayType arrayType() const;
        void setArrayType(kinds::ArrayType);
        void reset();
        
        void addChild(Data* data);
        void addChild(std::string, Data* data);
        void addChild(char*, Data* data);
        void addChild(const Data& data);
        void addChild(std::string,const Data& data);
        void addChild(char*,const Data& data);
        void toList();//Convert so we are moreData and byIndex
        void toAssoc();//Convert so we are moreData and 
        
        list_iterator list_begin();
        list_iterator list_end();
        //list_const_iterator list_const_begin();
        //list_const_iterator list_const_end();
        
        map_iterator map_begin();
        map_iterator map_end();
        //map_const_iterator map_const_begin();
        //map_const_iterator map_const_end();
        
        
        virtual ~Data();
        //void testSelf();
        
    private:
        void addChild(unsigned long int index, Data* data);
        kinds::DataType myType;
        kinds::ArrayType myArrayType;
        ObjectValues myMap;
        ObjectList myList;
        union numericalData {
            int i;
            double d;
            long int li;
            unsigned int ui;
            unsigned long int uli;
            bool b;
        } numericData;   
        
        
        const int numDataToInt() const;
        const bool numDataToBool() const;
        const double numDataToDouble() const;
        const long int numDataToLInt() const;
        const unsigned int numDataToUInt() const;
        const unsigned long int numDataToULInt() const;
       
        std::string stringData;
    };
    class ValueAllocator {//from jsoncpp public domain
   public:
      enum { unknown = (unsigned)-1 };

      virtual ~ValueAllocator();

      virtual char *makeMemberName( const char *memberName ) = 0;
      virtual void releaseMemberName( char *memberName ) = 0;
      virtual char *duplicateStringValue( const char *value, 
                                          unsigned int length = unknown ) = 0;
      virtual void releaseStringValue( char *value ) = 0;
   };
}

#endif	/* DATA_H */

