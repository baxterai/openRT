/*******************************************************************************
 *
 * File Name: XMLParserClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: XML Functions
 * Project Version: 3a5g 01-Nov-2011
 *
 *******************************************************************************/



#ifndef HEADER_XML_PARSER_CLASS
#define HEADER_XML_PARSER_CLASS


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;

#include "SHAREDglobalDefs.h"

#ifdef USE_GIA
	/*yet untested without GIA;
	#define XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_INSIDE_ATTRIBUTE_VALUE
	#define XML_PARSER_DO_NOT_ALLOW_TABS_OR_NEWLINES_WITHIN_TAG_VALUE	
	*/
#else
	#define XML_PARSER_DO_NOT_ALLOW_CHAR_TAG_END_SLASH_INSIDE_ATTRIBUTE_VALUE
	#define XML_PARSER_DO_NOT_ALLOW_TABS_OR_NEWLINES_WITHIN_TAG_VALUE
#endif

#define XML_FILE_MAX_SIZE (100000000)		//100MB


#ifndef XML_PARSER_ATTRIBUTE_CLASS
#define XML_PARSER_ATTRIBUTE_CLASS


class XMLParserAttribute
{
private:
	/*There are currently no private attributes of this class*/
public:

	XMLParserAttribute(void); // constructor
	~XMLParserAttribute();	// and destructor.

	string name;
	string value;

	XMLParserAttribute * nextAttribute;


};

#endif




#ifndef XML_PARSER_TAG_CLASS
#define XML_PARSER_TAG_CLASS

class XMLParserTag
{
private:
	/*There are currently no private attributes of this class*/
public:

	XMLParserTag(void); // constructor
	~XMLParserTag();	// and destructor.

	string name;
	string value;

	XMLParserTag * nextTag;
	XMLParserTag * firstLowerLevelTag;

	XMLParserAttribute * firstAttribute;
	XMLParserAttribute * currentAttribute;	//temporary variable used for attribute list creation

};

#endif



bool readXMLFile(string xmlFileName, XMLParserTag * firstTagInXMLFile);
bool parseTagOpen(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer);
	bool parseTagName(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer);
		bool parseTagAttributeName(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer);
			bool parseTagAttributeValue(ifstream * parseFileObject, XMLParserTag * currentTag, string parentTagName, bool isASubTag, int treeLayer);
		bool parseTagValueAssumingExistenceOfSubtabsAndClose(ifstream * parseFileObject, XMLParserTag * tag, XMLParserTag * subTag, string tagName, int treeLayer);
		bool parseTagComment(ifstream * parseFileObject);

//Low Level
bool isBlankChar(ifstream * parseFileObject, char c);
bool isBlankCharTabOrNewLine(ifstream * parseFileObject, char c);
void throwGenericXMLParseError();



bool writeXMLFileInefficient(string xmlFileName, XMLParserTag * firstTagInXMLFile);
bool writeXMLFile(string xmlFileName, XMLParserTag * firstTagInXMLFile);
	bool addTagLayerToFileObject(XMLParserTag * firstTagInCurrentLayer, ofstream * writeFileObject, int treeLayer);
		void incrementLineAndAddTabsToFileObject(ofstream * writeFileObject, int treeLayer);
		void addTabsToFileObject(ofstream * writeFileObject, int treeLayer);
		void writeStringToFileObject(string s, ofstream * writeFileObject);

	bool addTagLayerToByteArrayInefficient(XMLParserTag * firstTagInCurrentLayer, char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition, int treeLayer);
		void incrementLineAndAddTabsToByteArrayInefficient(char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition, int treeLayer);
		void addTabsToByteArrayInefficient(char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition, int treeLayer);
		void writeStringToByteArrayInefficient(string s, char * XMLFileByteArray, long * XMLFileByteArrayCurrentPosition);
	void writeByteArrayToFile(const char * fileName, char * fileByteArray, int fileByteArraySize);

#endif
