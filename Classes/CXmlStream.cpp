#include "CXmlStream.h"


CXmlStream::CXmlStream(const char* dicFilename)
{
	this->m_dictionary = CCDictionary::createWithContentsOfFile(dicFilename);
}

CXmlStream::~CXmlStream()
{

}

const char* CXmlStream::GetStringByKey(const char* keyword)
{
	//return ((CCString*)(this->m_dictionary->objectForKey(keyword)))->m_sString.c_str();
	return ((CCString*)(this->m_dictionary->valueForKey(keyword)))->getCString();
}

const char* CXmlStream::GetStringByKeyFromFile(const char* dicFilename, const char* keyword)
{
	CCDictionary *dictionary = CCDictionary::createWithContentsOfFile(dicFilename);
	//return ((CCString*)dictionary->objectForKey(keyword))->m_sString.c_str();
	return ((CCString*)(dictionary->valueForKey(keyword)))->getCString();
}