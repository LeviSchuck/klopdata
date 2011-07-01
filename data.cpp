/* 
 * File:   data.cpp
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

#include "data.h"
#include <assert.h>
#include <stdio.h>
#include <sstream>
namespace klop {
    //From jsoncpp public domain

    //Main class--------------------------------------------
    Data::Data(){
        //we are null
        this->myType = kinds::nullData;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const int i){
        this->myType = kinds::intData;
        this->numericData.i = i;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const long int li){
        this->myType = kinds::lintData;
        this->numericData.li = li;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const unsigned int ui){
        this->myType = kinds::uintData;
        this->numericData.ui = ui;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const unsigned long int uli){
        this->myType = kinds::ulintData;
        this->numericData.uli = uli;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const double d){
        this->myType = kinds::doubleData;
        this->numericData.d = d;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const bool b){
        this->myType = kinds::boolData;
        this->numericData.b = b;
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const char* cstr){
        this->myType = kinds::stringData;
        this->stringData = std::string(cstr);
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const std::string& str){
        this->myType = kinds::stringData;
        this->stringData = std::string(str);
        this->myArrayType = kinds::byNothing;
    }
    Data::Data(const Data& data){
        //printf("Copying Data.\n");
        this->myType = data.myType;
        this->myArrayType = data.myArrayType;
        this->numericData = data.numericData;
        this->stringData = data.stringData;
        if(data.myType == kinds::moreData){
            //we need to copy the tree.
            if(data.myArrayType == kinds::byAssociation){
                //Iterate through
                int x = 0;
                for(ObjectValues::const_iterator Iterator = data.myMap.begin(); 
                Iterator != data.myMap.end(); ++Iterator){
                    const Data* Object = Iterator->second;
                    /*printf("Copying object[%s,%d] with represented as: %s\n", 
                            Iterator->first.c_str(),x, data.asString().c_str());//*/
                    Data* newData = new Data(Object);
                    //printf("Old size: %lu; New size: %lu\n", Object->size(), newData->size());
                    //printf("New type: %d\n", newData->myType);
                    this->addChild(Iterator->first, newData);
                    x++;
                }
            }
            if(data.myArrayType == kinds::byIndex){
                for(ObjectList::const_iterator Iterator = data.myList.begin(); 
                Iterator != data.myList.end(); ++Iterator){
                    const Data* Object = Iterator->second;
                    /*printf("Copying object[%d] with represented as: %s\n", 
                            Iterator->first, Object->asCString());//*/
                    Data* newData = new Data(Object);
                    this->addChild(newData);
                }
            }
        }
    }
    Data::Data(const Data* data){
        //printf("Copying Data.\n");
        this->myType = data->myType;
        this->myArrayType = data->myArrayType;
        this->numericData = data->numericData;
        this->stringData = data->stringData;
        if(data->myType == kinds::moreData){
            //we need to copy the tree.
            if(data->myArrayType == kinds::byAssociation){
                //Iterate through
                int x = 0;
                for(ObjectValues::const_iterator Iterator = data->myMap.begin(); 
                Iterator != data->myMap.end(); ++Iterator){
                    const Data* Object = Iterator->second;
                    /*printf("Copying object[%s,%d] with represented as: %s\n", 
                            Iterator->first.c_str(),x, data->asString().c_str());//*/
                    Data* newData = new Data(Object);
                    //printf("Old size: %lu; New size: %lu\n", Object->size(), newData->size());
                    //printf("New type: %d\n", newData->myType);
                    this->addChild(Iterator->first, newData);
                    x++;
                }
            }
            if(data->myArrayType == kinds::byIndex){
                for(ObjectList::const_iterator Iterator = data->myList.begin(); 
                Iterator != data->myList.end(); ++Iterator){
                    const Data* Object = Iterator->second;
                    /*printf("Copying object[%d] with represented as: %s\n", 
                            Iterator->first, Object->asCString());//*/
                    Data* newData = new Data(Object);
                    this->addChild(newData);
                }
            }
        }
    }
    
    
    //Time for comparison!
    const bool Data::operator !() const{
        return this->myType == kinds::nullData;
    }
    const bool Data::operator <(const Data& data) const{
       
        if(data.isNumeric() && this->isNumeric()){
            switch(data.myType){
                case kinds::intData:{
                    return this->numDataToInt() < data.numericData.i;
                }break;
                case kinds::boolData: {
                    return this->numDataToBool() < data.numericData.b;
                }break;
                case kinds::doubleData: {
                    return this->numDataToDouble() < data.numericData.d;
                }break;
                case kinds::lintData: {
                    return this->numDataToLInt() < data.numericData.li;
                }break;
                case kinds::uintData: {
                    return this->numDataToUInt() < data.numericData.ui;
                }break;
                case kinds::ulintData: {
                    return this->numDataToULInt() < data.numericData.uli;
                }break;
                default: break;//we are not numeric.
            }
        }
        //Rule: return false when the types are not the same
        //We are not going to equate these kinds of things.
        //So, we are dealing with more data, null or a string.
        //If we are dealing with "more data" I can't compare them.
        //This is only to compare the values.
        //Which leaves null and string.
        if(this->myType != data.myType)
            return false;
        /*
       //* The following are fine with the last return at the end of the method.
        if(this->myType == kinds::moreData)
            return false;
        if(this->myType == kinds::nullData)
            return false;
         */
        //Then we should only have string left.
        if(this->myType == kinds::stringData){
            return this->stringData.compare(data.stringData) < 0;
        }
        if(this->myType == kinds::nullData)
            return true;//rule: null < *
        //However, for safety.
        return false;
    }
    const bool Data::operator <=(const Data& data) const{
       
        if(data.isNumeric() && this->isNumeric()){
            switch(data.myType){
                case kinds::intData:{
                    return this->numDataToInt() <= data.numericData.i;
                }break;
                case kinds::boolData: {
                    return this->numDataToBool() <= data.numericData.b;
                }break;
                case kinds::doubleData: {
                    return this->numDataToDouble() <= data.numericData.d;
                }break;
                case kinds::lintData: {
                    return this->numDataToLInt() <= data.numericData.li;
                }break;
                case kinds::uintData: {
                    return this->numDataToUInt() <= data.numericData.ui;
                }break;
                case kinds::ulintData: {
                    return this->numDataToULInt() <= data.numericData.uli;
                }break;
                default: break;//we are not numeric.
            }
        }
        //Rule: return false when the types are not the same
        //We are not going to equate these kinds of things.
        //So, we are dealing with more data, null or a string.
        //If we are dealing with "more data" I can't compare them.
        //This is only to compare the values.
        //Which leaves null and string.
        if(this->myType != data.myType)
            return false;
        /*
       //* The following are fine with the last return at the end of the method.
        if(this->myType == kinds::moreData)
            return false;
        if(this->myType == kinds::nullData)
            return false;
         */
        //Then we should only have string left.
        if(this->myType == kinds::stringData){
            return this->stringData.compare(data.stringData) <= 0;
        }
        //However, for safety.
        return false;
    }
    const bool Data::operator >=(const Data& data) const{
       
        if(data.isNumeric() && this->isNumeric()){
            switch(data.myType){
                case kinds::intData:{
                    return this->numDataToInt() >= data.numericData.i;
                }break;
                case kinds::boolData: {
                    return this->numDataToBool() >= data.numericData.b;
                }break;
                case kinds::doubleData: {
                    return this->numDataToDouble() >= data.numericData.d;
                }break;
                case kinds::lintData: {
                    return this->numDataToLInt() >= data.numericData.li;
                }break;
                case kinds::uintData: {
                    return this->numDataToUInt() >= data.numericData.ui;
                }break;
                case kinds::ulintData: {
                    return this->numDataToULInt() >= data.numericData.uli;
                }break;
                default: break;//we are not numeric.
            }
        }
        //Rule: return false when the types are not the same
        //We are not going to equate these kinds of things.
        //So, we are dealing with more data, null or a string.
        //If we are dealing with "more data" I can't compare them.
        //This is only to compare the values.
        //Which leaves null and string.
        if(this->myType != data.myType)
            return false;
        /*
       //* The following are fine with the last return at the end of the method.
        if(this->myType == kinds::moreData)
            return false;
        if(this->myType == kinds::nullData)
            return false;
         */
        //Then we should only have string left.
        if(this->myType == kinds::stringData){
            return this->stringData.compare(data.stringData) >= 0;
        }
        //However, for safety.
        return false;
    }  
    const bool Data::operator >(const Data& data) const{
       
        if(data.isNumeric() && this->isNumeric()){
            switch(data.myType){
                case kinds::intData:{
                    return this->numDataToInt() > data.numericData.i;
                }break;
                case kinds::boolData: {
                    return this->numDataToBool() > data.numericData.b;
                }break;
                case kinds::doubleData: {
                    return this->numDataToDouble() > data.numericData.d;
                }break;
                case kinds::lintData: {
                    return this->numDataToLInt() > data.numericData.li;
                }break;
                case kinds::uintData: {
                    return this->numDataToUInt() > data.numericData.ui;
                }break;
                case kinds::ulintData: {
                    return this->numDataToULInt() > data.numericData.uli;
                }break;
                default: break;//we are not numeric.
            }
        }
        //Rule: return false when the types are not the same
        //We are not going to equate these kinds of things.
        //So, we are dealing with more data, null or a string.
        //If we are dealing with "more data" I can't compare them.
        //This is only to compare the values.
        //Which leaves null and string.
        if(this->myType != data.myType)
            return false;
        /*
       //* The following are fine with the last return at the end of the method.
        if(this->myType == kinds::moreData)
            return false;
        if(this->myType == kinds::nullData)
            return false;
         */
        //Then we should only have string left.
        if(this->myType == kinds::stringData){
            return this->stringData.compare(data.stringData) > 0;
        }
        //However, for safety.
        return false;
    }
    const bool Data::operator ==(const Data& data) const{
        //lets handle numerical data initially, and then handle the rest.
        switch(data.myType){
            case kinds::intData:{
                return data.numericData.i == this->numDataToInt();
            }break;
            case kinds::boolData: {
                return data.numericData.b == this->numDataToBool();
            }break;
            case kinds::doubleData: {
                return data.numericData.d == this->numDataToDouble();
            }break;
            case kinds::lintData: {
                return data.numericData.li == this->numDataToLInt();
            }break;
            case kinds::uintData: {
                return data.numericData.ui == this->numDataToUInt();
            }break;
            case kinds::ulintData: {
                return data.numericData.uli == this->numDataToULInt();
            }break;
            default: break;
        }
        if(data.myType != this->myType){
            return false;
        }
        if(data.myType == kinds::stringData){
            //If the strings are the same, then the comparison will return 0.
            //When it returns 0, and 0 == 0, thus true.
            return data.stringData.compare(this->stringData) == 0;
        }
        //We must either be more Data or boolean at this point.
        if(data.myType == kinds::boolData){
            return this->numericData.b == data.numericData.b;
        }  
        //So, at this point, we must be more data, or null.
        //TODO: detect if the more data's are the same.
        if(data.myType == kinds::moreData){
            return this == &data;
        }
        
        //Should only hit if null.
        return false;
    }
    const bool Data::operator !=(const Data& data) const{
        //lets handle numerical data initially, and then handle the rest.
        switch(data.myType){
            case kinds::intData:{
                return data.numericData.i != this->numDataToInt();
            }break;
            case kinds::boolData: {
                return data.numericData.b != this->numDataToBool();
            }break;
            case kinds::doubleData: {
                return data.numericData.d != this->numDataToDouble();
            }break;
            case kinds::lintData: {
                return data.numericData.li != this->numDataToLInt();
            }break;
            case kinds::uintData: {
                return data.numericData.ui != this->numDataToUInt();
            }break;
            case kinds::ulintData: {
                return data.numericData.uli != this->numDataToULInt();
            }break;
            default: break;
        }
        if(data.myType != this->myType){
            return true;
        }
        if(data.myType == kinds::stringData){
            //If the strings are the same, then the comparison will return 0.
            //When it returns 0, and 0 == 0, thus true.
            return data.stringData.compare(this->stringData) != 0;
        }
        //We must either be more Data or boolean at this point.
        if(data.myType == kinds::boolData){
            return this->numericData.b != data.numericData.b;
        }  
        //So, at this point, we must be more data, or null.
        //TODO: detect if the more data's are the same.
        if(data.myType == kinds::moreData){
            return this != &data;
        }
        
        //Should only hit if null.
        return true;
    }
    
    int Data::compare(const Data *data) const{
        if(data->isNumeric() && this->isNumeric()){
            //printf("We are numeric. %d vs %d \n",this->myType, data->myType);
            //printf("We have values. %d vs %d \n",this->numericData.i, data->numericData.i);
            switch(data->myType){
                case kinds::intData:{
                    /*printf("Comparing Data, %d - %d = %d\n",
                            this->numDataToInt(), data->numericData.i,
                            this->numDataToInt() - data->numericData.i);*/
                    return this->numDataToInt() - data->numericData.i;
                }break;
                case kinds::boolData: {
                    return this->numDataToBool() - data->numericData.b;
                }break;
                case kinds::doubleData: {
                    /*printf("Comparing Data, %f - %f = %f\n",
                            this->numDataToDouble(), data->numericData.d,
                            this->numDataToDouble() - data->numericData.d);*/
                    return this->numDataToDouble() - data->numericData.d;
                }break;
                case kinds::lintData: {
                    return this->numDataToLInt() - data->numericData.li;
                }break;
                case kinds::uintData: {
                    return this->numDataToUInt() - data->numericData.ui;
                }break;
                case kinds::ulintData: {
                    return this->numDataToULInt() - data->numericData.uli;
                }break;
                default: break;//we are not numeric.
            }
        }
        if(data->myType != this->myType)
            return -1;//we can't compare them.
        //Rule: null < *
        if(data->myType == kinds::nullData)
            return -1;
        //At this point, we only have more data and strings.
        if(data->myType == kinds::moreData)
            return -1;//We can't compare.
        //So, only strings now.
        
        if(data->myType == kinds::stringData){//we still want to be sure we don't have segfaults.
            return this->stringData.compare(data->stringData);
        }
        
        return -1;//can't compare.
    }
    
    Data& Data::operator [](unsigned long int index) {
        assert(this->myArrayType == kinds::byIndex);
        if(index < 0 && index >= this->myList.size()){
            printf("\nFailed assertion, index out of range.\n");
            assert(false);
        }
        //We should be safe now.
        return *this->myList.at(index);
        
    }
    /*Data& Data::operator [](const char* key){
        assert(this->myArrayType == kinds::byAssociation);
        std::string newkey = std::string(key);
        return *this->myMap.at(newkey);
    }*/
    Data& Data::operator [](const std::string& key){
        assert(this->myArrayType == kinds::byAssociation);
        return *this->myMap.at(key);
    }
    
    const char* Data::asCString() const{
        //assert(this->myType != kinds::moreData);
        //If null, we print [NULL]
        return asString().c_str();
    }
    const std::string Data::asString() const{
        //assert(this->myType != kinds::moreData);
        if(this->myType == kinds::moreData)
            return "[DATA]";
        if(this->myType == kinds::stringData)
            return this->stringData;
        /*if(this->myType == kinds::nullData)
            return "[NULL]";*///Lets handle null at the end
        //                      in case we have a logic problem
        //All that's left are numerical data and boolean
        //(we will treat them as a number)
        //Unless of course, string stream does not treat it as a number
        
        if(this->isNumeric()){
            std::stringstream ss;
            switch(this->myType){
                case kinds::intData:{
                    ss << this->numericData.i;
                }break;
                case kinds::boolData: {
                    ss << this->numericData.b;
                }break;
                case kinds::doubleData: {
                    ss << this->numericData.d;
                }break;
                case kinds::lintData: {
                    ss << this->numericData.li;
                }break;
                case kinds::uintData: {
                    ss << this->numericData.ui;
                }break;
                case kinds::ulintData: {
                    ss << this->numericData.uli;
                }break;
                default: break;//we are not numeric.
            }
            return ss.str();
        }
        
        return "[NULL]";
    }
    const int Data::asInt() const{
        assert(this->isNumeric());
        if(this->myType == kinds::doubleData)
            return (int)this->numericData.d;
        return this->numericData.i;
    }
    const long int Data::asLInt() const{
        assert(this->isNumeric());
        if(this->myType == kinds::doubleData)
            return (long int)this->numericData.d;
        return this->numericData.li;
    }
    const unsigned int Data::asUInt() const{
        assert(this->isNumeric());
        if(this->myType == kinds::doubleData)
            return (unsigned int)this->numericData.d;
        return this->numericData.ui;
    }
    const unsigned long int Data::asULInt() const{
        assert(this->isNumeric());
        if(this->myType == kinds::doubleData)
            return (unsigned long int)this->numericData.d;
        return this->numericData.uli;
    }
    const double Data::asDouble() const{
        assert(this->isNumeric());
        if(this->myType != kinds::doubleData){
             switch(this->myType){
                case kinds::intData:
                case kinds::boolData:
                    return (double)this->numericData.i;
                case kinds::lintData:
                    return (double)this->numericData.li;
                case kinds::uintData:
                    return (double)this->numericData.ui;
                case kinds::ulintData:
                    return (double)this->numericData.uli;
                default: 
                    break;
            }
        }
        return this->numericData.d;
    }
    
   
    bool Data::isNull() const{
        return this->myType == kinds::nullData;
    }
    bool Data::isBool() const{
        return this->myType == kinds::boolData;
    }
    bool Data::isInt() const{
        return this->myType == kinds::intData;
    }
    bool Data::isUInt() const{
        return this->myType == kinds::uintData;
    }
    bool Data::isLInt() const{
        return this->myType == kinds::lintData;
    }
    bool Data::isULInt() const{
        return this->myType == kinds::ulintData;
    }
    bool Data::isString() const{
        return this->myType == kinds::stringData;
    }
    bool Data::isData() const{
        return this->myType == kinds::moreData;
    }
    bool Data::isDouble() const{
        return this->myType == kinds::doubleData;
    }
    bool Data::isNumeric() const{
        switch(this->myType){
            case kinds::intData:
            case kinds::boolData:
            case kinds::doubleData:
            case kinds::lintData:
            case kinds::uintData:
            case kinds::ulintData:
                return true;
            default: 
                return false;
        }
    }
    bool Data::isMember(const std::string key) const{
        ObjectValues::const_iterator it = this->myMap.find(key);
        return it != this->myMap.end();
    }
    bool Data::isMember(unsigned long int index){
        //index++;
        ObjectList::iterator it = this->myList.find(index);
        return it != this->myList.end();
    }
    
    unsigned long int Data::size() const{
        if(this->myArrayType == kinds::byAssociation){
            return this->myMap.size();
        }else{//We only have 
            return this->myList.size();
        }
    }
    bool Data::isEmpty() const{
        return this->size() == 0;
    }
    void Data::clear() {
        for(ObjectValues::iterator Iterator = this->myMap.begin(); 
                Iterator != this->myMap.end(); ++Iterator){
            Data* Object = Iterator->second;
            Object->clear();
            delete Object;
        }
        for(ObjectList::iterator Iterator = this->myList.begin(); 
                Iterator != this->myList.end(); ++Iterator){
            Data* Object = Iterator->second;
            Object->clear();
            delete Object;
        }
        this->myMap.clear();
        this->myList.clear();
    }
    const kinds::DataType Data::dataType() const{
        return this->myType;
    }
    const kinds::ArrayType Data::arrayType() const{
        return this->myArrayType;
    }
    void Data::setArrayType(kinds::ArrayType type){
        //assert(type >= 0 && type <= kinds::byNothing);//This must be changed
        //if we have other types in the future.
        if(this->myArrayType != type){
            //We are changing our types. We must clear.
            this->clear();
        }
        this->myArrayType = type;
    }
    void Data::reset(){
        this->clear();
        this->numericData.uli = 0;
        this->myArrayType = kinds::byNothing;
        this->stringData = "";
        this->myType = kinds::nullData;
    }
    
    
    const int Data::numDataToInt() const{
        assert(this->isNumeric());
        return this->numericData.i;
    }
    const bool Data::numDataToBool() const{
        assert(this->isNumeric());
        if(this->myType == kinds::boolData){
            return this->numericData.b;
        }
        return this->numericData.uli != 0;
    }
    const double Data::numDataToDouble() const{
        assert(this->isNumeric());
        switch(this->myType){
            case kinds::uintData:
                return (double)this->numericData.ui;
            case kinds::ulintData:
                return (double)this->numericData.uli;
            case kinds::lintData:
                return (double)this->numericData.li;
            default:
                return this->numericData.d;
        }
    }
    const long int Data::numDataToLInt() const{
        assert(this->isNumeric());
        switch(this->myType){
            case kinds::doubleData:
                return (long int)this->numericData.d;
            default: 
                return this->numericData.li;
        }
    }
    const unsigned int Data::numDataToUInt() const{
        assert(this->isNumeric());
        switch(this->myType){
            case kinds::doubleData:
                return (unsigned int)this->numericData.d;
            default: 
                return this->numericData.ui;
        }
    }
    const unsigned long int Data::numDataToULInt() const{
        assert(this->isNumeric());
        switch(this->myType){
            case kinds::doubleData:
                return (unsigned long int)this->numericData.d;
            default: 
                return this->numericData.uli;
        }
    }
    void Data::addChild(unsigned long int index, Data* data){
        assert(this->myType == kinds::moreData &&
                this->myArrayType == kinds::byIndex);
        this->myList.insert(std::pair<unsigned long int, Data*>(index,data));
        
    }
    void Data::addChild(std::string key, Data* data){
        assert(this->myType == kinds::moreData &&
                this->myArrayType == kinds::byAssociation);
        this->myMap.insert(std::pair<std::string, Data*>(key,data));
    }
    void Data::addChild(char* key, Data* data){
        const std::string skey = std::string(key);
        addChild(skey, data);
    }
    void Data::addChild(Data* data){
        this->addChild(this->size(), data);  
    }
    void Data::addChild(std::string key,const Data& data){
        assert(this->myType == kinds::moreData &&
                this->myArrayType == kinds::byAssociation);
        Data* newData = new Data(data);
        this->myMap.insert(std::pair<std::string, Data*>(key,newData));
    }
    void Data::addChild(char* key,const Data& data){
        const std::string skey = std::string(key);
        addChild(skey, data);
    }
    void Data::addChild(const Data& data){
        Data* newData = new Data(data);
        this->addChild(this->size(), newData);  
    }
    void Data::toList(){
        if(this->myType == kinds::moreData && 
                this->myArrayType == kinds::byIndex){
            return;//We already are a list. If you want to clear it, use clear...
        }
        if(this->myType == kinds::moreData && 
                this->myArrayType == kinds::byAssociation){
            this->clear();
        }
        if(this->myType != kinds::moreData){
            this->reset();
        }
        this->myArrayType = kinds::byIndex;
        this->myType = kinds::moreData; 
    }
    void Data::toAssoc(){
        if(this->myType == kinds::moreData && 
                this->myArrayType == kinds::byAssociation){
            return;//We already are a list. If you want to clear it, use clear...
        }
        if(this->myType == kinds::moreData && 
                this->myArrayType == kinds::byIndex){
            this->clear();
        }
        if(this->myType != kinds::moreData){
            this->reset();
        }
        this->myArrayType = kinds::byAssociation;
        this->myType = kinds::moreData; 
    }
    Data::list_iterator Data::list_begin(){
        return this->myList.begin();
    }
    Data::list_iterator Data::list_end(){
        return this->myList.end();
    }
    /*Data::list_const_iterator Data::list_const_begin(){
        return this->myList.begin();
    }
    Data::list_const_iterator Data::list_const_end(){
        return this->myList.end();
    }*/
    
    
    Data::map_iterator Data::map_begin(){
        return this->myMap.begin();
    }
    Data::map_iterator Data::map_end(){
        return this->myMap.end();
    }
    /*Data::map_const_iterator Data::map_const_begin(){
        return this->myMap.begin();
    }
    Data::map_const_iterator Data::map_const_end(){
        return this->myMap.end();
    }*/
    
    Data::~Data() {
        this->clear();
        this->numericData.uli = 0;
        this->stringData = "";
    }

}
