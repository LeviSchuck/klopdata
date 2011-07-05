/* 
 * File:   data.h
 * Author: kloplop321
 *
 * Created on June 28, 2011, 12:56 PM
 */
/*!
 * \mainpage
 * \section usage Basic Usage
 * In order to use this static library, you need to compile first using make.
 * You may also include the sources directly into your project and use them that
 * way. 
 * \subsection basic_info Information
 * In order to use the data class, you need to ensure that your compilation 
 * creates a data.o or data.obj, depending on your setup. Next, to use it in 
 * your code, you need to include the data.h included. 
 * The data class does NOT depend on external libraries. 
 * 
 * \subsection syntax_example Example
 * Using a list:
 * \code
 * klop::Data data;//Note: Do not use () if you plan to init with null data
 * data.toList();
 * data.addChild(klop::Data(42));
 * printf("Forty Two is %d\n",data[0].asInt());
 * \endcode
 * Using keys
 * \code
 * klop::Data data;
 * data.toAssoc();
 * data.addChild("F2",klop::Data(42));
 * printf("Forty Two is %d\n",data["F2"].asInt());
 * \endcode
 * Compounding nodes
 * \code
 * klop::Data data;
 * data.toAssoc();
 * klop::Data data2;
 * data2.toList();
 * data2.addChild(klop::Data(42));
 * data2.addChild(klop::Data("Forty Two as well"));
 * data.addChild("F2",data2);
 * printf("Forty Two is %d\n",data["F2"][0].asInt());
 * printf("Forty Two is %s\n",data["F2"][1].asString());
 * \endcode
 * \section license License
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
/*! \file data.h
 * \author Kloplop321
 * \date June 2011
 * \brief The header file that contains the klop::Data class
 * This header file describes the namespace of klop, klop::kinds(which contains
 * several enums) and the class klop::Data.
 * 
 */

#ifndef DATA_H
#define	DATA_H
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <list>

/*! \brief The klop namespace holds general things made by Kloplop321
 */
namespace klop {
    /*! \brief the kinds namespace will hold enums to avoid name collision
     */
    namespace kinds {
        /*! \brief DataType is used to define the data within the klop::Data 
         * class
         */
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
        /*! \brief ArrayType is to specify if the Data object is associative 
         * or by index
         */
        enum ArrayType {
            byNothing = 0,
            byIndex,
            byAssociation//Not an array
        };
    }
    class dataRW;//This is put here so we can be friendly later.
    /*! \class Data
     * \brief Data is a node based information storage class which should be 
     * easily dumped to a file, or created from a file
     * 
     * Data is created to allow easy access to the information within by 
     * means of nodes. For example, you may access a data object by something 
     * like dataInstance["key"]["subkey"][3].asDouble(); Note that 
     * dataInstance["key"] is a data object, which looks in its children for 
     * subkey, which then is a Data object which holds its information 
     * klop::kinds::byIndex and retrieves the data it holds as a double(meaning 
     * it was originally numeric. This does not support taking a string and 
     * converting to a number. The opposite however is possible and is 
     * implemented.
     * \date June 2011
     * \author Kloplop321
     */
    class Data {
    public:
        //typedef std::vector<std::string> Members;
        /**Data::ObjectValues refers to an associative array using a map*/
        typedef std::map<std::string, Data*> ObjectValues;
        /**Data::ObjectList refers to an indexed array using a map*/
        typedef std::map<unsigned long int, Data*> ObjectList;
        /**Data::list_iterator is the type for the Data::ObjectList iterator*/
        typedef ObjectList::iterator list_iterator;
        //typedef ObjectList::const_iterator list_const_iterator;
        /**Data::map_iterator is the type for the Data::ObjectValues iterator*/
        typedef ObjectValues::iterator map_iterator;
        //typedef ObjectValues::const_iterator map_const_iterator;
        /**Holds null data. Suggested to use this and then convert to an array 
         * type*/
        Data();//This is null.
        /*Starting Numbers*/
        /**Data can take normal integers*/
        Data(const int);
        /**Data can take long integers*/
        Data(const long int);
        /**Data can take unsigned integers*/
        Data(const unsigned int);
        /**Data can take unsigned long integers*/
        Data(const unsigned long int);
        /**Data can take real numbers*/
        Data(const double);
        /*Ending numbers*/
        /**Data can hold boolean values*/
        Data(const bool);
        /**Data can hold c strings, though it is stored as a std::string*/
        Data(const char*);
        /**Data can hold normal strings*/
        Data(const std::string &val);
        /**Data can take another Data object by reference and clone it, along 
         * with its children if it has any*/
        Data(const Data& data);
        /**Data can take another Data object by pointer and clone it, along with
         * its children*/
        Data(const Data* data);

