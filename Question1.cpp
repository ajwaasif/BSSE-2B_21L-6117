#include <iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>
using namespace std;

void DeallocateMemory(char** matrix, const int& rows)
{
	//Deletes the memorry after the use.

	for(int i = 0; i < rows; i++)
		if (matrix[i])
			delete[] matrix[i];
	if (matrix)
		delete[] matrix;
}

int StringLenght(char* mystr)
{
	int lenght = 0;
	for (char* j = mystr; *j != '\0'; j++, lenght++);

	return lenght;

}

void AllCaps(char* Word)
{
	//Converts the LowerCase Letters into UpperCase
	int strLen = StringLenght(Word);
	for (int i = 0; i < strLen; i++)
	{
		if (Word[i] >= 97 && Word[i] <= 122)
			Word[i] = Word[i] - 32;
	}

}

void RemoveSpaces(char* Word)
{
	int strLen = StringLenght((Word)), k = 0;
	
	for (int j = 0, i = 0; *(Word + j) != '\0'; j++)
	{
		if (*(Word + j) == ' ')
		{
			for (int i = j; i < strLen - 1; i++)
			{
				Word[i] = Word[i + 1];
			}
			
			Word[strLen - 1] = '\0';
		}
	}
}

void DisplayMatrix(char** matrix, const int& rows)
{
	// in this function nested loop is started to display the matrix in the right order.

	for (int i = 0; i < rows; i++)
	{

		cout << matrix[i] << " ";
		cout << endl;
	}
	
	cout << endl << endl;

}

char* GetStringFromBuffer(char* buffer)
{
	//converts charecter array into pointer
	int strLen = StringLenght(buffer);
	char* str = 0;

	if (strLen > 0)
	{
		str = new char[strLen + 1];
		char* tempDest = str;
		for (char* tempSrc = buffer; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}
	
	return str;

}

char** InputFile(int& size,int SizeOfStr[])
{
	//takes the name in the form of char and then convert it to pointer then save it in the Array.
	ifstream cinF("Input.txt");
	int  StrLen = 0;
	char** WordList = new char* [size];

	char tempBuffer[80];
	for (int i = 0; i < size; i++)
	{
		StrLen = 0;

		char* Word = 0;

		cinF.getline(tempBuffer, 80);
		RemoveSpaces(tempBuffer);
		AllCaps(tempBuffer);
		StrLen = StringLenght(tempBuffer);
		SizeOfStr[i] = StrLen;
		Word = GetStringFromBuffer(tempBuffer);

		WordList[i] = new char[StrLen];

		*(WordList + i) = Word;
	}
	cinF.close();
	return WordList;
}

void OutputFile(char** grid, int rows)
{
	//creates the Output file and saves the data in it.
	ofstream coutF("Output.txt");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			coutF << grid[i][j] << " ";
		}
		coutF << endl;

	}

	cout << endl << endl;

}

int NumberOfWords()
{
	//opens the file and Read the number of letters in the list.
	ifstream cinF("Input.txt");
	int i = 0;
	if (cinF.is_open())
	{

		int StrLen = 1;
		char tempBuffer[80];
		for (; StrLen != 0; i++)
		{
			cinF.getline(tempBuffer, 80);
			StrLen = StringLenght(tempBuffer);
			if (StrLen == 0)
				break;
		}
		cinF.close();

	}
	else
	{
		cout << "Error! File named Input.txt Doesnt Exist!" << endl;
	}

	return i;


}

int LongestWord(char** WordList,const int size)
{
	//Finding the Length of the logest word in the whole list
	int Max = StringLenght(*(WordList + 0));
	
	for (int i = 0; i < size; i++) {
		
		int strLen = StringLenght(*(WordList + i));
		
		for (int j = 0; *(*(WordList + i) + j) != '\0'; j++)
		{
			if (*(*(WordList + i) + j) == ' ')
				strLen--;
		}
		
		if (strLen >= Max)
		{
			Max = strLen;
		
		}
	}
	
	return Max;
}

void DecendinOrderSort(char** WordList, int size, int sizeOfStr[])
{
	//Sorts the list in Descending  order with respect to size.
	//it also sort the array containing their size.
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (sizeOfStr[i] <= sizeOfStr[j])
			{
				swap(WordList[i], WordList[j]);
				swap(sizeOfStr[i], sizeOfStr[j]);
			}
		}
	}
}

bool IsItAvailable(char** Grid, char* Word, int Row,int Column,int r, int c, int size)
{
	//This function checks whether the word can fit in the desried area or not. 
	for (int i = Row, j = Column, l = 0; l < size; i += r, j += c,l++)
	{
		if (Word[l] != Grid[i][j] && Grid[i][j] != '-')
			return false;
	}
	return true;
}

