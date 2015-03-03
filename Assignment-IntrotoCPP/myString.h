//#pragma once
#ifndef _MYSTRING_H
#define _MYSTRING_H

//Max char array size
const int MAX_CHAR_ARRAY = 1024;

class myString
{
public:
	void ReadFromConsole();

	void WriteToConsole();

	int Length();

	char CharacterAt(int);

	bool EqualTo(char*);

	void Append(char*);

	void Prepend(char*);

	char* CStr();

	void ToLower();

	void ToUpper();

	int Find(char*);

	int Find(int, char*);

	void Replace(char*, char*);

	void TestFunction();

private:
	//Character array data
	char charArray[MAX_CHAR_ARRAY];

};

#endif