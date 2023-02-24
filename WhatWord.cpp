/*
/ Robert Barrera
/ CS 141 at UIC
/ Program 5: WhatWord
/
/ Retry of Program 5 in CS 141 in C++
*/

#include <iostream>		// For standard input output
#include <cstring>		// For string functions
#include <cctype>		// For character functions
#include <ctime>		// For time
#include <cstdlib>		// For random numbers
#include <cmath>		// For fabs function
#include <fstream>		// For file input and output
#include <cassert>		// For the assert statement


using namespace std;
#pragma warning(disable:4996)

const int NumberOfWords = 300000;   // Number of dictionary words 300000
const int NumberOfRightSizedWords = 259709;	// Number of right size words
const int MinWordLength = 2;		// Minimum word length
const int MaxWordLength = 17;	    // Maximum word length + 1 for null 


// Displays programmer's information
void displayProgrammerInfo() {
	cout << "Author: Robert L Barrera\n";
	cout << "Program: #5, WhatWord\n";
	cout << "TA: Forgot\n";
	cout << "Feb 01, 2023\n\n";
}


// Displays introduction
void displayIntroduction() {
	cout << "Welcome to the game of Boggle, where you play against the clock\n";
	cout << "to see how many words you can find using adjacent letters on the\n";
	cout << "board.  Each letter can be used only once for a given word.\n\n";
	cout << "When prompted to provide input you may also:\n";
	cout << "     Enter 'r' to reset the board to user-defined values.\n";
	cout << "     Enter 's' to solve the board and display all possible words.\n";
	cout << "     Enter 't' to toggle the timer off/on.\n";
	cout << "     Enter 'x' to exit the program.\n\n";
}


// Displays timer for game
int displayTimer(time_t start) {
	cout << endl << "  ";

	if ((start - time(NULL)) > 0) {
		cout << start - time(NULL);
	}
	else {
		cout << "0";
	}

	cout << " seconds remaining";


	return (int)(start - time(NULL));
}


// Fuction for converting word to lower case letters
void convertWordToLowerCase(char theWord[]) {
	for (int i = 0; theWord[i] != '\0'; i++) {
		theWord[i] = tolower(theWord[i]);
	}
}


void setBoolsToFalse(bool array[]) {
	for (int i = 0; i < NumberOfRightSizedWords; i++) {
		array[i] = false;
	}
}


void addScore(char inputWord[], int &score) {
	int point = 0;

	if (strlen(inputWord) == 3) {
		point = 1;
	}
	else if (strlen(inputWord) == 4) {
		point = 2;
	}
	else if (strlen(inputWord) == 5) {
		point = 4;
	}
	else if (strlen(inputWord) > 5) {
		point = (int)strlen(inputWord);
	}
	score += point;
	cout << "   Worth " << point << " points." << endl;
}


// Reed's allocate array code
void allocateArray(char ** & matrix) {
	// Allocate space for large array of C-style strings
	matrix = new char*[NumberOfWords];

	// For each array entry, allocate space for the string to be stored there
	for (int i = 0; i < NumberOfWords; i++) {
		matrix[i] = new char[MaxWordLength];

		// just to be safe, initialize C-string to all null characters 
		for (int j = 0; j < MaxWordLength; j++) {
			matrix[i][j] = NULL;
		}//end for (int j=0...
	}//end for (int i...
}//end allocateArray()


 // Reed's deallocate array code
void deallocateArray(char ** & matrix) {
	// Deallocate dynamically allocated space for the array
	for (int i = 0; i < NumberOfWords; i++) {
		delete[] matrix[i];
	}
	delete[] matrix; // delete the array at the outermost level
}


// Uses Professor Reed's binary search code with changes
// Use binary search to look up the word in the word array
int binarySearch(char ** & matrix, char searchWord[]) {
	// the dictionary of words, word to be looked up
	int low, mid, high;     // array indices for binary search
	int searchResult = -1;  // Stores index of word if search succeeded, else -1

							// Binary search for word
	low = 0;
	high = NumberOfRightSizedWords - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		// searchResult negative value means word is to the left, positive value means
		// word is to the right, value of 0 means word was found
		searchResult = strcmp(searchWord, matrix[mid]);
		if (searchResult == 0) {
			// Word IS in dictionary, so return the index where the word was found
			return mid;
		}
		else if (searchResult < 0) {
			high = mid - 1; // word should be located prior to mid location
		}
		else {
			low = mid + 1; // word should be located after mid location
		}
	}

	// Word was not found
	return -1;
}//end binarySearch()


 // Reads in words from dicationary file using Reed's read file code
void readInDictionary(char ** & dictionary) {
	char tempWordArray[81];
	ifstream inStream;                          // Declare an input stream for my use
	int rightSizeWord = 0;						// Counter for right sized words
	int wordCounter = 0;                        // Counter for the current word
	inStream.open("dictionary.txt");
	assert(!inStream.fail());  // make sure file open was OK

							   // Keep repeating while input from the file yields a word
	while (inStream >> tempWordArray) {
		wordCounter++;

		if (strlen(tempWordArray) > MinWordLength && strlen(tempWordArray) < MaxWordLength) {
			convertWordToLowerCase(tempWordArray);	// Convert word to lower case
			strcpy(dictionary[rightSizeWord], tempWordArray);
			rightSizeWord++;	// Increment for every right size word within 3 - 16 length
		}
	}
	cout << "The dictionary total number of words is: " << wordCounter << endl;
	cout << "Number of words of the right length is:  " << rightSizeWord << endl;
}


