#include <iostream>
#include <fstream>

using namespace std;

void DeallocateMemory(char** matrix, const int& rows)
{
	//Deletes the memorry after the use.

	for (int i = 0; i < rows; i++)
		if (matrix[i])
			delete[] matrix[i];
	if (matrix)
		delete[] matrix;
}

void OutputFile(int Matrix[][4],char** Wordlist, const int& rows,int Cols, int Control)
{
	// Saves the result in the output file.
	ofstream coutF("Output.txt");
	for (int i = 0; i < rows; i++)
	{
		coutF << Wordlist[i] << "\t { ";
		for (int j = 0; j < Cols; j++)
		{
			if (j == 2)
				coutF << " } to { ";
			if (Matrix[i][0] == Control)
			{
				coutF << "Not Found  ";
				break;

			}
			coutF << Matrix[i][j] << " ";


		}
			
		coutF <<"}"<< endl;
	}

	coutF << endl << endl;

}

int StringLenght(char* mystr)
{
	//calculates the lenght of the word.
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
	//removes spaces between a zsingle entry.
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

void DisplayMatrix(int** matrix, const int& rows)
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
	//converts charecter array into pointer.
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

char** InputFile(int size)
{
	//this function takes input from user.
	//takes the name in the form of char and then convert it to pointer then save it in the Array.
	int  StrLen = 0;
	char** WordList = new char* [size];

	char tempBuffer[80];
	for (int i = 0; i < size; i++)
	{
		cout << "Word " << i + 1 << ": ";
		StrLen = 0;

		char* Word = 0;

		cin >> tempBuffer;
		StrLen = StringLenght(tempBuffer);
		Word = GetStringFromBuffer(tempBuffer);

		WordList[i] = new char[StrLen];

		*(WordList + i) = Word;
	}
	return WordList;
}

char** InputFile(ifstream& cinF,int& Rows,int Cols)
{
	//takes the name in the form of char and then convert it to pointer then save it in the Array.
	char** WordList = new char* [Rows];

	char tempBuffer[80];
	for (int i = 0; i < Rows; i++)
	{
		cinF.getline(tempBuffer, 80);

		if (Cols == 0)
		{
			int StrLen = StringLenght(tempBuffer);
			WordList[i] = new char[StrLen];
		}
		else
			WordList[i] = new char[Cols];


		char* Word = 0;


		Word = GetStringFromBuffer(tempBuffer);
		RemoveSpaces(Word);

		*(WordList + i) = Word;
	}
	cinF.close();
	return WordList;
}

int NumberOfRows()
{
	//opens the file and Read the number of Rows in the list.
	ifstream cinF("Input.txt");
	int i = 0;
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
	return i;


}

bool SearchWord(char** Grid, char* Word, int Row, int Column, int r, int c, int size,int cols)
{
	//this function search the word from the starting letter which same as the first letter of the desired word.
	if (c != 0)
	{
		if (c == 1) 
		{
			if (Column + size >= cols)
				return false;
		}
		else if (Column - size < 0)
				return false;
	}
	if (r != 0)
	{

		if (r == 1)
		{
			if (Row + size >= cols)
				return false;
		}

		else if (Row - size < 0)
				return false;
	}

	for (int i = Row, j = Column, l = 0; l < size ; i += r, j += c, l++)
	{
		if (Word[l] != Grid[i][j])
			return false;

	}
	return true;
}

void CoordinatesForWords(int Coordinates[][4],char** Grid, char** WordList, int Rows, int Cols, int Entries)
{
	//this function consits of multiple if statements.
	//if the first letter is same than the desired word then then we set the parameters one by one to find 
	//the word in all eight directions. if that is not possible we again find the fist letter.
	//if the word is found then the loop is broken and then the coordinates are set into the Coordinates array
	//Depending to its direction.
	for (int i = 0; i < Entries; i++)
	{
		bool Found = false;

		for (int j = 0; j < Rows; j++)
		{
			for (int l = 0; l < Cols; l++)
			{
				int count = 0;
				if (Grid[j][l] == WordList[i][0])
				{
					int StrLen = StringLenght(WordList[i]);
					int a = j;

					for(;count<8 && Found==false;count++)
					{	
						int r = 0, c = 0;

						//Right to Left
						if (count == 0)
						{
							c = 1;
						}
						
						//Left to Right
						else if (count == 1)
						{
							c = -1;
						}
						
						//Top to Bottom
						else if (count == 2)
						{
							r = 1;
						}
						
						//Bottom to Top
						else if (count == 3)
						{
							r = -1;
						}
						
						//Top Left to Bottom RIght
						else if (count == 4)
						{
							r = 1;
							c = 1;
						}
						
						//Bottom RIght to Top Left
						else if (count == 5)
						{
							r = -1;
							c = -1;
						}
						
						//Bottom Left to Top Right
						else if (count == 6)
						{
							r = -1;
							c = 1;
						}
						
						//Top Right to Bottom Left
						else if (count == 7)
						{
							r = 1;
							c = -1;

						}

						Found = SearchWord(Grid, WordList[i], j, l,r,c , StrLen,Cols);
						if (Found == true)
							break;
					}

					if (Found == true)
					{
						//Stating Coordinates
						Coordinates[i][0] = j;
						Coordinates[i][1] = l;

						//Right to Left
						if (count == 0)
						{
							Coordinates[i][2] = j;
							Coordinates[i][3] = l + StrLen-1;
						}
						
						//Left to Right
						else if (count == 1)
						{
							Coordinates[i][2] = j;
							Coordinates[i][3] = l - StrLen+1;
						}
						
						//Top to Bottom
						else if (count == 2)
						{
							Coordinates[i][2] = j + StrLen-1;
							Coordinates[i][3] = l;
						}
						
						//Bottom to Top
						else if (count == 3)
						{
							Coordinates[i][2] = j - StrLen+1;
							Coordinates[i][3] = l;
						}
						
						//Top Left to Bottom RIght
						else if (count == 4)
						{
							Coordinates[i][2] = j + StrLen-1;
							Coordinates[i][3] = l + StrLen-1;
						}
						
						//Bottom RIght to Top Left
						else if (count == 5)
						{
							Coordinates[i][2] = j - StrLen+1;
							Coordinates[i][3] = l - StrLen+1;
						}
						
						//Bottom Left to Top Right
						else if (count == 6)
						{
							Coordinates[i][2] = j - StrLen+1;
							Coordinates[i][3] = l + StrLen-1;
						}
						
						//Top Right to Bottom Left
						else if (count == 7)
						{
							Coordinates[i][2] = j + StrLen-1;
							Coordinates[i][3] = l - StrLen+1;
						}
						
						break;
					}
					
					if (Found == false && count == 8)
					{
						Coordinates[i][0] = Cols + Rows;
					}
				}
			}
		
			if (Found == true)
				break;
		}
	}
	return;
}

int main()
{
	char** Grid;
	int Rows, Cols, Entries = 0,Coordinates[100][4];
	char** WordList;
	
	ifstream cinF("Input.txt");
	if (cinF.is_open())
	{
		cinF >> Rows;
		cinF >> Cols;
		cinF.ignore();
		Grid = InputFile(cinF, Rows, Cols);
		cout << "Press 1 Take input of the  Words from Word.txt" << endl << "Press 2 if you want to type it in one by one!" << endl;
		int Choice = 3;
		cin >> Choice;
		while (Choice != 2 && Choice != 1)
		{
			cout << "Wrong Input" << endl
				<< "Press 1 Take input of the  Words from Word.txt" << endl
				<< "Press 2 if you want to type it in one by one!" << endl;
			cin >> Choice;
		}

		if (Choice == 1)
		{
			ifstream cinF("Words.txt");
			if (cinF.is_open())
			{
				cinF >> Entries;
				cinF.ignore();
				WordList = InputFile(cinF, Entries, 0);

			}
			else
			{
				cout << "Error! File named Words.txt doesnt exist!" << endl;
				WordList = 0;
			}

		}

		else
		{
			cout << "Please enter number of Entries: " << endl;
			cin >> Entries;
			WordList = InputFile(Entries);
		}


		for (int i = 0; i < Entries; i++)
		{
			AllCaps(WordList[i]);
			RemoveSpaces(WordList[i]);
		}

		CoordinatesForWords(Coordinates, Grid, WordList, Rows, Cols, Entries);
		OutputFile(Coordinates, WordList, Entries, 4, (Cols + Rows));
		cout << "Results saved into the file Output.txt Successfully! \nHope you got all of them Correct!" << endl;
	}
	else
	{
		cout << "Error! File named Input.txt Doesnt Exist!" << endl;
		WordList = 0;
		Grid = 0;
		Rows = 0;
		Entries = 0;
	}
	DeallocateMemory(Grid,Rows);
	DeallocateMemory(WordList, Entries);

	return 0;

}
