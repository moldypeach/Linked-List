/* Filename:        TestLinkedList.cpp
 * Last Modified:   14 March 2014
 * Author:          Todd Parker
 * Email:           todd.i.parker@maine.edu
 * Course:          CIS354 - Algorithms and Data Structures
 * 
 * TestLinkedList.cpp is a test-harness program for LinkedList.h. It prints a header from
 * SingatureBlock.h, two hard-coded messages, and a prompt requesting a user to input a word
 * or words to try and remove from the printed hard-coded excerpt. A regex_replace function
 * is utilized for the purposes of stripping the all punctuation from a string, and then
 * a stringstream object is created to extract and add tokens to a Linked List. Functions
 * printList and strlen so as their names suggest, print values of a list and return the
 * length of a string.
 *
 * NOTE: Most of LinkedList.h, and the function printList were adapted from source code
 * in "Introduction to Programming with C++, 3E - by Y. Daniel Liang"
 */
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <stdexcept>
#include "LinkedList.h"
#include "SignatureBlock.h"

using namespace std;
 
void printList(const LinkedList<string>& list)
{
	cout << endl;
	for (int i = 0; i < list.getSize(); i++)
	{
		cout << list.get(i) << " ";
	}
	cout << endl;
}

// Function used to determine the size of a C-string
unsigned int strlen(char s[])
{
	int i = 0;
	for ( ; s[i] != '\0'; i++);
	return i;
} // end strlen

int main()
{
	SignatureBlock::printHeader();
	// Create a list for strings
	LinkedList<string> list;

	// Store start C-String address of the predetermined excerpt for testing the program
	const char *stringStart = "DURING the whole of a dull, dark, and soundless day in the autumn of the year, when the clouds hung oppressively low in the heavens, I had been passing alone, on horseback, through a singularly dreary tract of country; and at length found myself, as the shades of the evening drew on, within view of the melancholy House of Usher.";

	cout << "For your reading pleasure, here is an excerpt from Edgar Allen Poe's \"Fall of the House of Usher\", untainted and full of punctuation. Now with 50% more madness and dispair!\n\n" << stringStart << endl;

	// Store end memory address of stringStart
	const char *stringEnd = stringStart + strlen(stringStart);
	// Dynamically create C-String to size of stringStart to hold the result of string replacement
	char *buf = new char[strlen(stringStart)];
	// Regular expression to remove all punctuation and special characters
	std::regex rx ("[^([:alpha:][:space:])]");
	// Replace rx matches with an empty character (i.e. delete them)
	std::string fmt("");
	// Perform the string replacement and store results
	*std::regex_replace(&buf[0], stringStart, stringEnd, rx, fmt) = '\0';
	// Create stringstream object and initialize with buf
	stringstream extractTokens(buf);
	// String to hold temporary tokens
	string token;
	// While stringstream has input, extract a token and insert it into linked list
	while( !extractTokens.eof() )
	{
		extractTokens >> token;
		list.add(token);
	}

	cout << "\nPlease enter a word, or words separated by spaces, to delete from excerpt.\n: ";
	string userInput;
	getline(cin, userInput);
	stringstream test(userInput);

	try
	{
		while( !test.eof() )
		{
			test >> token;
			list.remove( token );
		}
	}
	catch(exception& isEmpty)
	{
		cout << isEmpty.what() << endl;
	}

	cout << "\n\tExcerpt after calling remove function:" << endl;
	printList(list);
   
	getchar();
	return 0;
}