        //Time for operators
        /** This returns true when the data within is not kinds::nullData*/
        const bool operator !() const;//Can't seem to get this to work.
        /** This compares only numerical and string kinds::dataType.*/
        const bool operator <(const Data&) const;
        /** This compares only numerical and string kinds::dataType.*/
        const bool operator <=(const Data&) const;
        /** This compares only numerical and string kinds::dataType.*/
        const bool operator >=(const Data&) const;
        /** This compares only numerical and string kinds::dataType.*/
        const bool operator >(const Data&) const;
        /** This compares numerical and strings, It also checks if the pointers
         * are the same*/
        const bool operator ==(const Data&) const;
        /** This compares numerical and strings, It also checks if the pointers
         * are different*/
        const bool operator !=(const Data& that) const;
        /** \brief compares this with that. 
         * \param that The other Data object to compare to.
         * \return an int that specifies the distance from this Data to the 
         * parameter.
         * Data::compare checks the differences between this value, and the
         * parameter's value, if they are moreData, we don't have a means to
         * currently compare, so it returns -1. The same for nullData.
         * 
         */
        int compare(const Data* that) const;
        /*!
         * Example of what the int index would be used for
         * \code
         * <list id="happy">
         *      <item>blah</item>
         *      <item>another</item>
         * </list>
         * \endcode
         * This does not necessarily mean duplication, but multiple entries.
         * so, it would be accessed like root["happy"][0] for blah.
         */
        Data& operator[](unsigned long int index);
        //Data& operator[](const char* key);
        /*! Example of what the string key  would be used for
         * \code
         * <physics>
         *      <mass type="float">40.0</mass>
         * </physics>
         * \endcode
         * So you would access this like root["physics"]["mass"].asDouble();
         * 
         */
        Data& operator[](const std::string &key);


        
        /*! This function provides the value represented as a string.
         * 
         * \return char* C String, which is basically the Data::asString()
         * .c_str();
         */
        const char* asCString() const;
        /*! This function provides the value represented as a string.
         * 
         * \return std::string The data represented as a string.
         * Will return [NULL] when null data is within.
         * Will return [DATA] when it is just an array of data
         * Will return the number as a string, thanks to std::stringstream
         * Will return the string data as normal
         */
        const std::string asString() const;
        /*! This function will try to return an int value if the data is 
         * numeric.
         * 
         * \note This will cause an assertion failure if the data is not 
         * numeric.
         * 
         * \return int value of Data
         */
        const int asInt() const;
        /*! This function will try to return a long int value if the data is 
         * numeric.
         * 
         * \note This will cause an assertion failure if the data is not 
         * numeric.
         * 
         * \return long int value of Data
         */
        const long int asLInt() const;
        /*! This function will try to return an unsigned int value if the data
         * is numeric.
         * 
         * \note This will cause an assertion failure if the data is not 
         * numeric.
         * 
         * \return unsigned int value of Data
         */
        const unsigned int asUInt() const;
        /*! This function will try to return an unsigned long int value if the 
         * data is numeric.
         * 
         * \note This will cause an assertion failure if the data is not 
         * numeric.
         * 
         * \return unsigned long int value of Data
         */
        const unsigned long int asULInt() const;
        /*! This function will try to return an double value if the data is 
         * numeric.
         * 
         * \note This will cause an assertion failure if the data is not 
         * numeric.
         * 
         * \return double value of Data
         */
        const double asDouble() const;
        
