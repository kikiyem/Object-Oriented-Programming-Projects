// Author: Kiki Yem
// CIS 3100
// Assignment 4

#include <iostream>
#include <ctime> //computer time

using namespace std;
void white();
void red();

const int whiteBalls = 69;
const int whitePicks = 5;
const int redBalls = 26;



int main()
{	
	int numberOfGames;
	cout << "How many games would you like to play? ";
	cin >> numberOfGames;
	cout << endl;

	//for random number
	srand(time(0));

	for (int i = 0; i < numberOfGames; i++) {
		//Print lucky balls
		white();
		red();

	}
	
	return 0;

}

void white() {


	int arrayWhiteBalls[whiteBalls] = {};

	//intial array adds numbers 1-69 to array
	int num = 1;
	for (int i = 0; i < whiteBalls; i++) {
		arrayWhiteBalls[i] = num;
		num++;
	}
	

	//lucky numbers array
	int luckyWhitePicked[whitePicks] = {};
	
	//repeats to get number for number of picks
	for (int picks = 1; picks <= whitePicks; picks++) {

		//choosing random number position between 0- 68
		int randomNumber = rand() % (whiteBalls);
		//cout << randomNumber << endl;

		//acutal number picked
		int actualNumberPicked = arrayWhiteBalls[randomNumber];
		//cout << actualNumberPicked << endl;
		
		//add number picked to luckyWhitePicked array
		luckyWhitePicked[picks - 1] = actualNumberPicked;

		//new/pack array
		for (int i = randomNumber; i < (whiteBalls - picks); i++) {
			arrayWhiteBalls[i] = arrayWhiteBalls[i + 1];
		}
	}

	//bubble sort lucky numbers array
	
	for (int x = (whitePicks - 1); x > 0; x--) {
		for (int y = 0; y < x; y++) {

			// Swaping the elements if first one is greater than second one.
			if (luckyWhitePicked[y] > luckyWhitePicked[y + 1]){
				swap(luckyWhitePicked[y], luckyWhitePicked[y + 1]);
			}
		}
	}

	//print Lucky ball picks
	cout << "\nWhite Balls are: ";
	for (int num = 0; num < whitePicks; num++) {
		cout << luckyWhitePicked[num] << " ";
	}

}

void red() {
	int arrayRedBalls[redBalls] = {};

	//intial array adds numbers 1-26 to array
	int num = 1;
	for (int i = 0; i < redBalls; i++) {
		arrayRedBalls[i] = num;
		num++;
	}

	//Random lucky number position 0-25
	int randomNumber = rand() % (redBalls);
	//Actual number from position
	int powerBall = arrayRedBalls[randomNumber];
	

	//print Lucky ball picks
	cout << "Power Ball is: " << powerBall <<endl;
}