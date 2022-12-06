// Assignment3

#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>

using namespace std;


int length(double);
void printCurrencyFormat(ofstream& o, int d, double x, int space, int position);
const int space = 12;

int main(){

	double loanAmount, annualInterest, numberOfYears, additionalPrincipal;
	const int frequency = 12;
	const int loanLowerbound = 0;
	const int loanUpperbound = 9999999;
	const int maxInterest = 30;
	const int minYears = 1;
	const int maxYears = 99;
	

	//ask and checks input
	do {
		cout << "Enter Loan amount (0-9999999), for example 300000.90: ";
		cin >> loanAmount;
	} while (loanAmount <= loanLowerbound || loanAmount > loanUpperbound);

	do {
		cout << "Enter annual interest rate (0-30), for example 4.25 meaning 4.25%: ";
		cin >> annualInterest;
	} while (annualInterest <= loanLowerbound || annualInterest > maxInterest);

	do {
		cout << "Enter no. of years as integer (1-99), for example 30: ";
		cin >> numberOfYears;
	} while (numberOfYears < minYears || numberOfYears > maxYears);

	do {
		cout << "Enter additional principal per month (0-9999999), for example 300: ";
		cin >> additionalPrincipal;
	} while (additionalPrincipal < loanLowerbound || additionalPrincipal > loanUpperbound);

	//monthlyPayment Calculation

	//annualInterestRate (percent) = annualInterest/100
	//monthly Interest (percent) = annualInterestRate  / 12
	double monthlyInterestRate = ((annualInterest / 100) / frequency);

	double monthlyPayment = (loanAmount * monthlyInterestRate) / (1 - (1 / pow(1 + monthlyInterestRate, numberOfYears * frequency)));
	double actualPayment = monthlyPayment + additionalPrincipal;

	
	//output file
	ofstream outfile;
	string outfilename;

	cout << "Send the mortgage amortization table to a file (enter file name): ";
	cin >> outfilename;
	outfile.open(outfilename);

	
	outfile << endl << endl << endl;
	outfile << setw(34) << "MORTGAGE AMORTIZATION TABLE" << "\n" << endl;

	outfile << left << setw(24) << "Amount:";
	printCurrencyFormat(outfile, 1, loanAmount, space, 1);
	outfile << endl;

	outfile << left << setw(24) << "Interest Rate:" << int(annualInterest) << "%" << endl;

	outfile << left << setw(24) << "Term(Years):" << int(numberOfYears) << endl;

	outfile << left << setw(24) << "Monthly Payment:";
	printCurrencyFormat(outfile, 1, monthlyPayment, space, 1);
	outfile << endl;

	outfile << left << setw(24) << "Additional Principal:";
	printCurrencyFormat(outfile, 1, additionalPrincipal, space, 1);
	outfile << endl;

	outfile << left << setw(24) << "Actual Payment:";
	printCurrencyFormat(outfile, 1, actualPayment, space, 1);
	outfile << endl;
	outfile << endl;

	outfile << right << setw(18) << "Principal" << setw(18) << "Interest" << setw(18) << "Balance" << endl;

	//set intial remaining balance to loan amount
	double remainingBalance = loanAmount;
	int period = 1;

	while (remainingBalance > 0) {
		//double interestPayment = remainingBalance * monthlyInterestRate;
		//double principalPayment = actualPayment - interestPayment;
		//new remainingBalance = previous period remainingBalance - current period principalPayment
		double interestPayment = remainingBalance * monthlyInterestRate;
		double principalPayment;
		if (remainingBalance > actualPayment) {
			principalPayment = actualPayment - interestPayment;
			remainingBalance = remainingBalance - principalPayment;
		}
		else {
			principalPayment = remainingBalance;
			remainingBalance = principalPayment - remainingBalance;
		}

		if (period == 1) {
			outfile << left << setw(6) << period;
			printCurrencyFormat(outfile, 1, principalPayment, space, 1);
			printCurrencyFormat(outfile, 1, interestPayment, space, 2);
			printCurrencyFormat(outfile, 1, remainingBalance, space, 3);
			outfile << endl;
		}
		else {
			outfile << left << setw(6) << period;
			printCurrencyFormat(outfile, 2, principalPayment, space, 1);
			printCurrencyFormat(outfile, 2, interestPayment, space, 2);
			printCurrencyFormat(outfile, 2, remainingBalance, space, 3);
			outfile << endl;
		}

		//add to period number
		period++;

	}
	outfile.close();

	return 0;
}

//print final number
void printCurrencyFormat(ofstream& o, int d, double x, int space, int position) {

	// position is position on the file 1 for left, 2 for center, 3 for right-justified
	//switch checks/displays for the position the number should be
	switch (position) {
	case 1:
		o << "";
		break;
	case 2:
		o << "     ";
		break;
	case 3:
		o << "     ";
		break;
	}
	
	//Checks if d is 1 for $ or 2 for blank space to see if $ is needed
	if (d == 1) {
		// $ is needed
		o << "$";	
	}
	else if (d == 2) {
		//$ not needed
		o << " ";
	}
	

	//blank spaces left before the number = the number of max spaces (12) - spaces required for number x
	int amount = space - length(x);
	for (int i = amount; i > 0; i--) {
		o << " ";
	}

	//print comma number

	int integerPart, decimalPart, log, commas, integerPart2;
	o << fixed << setprecision(2);
	integerPart = int(x);
	decimalPart = (x - int(x)) * 100;
	
	//Number of decimal places until ones place 
	log = log10(integerPart);
	//Commas needed in number
	commas = log / 3;

	// Print number before comma then comma

	for (int i = 1; i <= commas; i++) {

		// number before comma = number/ number place value
		integerPart2 = integerPart / int(pow(10, i * 3));

		if (i == 1) {
			o << integerPart2;
		}// if after the first comma, then make sure number prints in the 000 format
		else {
			if (integerPart2 < 10) {
				o << "00" << integerPart2;
			}
			else if (integerPart2 < 100) {
				o << "0" << integerPart2;
			}
			else {
				o << integerPart2;
			}
		}
		//Comma
		o << ",";

		// integerPart =  remainder of (orginal integerPart/ number place value) gets rid of number already printed
		integerPart = integerPart % int(pow(10, i * 3));
	}


	//prints part of number before decimal 

	if (x == 0) {
		o << "0";
	}
	else if (commas == 0 && integerPart != 0) {
		o << integerPart;
	}
	else {
		//makes sure in 000 format
		if (integerPart < 10) {
			o << "00" << integerPart;
		}
		else if (integerPart < 100) {
			o << "0" << integerPart;
		}
		else {
			o << integerPart;
		}
	}
	// Print decimal part format .00
	o << ".";
	if (decimalPart == 0) {
		o << "00";
	}
	else if (decimalPart < 10) {
		o << "0" << decimalPart;
	}
	else {
		o << decimalPart;
	}

}

/* given in assignment: function for number of spaces needed to print a number with commas and two decimal places*/
int length(double n) {
	if (n >= 10) {
		int d = log10(n);
		return d + d / 3 + 4;
	}
	else {
		return 4;
	}
}
		