        /*!
         * \return bool is this dataType nullData?
         */
        bool isNull() const;
        /*!
         * \return bool is this dataType boolData?
         */
        bool isBool() const;
        /*!
         * \return bool is this dataType intData?
         */
        bool isInt() const;
        /*!
         * \return bool is this dataType uintData?
         */
        bool isUInt() const;
        /*!
         * \return bool is this dataType lintData?
         */
        bool isLInt() const;
        /*!
         * \return bool is this dataType ulintData?
         */
        bool isULInt() const;
        /*!
         * \return bool is this dataType stringData?
         */
        bool isString() const;
        /*!
         * \return bool is this dataType moreData?
         */
        bool isData() const;
        /*!
         * \return bool is this dataType doubleData?
         */
        bool isDouble() const;
        /*!
         * \return bool is this dataType numerical?
         * Will return true if intData, uintData, lintData, ulintData, 
         * or doubleData
         */
        bool isNumeric() const;
        /*!
         * \return bool does this[parameter] exist?
         */
        bool isMember(const std::string) const;
        /*!
         * \return bool does this[index] exist?
         */
        bool isMember(unsigned long int index);

        /*!
         * \return unsigned long int how many items are in the array
         */
        unsigned long int size() const;
        /*!
         * \return bool is the size 0
         */
        bool isEmpty() const;
        /*!
         * This function cleanly removes all items in the Data tree 
         * and subtrees
         */
        void clear();
        
        /*!
         * \return kinds::DataType what type this Data is.
         * Example: nullData, stringData, etc.
         */
        const kinds::DataType dataType() const;
        /*!
         * \return  kinds::ArrayType type of array, associative or indexed
         * Results are kinds::byNothing, kinds::byAssociation, kinds::byIndex
         */
        const kinds::ArrayType arrayType() const;
        /**This function will reset the entire Data structure. It will then
         be set to nullData*/
        void reset();
        
        /*! Adds a child if the Data is set to a list.
         * 
         * \param data the child to add
         * \note Will have an assertion failure if this is not set to list mode.
         */
        void addChild(Data* data);
        /*! Adds a child to the Data if it is set to an Associative array
         * 
         * \param key the key by which it can later be retrieved by
         * \param data The child to add
         * \note Will have an assertion failure if it is not set to an
         * associative mode
         */
        void addChild(std::string key, Data* data);
        /*! Adds a child to the Data if it is set to an Associative array
         * 
         * \param data The child to add
         * \note Will have an assertion failure if it is not set to list mode
         */
        void addChild(const Data& data);
        /*! Adds a child to the Data if it is set to an Associative array
         * 
         * \param key the key by which it can later be retrieved by
         * \param data The child to add
         * \note Will have an assertion failure if it is not set to list
         */
        void addChild(std::string,const Data& data);
        /*! Converts this data structure to an indexed array. 
          * It will reset the data if any exist.
          * \note if it is already a list, then this will do nothing. You must 
          * use clear if you wish to have a clean list.
          */
        void toList();//Convert so we are moreData and byIndex
         /*! Converts this data structure to an associative array. 
          * It will reset the data if any exist.
          * \note if it is already a list, then this will do nothing. You must 
          * use clear if you wish to have a clean map.
          */
        void toAssoc();//Convert so we are moreData and 
        /*!
         * \return a list_iterator so that you can sorta use STL style 
         * incrementing
         */
        list_iterator list_begin();
        /*!
         * \return a list_iterator so that you can sorta use STL style 
         * incrementing
         * \note This is the end. I don't know why, but you can only do !=, not
         * <= list end.
         */
        list_iterator list_end();
        //list_const_iterator list_const_begin();
        //list_const_iterator list_const_end();
        /*!
         * \return a map_iterator so that you can sorta use STL style 
         * incrementing
         */
        map_iterator map_begin();
        /*!
         * \return a map_iterator so that you can sorta use STL style 
         * incrementing
         * \note This is the end. I don't know why, but you can only do !=, not
         * <= map end.
         */
        map_iterator map_end();
        
        //map_const_iterator map_const_begin();
        //map_const_iterator map_const_end();
        
        
        virtual ~Data();
        //void testSelf();
        friend class dataRW;
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
        
        void setArrayType(kinds::ArrayType type);
        const int numDataToInt() const;
        const bool numDataToBool() const;
        const double numDataToDouble() const;
        const long int numDataToLInt() const;
        const unsigned int numDataToUInt() const;
        const unsigned long int numDataToULInt() const;
       
        std::string stringData;
    };
}

#endif	/* DATA_H */

