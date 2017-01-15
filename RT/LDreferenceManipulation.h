/*******************************************************************************
 *
 * File Name: LDreferenceManipulation.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a5g 01-Nov-2011
 *
 *******************************************************************************/


#ifndef HEADER_LD_REFERENCE_MANIPULATION
#define HEADER_LD_REFERENCE_MANIPULATION

#include "LDreferenceClass.h"

#define DAT_FILE_GENERIC_MAX_SIZE (100000000)		//100MB - the maximum size of any ldraw .DAT/.LDR file

/*currently shared routines*/

#define SPRITE_HEADER_NAME "0 Start Sprites"
#define SPRITE_TRAILER_NAME "0 End Sprites"

#define CHAR_SPACE ' '
#define CHAR_NEWLINE '\n'

/*
#ifdef USE_RT
	#define FILE_FLOAT_PRECISION "%0.2f"
#else
	#define FILE_FLOAT_PRECISION "%0.4f"
#endif
*/
#ifdef USE_CS
	#define FILE_FLOAT_PRECISION "%0.4f"
#else
	#define FILE_FLOAT_PRECISION "%0.4f"
#endif

Reference * search1DRefListFindLastReference(Reference * initialReferenceInList);
bool search1DRefListFindRef(Reference * referenceToFind, Reference * initialReferenceInList);		//not currently used
bool search1DRefListNameAndColourFindRef(Reference * referenceToFind, Reference * initialReferenceInList);
bool search1DRefListReplaceRef(Reference * referenceToFind, Reference * referenceToReplaceWith, Reference * initialReferenceInList);	//not currently used
bool search1DRefListNameAndColourReplaceRef(Reference * referenceToFind, Reference * referenceToReplaceWith, Reference * initialReferenceInList);
bool search1DRefListAddReference(Reference * initialReferenceInList, Reference * referenceToAdd);
bool compareReferenceNameAndColour(Reference * reference, string referenceName, int referenceColour);
void copyReferences(Reference * referenceNew, Reference * referenceToCopy, int type);
#ifdef USE_LRRC
void copyReferencesAndSubmodelDetails(Reference * referenceNew, Reference * referenceToCopy, int type);		//not currently used
#endif
bool compareReferences(Reference * reference1, Reference * reference2, int type);


void addNewLineCharacterToString(char * string);
void addSpaceCharacterToString(char * string);
void addArbitraryCharacterToString(char * string, char delimiter);

void convertPositionCoordinatesToString(vec * spriteSceneCoords, char * string);
void convertPositionCoordinatesToStringWithCommaDelimiterPreceeding(vec * spriteSceneCoords, char * string);

bool writeReferencesToFileInefficient(char * fileName, Reference * firstReference);
bool convertReferencesToByteArray(Reference * firstReference, char * fileByteArray, int * fileByteArraySize);

bool writeReferencesToFile(char * fileName, Reference * firstReference);
bool addReferenceToFileObjectInefficient(ofstream * writeFileObject, Reference * reference);
bool addReferenceToFileObject(ofstream * writeFileObject, Reference * currentReference);
	bool convertReferenceToString(Reference * currentReference, char * referenceString);
bool openFileAndCopyDataIntoCurrentFileObject(char * fileToOpenName, ofstream * writeFileObject);

void writeByteArrayToFile(char * fileName, char * fileByteArray, int fileByteArraySize);
bool readFileIntoByteArray(char * fileName, char * fileByteArray, int * fileNumberOfLines, int * fileByteArraySize);
bool readFileIntoString(string fileName, string * fileContentsString, int * fileNumberOfLines, int * fileByteArraySize);
void copyFilesInefficient(char * newFileName, char * fileToCopyName);
void copyFiles(char * newFileName, char * fileToCopyName);

/*sprite routines*/
void convertRotationMatrixToString(mat * rotationMatrix, char * string);
bool findTextInByteArray(char * byteArray, int byteArraySize, char * searchString, int searchStringLength, int * lineNumberOfReference);	//OLD
bool addLinesToByteArray(char * byteArray, char * lineByteArray, int * byteArraySize, int lineByteArraySize, int lineNumberToAdd);	//OLD
bool replaceLinesInByteArray(char * byteArray, char * lineByteArray, int * byteArraySize, int lineByteArraySize, int lineNumberToReplace, int numberOfLinesToReplace);	//OLD


bool addSpriteReferenceListToSceneFile(char * sceneFileName, char * sceneFileNameWithSprites, Reference * firstSpriteInReferenceList, int spriteListByteArrayLines);

bool write2DReferenceListCollapsedTo1DToFile(char * fileName, Reference * firstReference);
	bool write2DReferencesLayerToFileObject(ofstream * writeFileObject, Reference * firstReferenceInLayer);

bool joinReferenceLists(Reference * initialReferenceInMainList, Reference * initialReferenceInAdditionalList);

#endif
