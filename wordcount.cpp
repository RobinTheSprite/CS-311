/*
wordcount.cpp
Mark Underwood
12.3.17
Contains wordcount function
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <fstream>
#include <string>
#include <map>

bool checkExtension(std::string & filename)
{
	std::string ext;
	for (auto it = (filename.end()-1); *it != '.'; --it)
	{
		ext.push_back(*it);
	}
	ext.push_back('.');

	return ext == "txt.";
}

void count(std::string filename, std::map<std::string, int> & allWords)
{
	std::ifstream fileBuffer(filename);
	if (!fileBuffer)
	{
		cout << "ERROR: could not open file \"" << filename << "\"" << endl;
	}

	std::string word;
	while (fileBuffer >> word)
	{
		++allWords[word];	
	}
}

int main()
{
	std::map<std::string, int> allWords;

	cout << "Enter a file name: ";
	std::string line;
	std::getline(cin, line);
	if (!cin)
	{
		cout << "ERROR: Input read failed" << endl;
	}
	else if (!checkExtension(line))
	{
		cout << "ERROR: File extension incorrect" << endl;
	}

	count(line, allWords);

	if (allWords.size() == 0)
	{
		cout << "No words in file" << endl;
	}
	else
	{
		cout << "Number of words: " << allWords.size() << endl;
		for (auto pair : allWords)
		{
			cout << pair.first << " " << pair.second << endl;
		}
		cout << endl;
	}

	cout << "Press ENTER to exit" << endl;
	while(cin.get() != '\n')

	return 0;
}