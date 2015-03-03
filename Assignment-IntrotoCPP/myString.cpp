#include <iostream>
#include "myString.h"

using namespace std;

//Gets the input from the console for myString class
void myString::ReadFromConsole()
{
	cin.getline(charArray, MAX_CHAR_ARRAY);
}

//Writes the char array to the console
void myString::WriteToConsole()
{
	cout << charArray;
}

//Gets length of the char array
int myString::Length()
{
	int count = 0;
	for (int i = 0; i < MAX_CHAR_ARRAY; i++)
	{
		if (charArray[i] > NULL && charArray[i] != (char)32)
		{
			count++;
		}
	}
	return count;
}

//Returns the char at position of array
char myString::CharacterAt(int input)
{
	if (input >= 0 && input <= Length())
	{
		return charArray[input];
	}
	else
	{
		return NULL;
	}
}

//Returns true if char contains the same characters as the char array
bool myString::EqualTo(char* input)
{
	if (strcmp(charArray, input) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Adds a string to the end of the char array
void myString::Append(char* input)
{
	int charlength = strlen(charArray);
	for (int i = 0; i < (int)strlen(input); i++)
	{
		if (input[i] != NULL)
		{
			charArray[charlength++] = input[i];
		}
	}

	charArray[charlength++] = NULL;
}

//Adds a string to the begining of the char array
void myString::Prepend(char* input)
{
	int charlength = strlen(input);
	for (int i = 0; i < (int)strlen(charArray); i++)
	{
		if (input[i] != NULL)
		{
			input[charlength++] = charArray[i];
		}
	}

	for (int i = 0; i < MAX_CHAR_ARRAY; i++)
	{
		charArray[i] = input[i];
	}

	charArray[charlength++] = NULL;
}

//Returns the char array to be usable with console( cout << )
char* myString::CStr()
{
	return charArray;
}

//Convert all characters to lowercase
void myString::ToLower()
{
	for (int i = 0; i < Length(); i++)
	{
		if (charArray[i] >= 65 && charArray[i] <= 90)
		{
			charArray[i] += 32;
		}
	}
}

//Convert all characters to uppercase
void myString::ToUpper()
{
	for (int i = 0; i < Length(); i++)
	{
		if (charArray[i] >= 97 && charArray[i] <= 122)
		{
			charArray[i] -= 32;
		}
	}
}

//Returns the position of the char array in the main array
int myString::Find(char* input)
{
	return Find(0, input);
}

//Returns the position of the char array in the main array from the start index
int myString::Find(int startIndex, char* findArray)
{
	bool checker = false;

	for (int i = startIndex; i < (int)strlen(charArray); i++)
	{
		//checks the first iteration of the findArray if equals sets checker true
		if (findArray[0] == charArray[i])
		{
			checker = true;

			int count = i + 1;

			//Loops through findArray and charArray to check if next letter is equal, if not checker equals false.
			for (int j = 1; j < (int)strlen(findArray); j++)
			{
				if (findArray[j] == charArray[count])
				{
					checker = true;
					count++;
				}
				else
				{
					checker = false;
					break;
				}
			}
			if (checker)
			{
				return i;
			}
		}
	}
	return -1;
}

//Replaces all instances of findArray with replaceArray
void myString::Replace(char* findArray, char* replaceArray)
{
	int counter = 0;

	while (counter < (int)strlen(charArray))
	{
		//finds the location of the findArray
		int location = Find(counter, findArray);

		if (location < 0)
		{
			break;
		}

		for (int j = 0; j < (int)strlen(charArray); j++)
		{
			if (j < (int)strlen(replaceArray))
			{
				if (j >= (int)strlen(findArray))
				{
					//Moves the memory location in the char array forward so it doesnt overwrite exisiting memory
					memmove(charArray + (location + j), charArray + (location + j - 1), (int)strlen(charArray));
				}

				//replaces each character of the charArray with the replaceArray each loop
				charArray[location + j] = replaceArray[j];
				counter++;
			}
			else if (j <= (int)strlen(findArray) && j >= (int)strlen(replaceArray))
			{
				//Moves the memory location in the char array if the findArray is bigger than the replaceArray.
				//this makes it so it will replace the whole word instead of leaving the remainder of the findArray
				memmove(charArray + (location + j), charArray + (location + j + (int)strlen(findArray) - (int)strlen(replaceArray)), (int)strlen(charArray));
				break;
			}
			else
			{
				break;
			}
		}
	}
}

//Tests all functions in this function
void myString::TestFunction()
{
	myString word;
	int int_input = 0;
	char char_array_input[MAX_CHAR_ARRAY] = {};
	char char_array_input_2[MAX_CHAR_ARRAY] = {};

	//////////////////////////////////////////////////////////
	////Test ReadFromConsole() & WriteToConsole() function////
	//////////////////////////////////////////////////////////
	cout << "Enter a string to test the ReadFromConsole Function: ";
	word.ReadFromConsole();
	cout << "Test the WriteToConsole Function." << endl;
	system("pause");
	cout << "Result: ";
	word.WriteToConsole();
	cout << endl;

	//////////////////////////////
	////Test Length() function////
	//////////////////////////////
	cout << "Test the Length of the string." << endl;
	system("pause");
	cout << "The length of that string = " << word.Length() << endl << endl;

	///////////////////////////////////
	////Test CharacterAt() function////
	///////////////////////////////////
	cout << "Enter a index to test the CharacterAt: ";
	cin >> int_input;
	cout << "The char at location" << int_input << " = " << word.CharacterAt(int_input) << endl << endl;

	///////////////////////////////
	////Test EqualTo() function////
	///////////////////////////////
	bool equalCheck = false;
	cout << "Enter a string to test the EqualTo: ";
	cin >> char_array_input;
	equalCheck = word.EqualTo(char_array_input);
	if (equalCheck)
	{
		cout << "The input contains the same characters." << endl << endl;
	}
	else
	{
		cout << "The input does not contain the same characters." << endl << endl;
	}

	///////////////////////////////
	////Test Append() function/////
	///////////////////////////////
	cout << "Enter a string to test the Append: ";
	cin >> char_array_input;
	word.Append(char_array_input);
	cout << "The new string now equals: " << word.CStr() << endl << endl;

	///////////////////////////////
	////Test Prepend() function////
	///////////////////////////////
	cout << "Enter a string to test the Prepend: ";
	cin >> char_array_input;
	word.Prepend(char_array_input);
	cout << "The new string now equals: " << word.CStr() << endl << endl;

	////////////////////////////
	////Test CStr() function////
	////////////////////////////
	cout << "Press any key to test the CStr return function." << endl;
	system("pause");
	cout << "The CStr returned: " << word.CStr() << endl << endl;

	///////////////////////////////
	////Test ToLower() function////
	///////////////////////////////
	cout << "Test the ToLower function." << endl;
	system("pause");
	word.ToLower();
	cout << "The result is: " << word.CStr() << endl << endl;

	///////////////////////////////
	////Test ToUpper() function////
	///////////////////////////////
	cout << "Test the ToUpper function." << endl;
	system("pause");
	word.ToUpper();
	cout << "The result is: " << word.CStr() << endl << endl;
	word.ToLower();

	////////////////////////////
	////Test Find() function////
	////////////////////////////
	cout << "Enter a string to test the Find function: ";
	cin >> char_array_input;
	cout << "The find returned location: " << word.Find(char_array_input) << endl << endl;

	cout << "Enter a start index to check from that location in the array: ";
	cin >> int_input;
	cout << "The find returned location: " << word.Find(int_input, char_array_input) << endl << endl;

	///////////////////////////////
	////Test Replace() function////
	///////////////////////////////
	cout << "Enter a Find string to test the Replace function: ";
	cin >> char_array_input;
	cout << "Now enter a Replace string: ";
	cin >> char_array_input_2;
	word.Replace(char_array_input, char_array_input_2);
	cout << "The Replace function returned: " << word.CStr() << endl << endl;
}