bool SettingWordsIntoTheGrid(char** Grid, char* Word, int r, int c, int Max)
{
	//First the row amd column is randomized and checked that wheather it can fit into the grid or not
	// then we check the availability of space for the word. 
	// then we set the word into the grid.
	int strLen = StringLenght(Word);
	int Row = (rand() % Max);
	int Column = rand() % Max;

	if (c != 0)
	{
		if (c==1) 
		{
			if (strLen != Max) {
				while (Column + strLen >= Max)
					Column = rand() % Max;
			}
			else
				Column = 0;
		}
		
		else 
		{
			if (strLen != Max) 
			{
				while (Column - strLen < 0)
					Column = rand() % Max + 0;
			}
			else
				Column = Max - 1;		
		}
		}
	if (r != 0)
	{
		if (r==1) 
		{
			if (strLen != Max) {
				while (Row + strLen >= Max)
					Row = rand() % Max;
			}
			else
				Row = 0;
		}

		else
		{
			if (strLen != Max) {
				while (Row - strLen < 0)
					Row = rand() % Max;
			}
			else
				Row = Max - 1;
		}
	}

	bool Availability = IsItAvailable(Grid, Word, Row, Column, r, c, strLen);

	if (Availability == true)
	{
		for (int i = Row, j = Column, l = 0; l < strLen; i += r, j += c,l++)
		{
			Grid[i][j] = Word[l];
		}
		return true;
	}
	return false;
}

void RandomWords(char** Grid, int Max)
{
	//This sets random words on the remaining empty spaces after the words are set.
	srand(time(0));
	for (int i = 0; i < Max; i++)
	{
		for (int j = 0; j < Max; j++)
		{
			if (Grid[i][j] == '-')
			{
				Grid[i][j]= (char)((rand() % 26) + 65);
			}
		}
	}
}

char** GridGenerator(char** WordList, const int size,const int Max)
{
	//This functionn creates a grid then sets the words from list and then fills it with random words.
	char** Grid = new char* [Max];
	//in these 2 loops we firs create a memmory and then set '-' as a control varriable.
	for (int i = 0; i < Max; i++)
	{
		Grid[i] = new char[Max+1];
	}

	for (int i = 0; i < Max; i++)
	{
		for (int j = 0; j < Max; j++)
			Grid[i][j] = '-';
		Grid[i][Max] = '\0';
	}

	//srand is used to produce diffferent results everytime.
	srand(time(0));
	for (int i = 0,count=0; i < size;i++)
	{
		//this varriable takes a random number and then sets the word to on the grid with the pattern set for that umber. 
		int pattern = rand() % 8 + 1;
		// We call the function settingWordsIntoTheGrid then if the word can fit into the grid it sets it 
		// if not the loop is started to set the word into the grid.
		// if the word is not able to fit into the grid then we skip the word to prevent infinite laop
		// 
		
		//left to right
		if (pattern == 1)
		{
			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 0, +1,Max);
				
			if (Availability == false)
			{
				count++;
				i--;
			}

		}
		//Right to Left
		else if (pattern == 2)
		{
			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 0, -1, Max);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}
	
		//Top to bottom
		else if (pattern == 3)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 1, 0, Max);

			if (Availability == false)
			{
				count++;
				i--;
			}
		}
		
		//Bottom to Top	
		else if (pattern == 4)
		{				
			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], -1, 0, Max);;

			if (Availability == false)
			{
				count++;
				i--;
			}

		}
		
		//Top left to Bottom right
		else if (pattern == 5)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 1, 1, Max);;

			if (Availability == false)
			{
				count++;
				i--;
			}

		}
		
		//Bottom Right to Top Left
		else if (pattern == 6)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], -1, -1, Max);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}
		
		//Top Right to Bottom left
		else if (pattern == 7)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], 1, -1, Max);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}
		
		//Bottom Left to Top Right
		else if (pattern == 8)
		{

			bool Availability = SettingWordsIntoTheGrid(Grid, WordList[i], -1, 1, Max);;

			if (Availability == false)
			{
				count++;
				i--;
			}
		}

		// if the word is not able to set into the grid and the loop is inititated 500 times then we skip the word.
		if (count == 500)
		{
			cout << "Word ' " << WordList[i] << " ' is Skipped Because it cant fit into the grid!" << endl;
			i++;
		}
	}
	//Setting Random WOrds on the remaining space left
	RandomWords(Grid, Max);
	
	return Grid;
}
int main()
{
	int size = 0;
	char** WordList,**Grid;
	
	size=NumberOfWords();

	int SizeOfStr[50];
	WordList = InputFile(size,SizeOfStr);

	int Max=LongestWord(WordList, size);

	DecendinOrderSort(WordList, size, SizeOfStr);
	Grid = GridGenerator(WordList, size, Max);
	
	OutputFile(Grid, Max);
	cout << "Results saved into the file Output.txt Successfully! \nHope you got all of them Correct!" << endl;
	DeallocateMemory(Grid, Max);
	DeallocateMemory(WordList, size);

	return 0;
}
