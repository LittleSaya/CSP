#ifndef _SIMPLEJSONOBJECT_
#define _SIMPLEJSONOBJECT_
#include <string>
#include <list>
#include <iostream>
#include <cstdlib>

class SimpleJSONObject;

// define the range of SimpleJSONObject::type
enum
{
	LST_T = 0,	// the value of this object is a list of other objects
	STR_T = 2,	// the value of this object is a string
	UDE_T = 9,	// this object is undefined, used when there is an error
};

typedef std::string *PString_t;
typedef std::list<SimpleJSONObject> *PList_t;

class SimpleJSONObject
{
private:
	int type;			// the type of this object
	std::string name;	// the name of this object
	void *valuePointer;	// the value of this object
	// if type == LST_T, the valuePointer will be reinterpreted as a PList_t
	// if type == STR_T, the valuePointer will be reinterpreted as a PString_t
	
public:
	// build a json object without a valuePointer
	SimpleJSONObject(const int p_type, const std::string &p_name): type(p_type), name(p_name), valuePointer(NULL)
	{ }
	
	// build a json object with a valuePointer
	SimpleJSONObject(const int p_type, const std::string &p_name, void *p_valuePointer): type(p_type), name(p_name), valuePointer(p_valuePointer)
	{ }
	
	// build a json object from an existing json object (shallow copy)
	SimpleJSONObject(const SimpleJSONObject &p_obj): type(p_obj.type), name(p_obj.name), valuePointer(p_obj.valuePointer)
	{ }
		
	// build a json object from a raw string
	// todo optimize
	SimpleJSONObject(const std::string &raw, const size_t begIdx): type(UDE_T), name(""), valuePointer(NULL)
	{
		valuePointer = buildFromString(raw, begIdx);
		if (valuePointer != NULL)
		{ type = LST_T; }
	}
	
	// deconstruct
	~SimpleJSONObject()
	{
		if (type == LST_T)
		{ delete (PList_t)valuePointer; }
		else if (type == STR_T)
		{ delete (PString_t)valuePointer; }
		else
		{
			std::cout << "undefined SimpleJSONObject::type (" << type << ") in SimpleJSONObject::~SimpleJSONObject()" << std::endl;
			std::exit(-1);
		}
	}
public:
	// print this object
	void print() const;
	
	int getType() const
	{ return type; }
	
	void setType(int p_type)
	{ type = (p_type >= LST_T && p_type <= STR_T ? p_type : UDE_T); }
	
	const std::string &getName() const
	{ return name; }
	
	void setName(const std::string &p_name)
	{ name = (p_name.size() == 0 ? "null" : p_name); }
	
	const void *getValuePointer() const
	{ return valuePointer; }
	
	void *getValuePointer()
	{ return valuePointer; }
	
	void setValuePointer(void *p_valuePointer)
	{ valuePointer = p_valuePointer; }
	
	SimpleJSONObject *query(const std::string &p_name);
private:
	// init the process
	// para:
	//		begIdx: '{'
	// ret:
	//		NULL if error
	PList_t buildFromString(const std::string &raw, const size_t begIdx);
	
	// create an object list
	//		begIdx[in]: the begin '{'
	//		endIdx[out]: the end '}'
	PList_t createListValue(const std::string &raw, const size_t begIdx, size_t *endIdx);
	
	// create a name
	// para:
	//		begIdx[in]: the begin '\"'
	//		endIdx[out]: the end '\"'
	std::string createName(const std::string &raw, const size_t begIdx, size_t *endIdx);
	
	// create a string value
	// para:
	//		begIdx[in]: the begin '\"'
	//		endIdx[out]: the end '\"'
	PString_t createStringValue(const std::string &raw, const size_t begIdx, size_t *endIdx);
	
	// move the iter forward until it stands on a non-blank char or meets the end (iter == str.size())
	// ret:
	//		return the char on str[iter] if it doesn't meet the end
	//		otherwise return ' '
	char moveToNextChar(const std::string &str, size_t &iter);
	
	void print_internal(const SimpleJSONObject &obj, const int indent, bool last) const;
	
	void printIndent(const int indent) const;
};

#endif