// Initialize game board, puts *'s in array
void initializeGameBoard(char board[]) {
	for (int i = 0; i < 36; ++i) {	// For loop to iterate through each element
		board[i] = '*';		// Places *'s in each element
	}
}


// Displays game board array elements
void displayBoard(char board[]) {
	cout << endl;
	cout << board[7] << " " << board[8] << " " << board[9] << " " << board[10] << endl;		// First row 
	cout << board[13] << " " << board[14] << " " << board[15] << " " << board[16] << endl;	// Second row 
	cout << board[19] << " " << board[20] << " " << board[21] << " " << board[22] << endl;	// Third row 
	cout << board[25] << " " << board[26] << " " << board[27] << " " << board[28] << endl;	// Fourth row 
}


// Generates random number between 0-1
double generateRandomNumber() {
	(double)rand() / RAND_MAX;			// First random number is mostly the same everytime so
	return (double)rand() / RAND_MAX;	// Returns second random number
}


// Assigns a letter to the board according to random number
void assignLettersToBoard(char board[]) {
	double randomNumber;
	int count = 0;
	// Frequency numbers for each letter of the alphabet
	double letterValues[26]{0.07680,  //  a
							0.09485,  //  b
							0.13527,  //  c
							0.16824,  //  d
							0.28129,  //  e
							0.29299,  //  f
							0.32033,  //  g
							0.34499,  //  h
							0.43625,  //  i
							0.43783,  //  j
							0.44627,  //  k
							0.49865,  //  l
							0.52743,  //  m
							0.59567,  //  n
							0.66222,  //  o
							0.69246,  //  p
							0.69246,  //  q
							0.76380,  //  r
							0.86042,  //  s
							0.92666,  //  t
							0.95963,  //  u
							0.96892,  //  v
							0.97616,  //  w
							0.97892,  //  x
							0.99510,  //  y
							1.00000}; //  z

	for (int row = 0; row < 19; row += 6) {					// For rows
		for (int column = 7; column < 11; column++) {		// For columns
			randomNumber = generateRandomNumber();			// New random number for each position

			for (int value = 0; value < 26; value++) {		// Values in letterValues array
				if (randomNumber <= letterValues[value]) {	// Compare random number to letterValues
					board[row + column] = 'a' + value;		// Assign board position a letter 
					break;
				}
			}
		}
	}
}


// Reset board to user characters
void resetBoard(char newBoard[], char board[]) {
	int index = 0;	// For newBoard's elements
	for (int row = 0; row < 19; row += 6) {			// For rows
		for (int column = 7; column < 11; column++) {// For columns
			board[row + column] = newBoard[index++]; // Copy user characters to board
		}
	}
}


void displayAllFoundWords(char ** & dictionary, bool wordsFound[]) {
	cout << "Words so far are: ";

	for (int size = MinWordLength + 1; size < MaxWordLength; size++) {
		for (int i = 0; i < NumberOfRightSizedWords; i++) {
			if (wordsFound[i] && strlen(dictionary[i]) == size) {
				cout << dictionary[i] << " ";
			}
		}
	}
	cout << endl;
}


int checkDictionaryArrayForWord(char inputWord[], char ** & dictionary) {
	int index = binarySearch(dictionary, inputWord);

	if (index < 0) {
		cout << "was not found in the dictionary." << endl;
	}

	return index;
}


bool checkNextCharacter(char inputWord[], char board[], int boardPos, int wordPos) {
	char tempChar = '0';
	int moves[] = { 1, 7, 6, 5, -1, -7, -6, -5 };

	if (board[boardPos] == inputWord[wordPos]) {	// Letters matched
		if (wordPos == strlen(inputWord) - 1) {		// Matched letter is last
			return true;
		}

		tempChar = board[boardPos];					// Save board letter
		board[boardPos] = '*';						// Place star so letter can't be used again

		for (int i = 0; i < 8; i++) {
			if (board[boardPos + moves[i]] != '*') {
				if (checkNextCharacter(inputWord, board, boardPos + moves[i], wordPos + 1)) {
					board[boardPos] = tempChar;		// Place character back on board
					return true;
				}
			}
		}
		board[boardPos] = tempChar;		// Place character back on board
	}

	return false;
}


void displayAllWordsOnBoard(char board[], char ** &dictionary) {
	int min = MinWordLength, max = MaxWordLength;
	cout << "Enter min and max word lengths to display: ";
	cin >> min;
	cin >> max;
	cout << "Words between " << min << " and " << max << " are: " << endl;

	for (int size = min; size < max; size++) {	// Starting with size
		for (int i = 0; i < NumberOfRightSizedWords; i++) {				// For each word
			if (strlen(dictionary[i]) == size) {						// If sizes match
				for (int row = 0; row < 19; row += 6) {					// For rows
					for (int column = 7; column < 11; column++) {		// For columns
						if (checkNextCharacter(dictionary[i], board, row + column, 0)) {
							cout << dictionary[i] << " ";
						}
					}
				}
			}
		}
	}
	cout << endl;
}


