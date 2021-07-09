// structured_scores.cpp : week 07 programming assignment
// Darren Cronover
// 7 9 2021

/// this console application will take in a txt file of bowling scores as input,
//calculate the average, then display to the user 

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//declare CONSTANTS
const int NUM_ROWS = 10;
const int NUM_COLS = 5;
const double NUM_GAMES = NUM_COLS;

// define structure
struct Bowlers {
    string name = " ";
    int scores[NUM_COLS]{};
    int avg = 0;
};

//prototype the functions that don't come first
double GetAverageScore(Bowlers player[]);
void PrintPrettyResults(Bowlers player[]);

//reads the data from the file(FileName), and loads the names into an array(NAMES(one row)), and the scores into a 2-dimensional array(SCORES (however many rows, default 4 columns))
bool GetBowlingData(string FileName, Bowlers player[]) {
    ifstream iFile;
    iFile.open(FileName);
    int r = 0;
    int c = 0;
    if (!iFile) {
        // if file did not open
        cout << "Error opening file." << endl;
        return false;
    }
    else {
        while (!iFile.eof()) {
            // while not at the end of the file...
            // write each line of the file to each indexed element of the arrays
            iFile >> player[r].name; // write the first column of each row to names, referenced with the member operator
            for (c = 0; c < NUM_COLS; c++) {
                // for c in the range of the amount of columnS, 
                //write to a corresponding index
                // for the current player, iterate through the scores
                iFile >> player[r].scores[c];
            }
            r++; // move on to next row, after each of the 4 columns are filled
        }
        iFile.close();
        // function calls are here, because i only want to print the results if the file successfully opens
        GetAverageScore(player);
        PrintPrettyResults(player);
        return true;
    }
}
//takes in the SCORES and AVG arrays, and populates AVG based on the sum of the scores
double GetAverageScore(Bowlers player[]) {
    double avgScore;
    int r = 0; // rows
    int c = 0; // columns
    for (r = 0; r < NUM_ROWS; r++) { // outer loop that loops through the rows
        int sum = 0; // reset the sum for each bowler
        for (c = 0; c < NUM_COLS; c++) { // inner loop that loops through each column
            sum += player[r].scores[c]; // sum = sum + element in scores array
        }
        // calculate average and add it to the AVG array
        avgScore = sum / NUM_GAMES;
        //avg is a member of the player structure
        player[r].avg = avgScore; // this array index = respective bowler avg score
    }
    return avgScore;
}
void PrintPrettyResults(Bowlers player[]) {
    // use format manipulators to beautify the console
    int width = 22; // trial and error to find a number that was aesthetically pleasing
    int c = 0;
    int r = 0;
    string strName = "Bowler Name ",
        str1 = " Score 1 ",
        str2 = " Score 2 ",
        str3 = " Score 3 ",
        str4 = " Score 4 ",
        str5 = " Score 5 ",
        strAVG = " Average Score";
    // the title across the top of the table
    cout << setfill('-') << left << strName << setw(width / 2) << ' ' << str1 << setw(width / 2) << ' ' << str2 << setw(width / 2) << ' ' << str3 << setw(width / 2) << ' ' << str4 << setw(width / 2) << ' ' << str5 << setw(width / 2) << ' ' <<  strAVG << endl;
    // print every name
    for (r = 0; r < NUM_ROWS; r++) {
        cout << setfill('-') << player[r].name << setw(width - player[r].name.length()) << ' ';
        // print every score they got, but maintaining clean spacing
        for (c = 0; c < NUM_COLS; c++) {
            cout << player[r].scores[c] << setw(width - to_string(player[r].scores[c]).length()) << ' ';
        }
        // print each average score, then move to a new line
        cout << player[r].avg << endl;
    }
}
int main()
{
    //declare variables
    string NAMES[NUM_ROWS] = {};
    int SCORES[NUM_ROWS][NUM_COLS] = {};
    double AVG[NUM_ROWS] = {};
    string FileName;

    // create an instance of the structure, specifically an array
    Bowlers player[NUM_ROWS];

    //prompt user for FileName
    cout << "Please enter the filename for the bowlers' scores: ";
    cin >> FileName;
    //Pass the data the function calls. - including the player array
    GetBowlingData(FileName, player);
    system("pause");
    return 0;
}

