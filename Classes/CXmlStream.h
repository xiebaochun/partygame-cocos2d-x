#ifndef __CXMLSTREAM_H__
#define __CXMLSTREAM_H__

#include "cocos2d.h"

USING_NS_CC;

class CXmlStream
{
private:
	CCDictionary* m_dictionary;
public:
	CXmlStream(const char* dicFileName);
	~CXmlStream();
	const char* GetStringByKey(const char* keyword);

	static const char* GetStringByKeyFromFile(const char* dicFilename, const char* keyword);
};

#endif