// Checks user input for options
bool checkForOptions(char inputWord[], char board[], char ** & dictionary, bool &timerToggle, bool wordsFound[]) {
	if (inputWord[0] == 'r' || inputWord[0] == 'R') {		// Reset board
		cout << "Enter 16 characters to be used to set the board: ";
		char newBoard[20];
		cin >> newBoard;
		resetBoard(newBoard, board);	// Reset board to user characters
		setBoolsToFalse(wordsFound);
		return true;
	}
	else if (inputWord[0] == 's' || inputWord[0] == 'S') {	// Solve & display all words on board
		displayAllWordsOnBoard(board, dictionary);
		deallocateArray(dictionary);
		cout << "Exiting the program.";
		cin.get();
		cin.ignore();
		exit(0);
		return true;
	}
	else if (inputWord[0] == 't' || inputWord[0] == 'T') {	// Timer toggle
		if (timerToggle) {
			timerToggle = false;
		}
		else {
			timerToggle = true;
		}
		return true;
	}
	else if (inputWord[0] == 'x' || inputWord[0] == 'X') {	// Exit
		deallocateArray(dictionary);
		cout << "Exiting the program.";
		cin.get();
		cin.ignore();
		exit(0);			// Exit program if input is x or X
		return true;
	}
	return false;
}


// Checks board for input word 
bool checkBoardForWord(char inputWord[], char board[], char ** & dictionary, bool wordsFound[], int &score) {
	int indexOfWord = binarySearch(dictionary, inputWord);	// Variable is index of dictionary word
	if (indexOfWord != -1) {	// True if word is found
		if (wordsFound[indexOfWord]) {
			cout << "Sorry, that word was already previously found." << endl;
			displayAllFoundWords(dictionary, wordsFound);
			return false;
		}

		for (int row = 0; row < 19; row += 6) { // For rows
			for (int column = 7; column < 11; column++) {		// For columns
				if (checkNextCharacter(inputWord, board, row + column, 0)) {
					wordsFound[indexOfWord] = true;
					addScore(inputWord, score);
					displayAllFoundWords(dictionary, wordsFound);
					return true;
				}
			}
		}
		cout << "cannot be formed on this board." << endl;
	}
	else {
		cout << "was not found in the dictionary." << endl;
	}

	return false;
}


// Checks user input if options are selected
bool checkUserInput(char inputWord[], char board[], char ** & dictionary, bool wordsFound[], bool &timerToggle, int &score) {
	if (strlen(inputWord) == 1) {	// If string is one character
		if (checkForOptions(inputWord, board, dictionary, timerToggle, wordsFound)) {	// Then check for options
			return false;
		}
	}

	if (strlen(inputWord) > MinWordLength && strlen(inputWord) < MaxWordLength) {	// If input is valid length
		return checkBoardForWord(inputWord, board, dictionary, wordsFound, score);	// Check for word on board
	}

	cout << "incorrect word length." << endl;
	return false;
}


// Ask user for input
bool askUserForInput(char board[], char ** & dictionary, bool wordsFound[], bool &timerToggle, int &score) {
	cout << "Enter a word: ";
	char inputWord[20];
	cin >> inputWord;
	/*cout << inputWord << endl;
	cout << strlen(inputWord) << endl;*/

	return checkUserInput(inputWord, board, dictionary, wordsFound, timerToggle, score);	// Check input word
}


int main() {
	char board[36];				// Char array for game board
	char ** dictionary;			// Char pointers for dictionary array
	bool wordsFound[NumberOfRightSizedWords];
	srand((unsigned)time(NULL));		// Start random number generator
	int counter = 1;
	bool timerToggle = false;
	int score = 0;

	displayProgrammerInfo();	// Displays programmer's information
	displayIntroduction();		// Displays introduction
	initializeGameBoard(board);	// Initialize game board, puts *'s in array
	assignLettersToBoard(board);// Assigns a letter to the board according random number
	allocateArray(dictionary);	// Allocates array for dictionary file
	readInDictionary(dictionary);	// Reads in dicationary words into array
	setBoolsToFalse(wordsFound);

	time_t start = time(NULL) + 60;	// Timer starts at 60
	displayTimer(start);		// Display timer

	do {
		displayBoard(board);		// Displays game board array elements
		cout << "   Score: " << score << endl;
		cout << counter << ". ";
		if (askUserForInput(board, dictionary, wordsFound, timerToggle, score)) {	// Asks user for input
			counter++;
		}
	} while (timerToggle || (displayTimer(start) > 0)); // End game when timer reaches 0

	deallocateArray(dictionary);	// Deallocates array for dictionary file
	cout << "Exiting the program.";
	cin.get();
	cin.ignore();
	return 0;
}