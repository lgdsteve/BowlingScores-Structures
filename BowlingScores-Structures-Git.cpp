// BowlingScores-Structures.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>         // std input/output stream objects  (cout, cin)
#include <fstream>          // used to read data from file. (ifstream)
#include <iomanip>          // used to manipulate strings (setfill, setw, setpercision)

/* Standard Libraries not used for this assignment */
//#include <algorithm>
//#include <string>
//#include <cwctype>
//#include <cctype>  
//#include <string>

using namespace std;

const int NumRows = 10;		// Total number of bowlers
const int NumScores = 5;	// Total Scores for each bowler

/****************************** STRUCTURE FOR BOWLER'S DATA **************************************/
struct BowlingData {
	string	sBName;				// Bowler's Name
	int		aScore[NumScores];		// Bowler's scores (as an array)
	float	fAvgScore;			// Average score
};

/****************************** HEADER **************************************/
void ShowHeader() {
	int HEADERLEN = 60;           // White spacing for total header length (Width of program and text)
	string MSGHeader = " Bowling Scores Calculator  ";
	int MSGHeaderLen = static_cast<int>(MSGHeader.length());
	// Declare and figure out how man astrisks to put on the left and right side of the header text
	int FillLen = HEADERLEN - MSGHeaderLen;
	int FillSide = FillLen / 2;
	string Fill(FillSide, '*');

	// Build the Program Header
	cout << setfill('*');                               // Sets filler to astrisks
	cout << setw(HEADERLEN) << "" << endl;              // Astrisks on the top
	cout << setw(static_cast<std::streamsize>(MSGHeaderLen) + FillSide) << right << MSGHeader << Fill << endl; // Left astrisks, Program title, right astrisks
	cout << setw(HEADERLEN) << "" << endl << endl;      // Astrisks on the bottom

	cout << setfill(' ');	// reset the fill for bowling score formatting 
}

/****************************** GET BOWLING DATA **************************************/
bool GetBowlingData(string sFileArg, BowlingData Bowler[NumRows])
{
	ifstream fs;								// Declare the file stream
	fs.open(sFileArg);							// Open file from command prompt arguments
	if (!fs) {									// If the file fails to load..
		cout << "File read error" << endl;		// print the error and..
		return false;							// Exit function with a (bool) false
	}
	int index = 0;								// Initialize Row Index
	while (!fs.eof() && index < NumRows) {		// If the file opened and the row index variable is less than the const num rows
		fs >> Bowler[index].sBName;				// Insert the bowler's name into the Bowler array 
		for (int c = 0; c < NumScores; c++) {	// Start iterating through the scores of the specific bowler
			fs >> Bowler[index].aScore[c];		// and insert each score into a specific bowler's score array
		}
		index++;								// Increment the row index by one to control the while loop
	}
	fs.close();									// Close the file..
	return true;								// And end the function with a (bool) true
}

/****************************** CALCULATE AVERAGE SCORE **************************************/
void GetAverageScore(BowlingData Bowler[NumRows])
{
	for (int r = 0; r < NumRows; r++) {					// Start iterating through the rows..
		int iScoresTotal = 0;							// And make sure the total score calculation is reset to zero before starting the next bowler (row)
		for (int c = 0; c < NumScores; c++) {			// Start iterating through the bowler's scores
			iScoresTotal += Bowler[r].aScore[c];		// Tally up each score from the structure array
		}												
		Bowler[r].fAvgScore = static_cast<float>(iScoresTotal / NumScores);		// Calculate the average (total score divided by number of scores (const)
	}
}

/****************************** PRINT THE STRUCTURE **************************************/
void PrettyPrintResults(BowlingData Bowler[NumRows])
{
	for (int r = 0; r < NumRows; r++) {									// Start iterating through the structure data
		cout << Bowler[r].sBName << ": ";								// Print the bowler's name
		for (int c = 0; c < NumScores; c++) {							// Enter the score array
			cout << setw(5) << right << Bowler[r].aScore[c] << " ";		// Print the scores
		}
		cout << "   Average: " << Bowler[r].fAvgScore << endl ;			// Then print the average score for that bowler
	}																	// and repeat until complete
	cout << endl;														// End line for beautification
}


/****************************** MAIN **************************************/
int main(int argc, char* argv[])
{
	ShowHeader();							// Show header (I like  the header, sort of makes it look like a real program)

	if (argc < 2)							// Check for a supplied file name in command arguments
	{										// If, less than two arguments..
		cout << "Enter File Name" << endl;	// No file was supplied
		return 1;
	}

	BowlingData Bowler[NumRows];			// Initialize the structure array

	GetBowlingData(argv[1], Bowler);		// Call the function to get the bowling data
	GetAverageScore(Bowler);				// Call the function to calculate average score
	PrettyPrintResults(Bowler);				// Call the function to print the results

	system("PAUSE");						// Pause and end application
	return 0;

}
