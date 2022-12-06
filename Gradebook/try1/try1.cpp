// Kiki Yem Assignment 5

#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>

using namespace std;

const int classSize = 75; // the maximum number of students in a class
const int bar = 60; // student needs to pass the minimum bar to enjoy the curve grade

enum Grade { F, D, CMINUS, C, CPLUS, BMINUS, B, BPLUS, AMINUS, A };

struct studentData {
	string lastName;
	string firstName;
	double score;
	Grade pointGrade;
	double percentage;
	Grade curveGrade;
	Grade finalGrade;
};

int grabData(string inputfilename, studentData student[]);
void outputGradeBook(string outfilename, studentData student[], int realSize);
void pointgrades(studentData student[], int realSize);
void percentSort(studentData student[], int realSize);
void ranking(studentData student[], int realSize);
void favorableGrading(studentData student[], int realSize);
void finalGrade(studentData student[], int realSize);
void alphabeticalSort(studentData student[], int realSize);
string letterGrade(Grade g);

int main()
{
	studentData student[classSize];

	//ask for input file name
	string  inputfilename;
	cout << "Enter the student grade data file: ";
	cin >> inputfilename;

	//real size of the input file (number of students), get data from file
	int realSize = grabData(inputfilename, student);

	pointgrades(student, realSize);
	percentSort(student, realSize);
	ranking(student, realSize);
	favorableGrading(student, realSize);
	finalGrade(student, realSize);
	alphabeticalSort(student, realSize);

	//Ask for output file name
	string  outfilename;
	cout << "Enter the gradebook file name: ";
	cin >> outfilename;

	outputGradeBook(outfilename, student, realSize);

	return 0;
}

//function to get data from input file, returns real Size (# of students in class)
int grabData(string inputfilename, studentData student[]) {
	fstream inputFile;
	inputFile.open(inputfilename, ios::in | ios::binary);

	int realSize = 0;
	while (inputFile >> student[realSize].lastName >> student[realSize].firstName >> student[realSize].score) {
		realSize++;
	}
	inputFile.close();
	return realSize;
}

//function to output grades
void outputGradeBook(string outfilename, studentData student[], int realSize) {
	ofstream outfile;
	outfile.open(outfilename, ios::out | ios::binary);

	int formatnum = 7;
	int formatname = 16;
	outfile << left 
				<< setw(formatname) << "Last Name"
				<< setw(formatname) << "First Name"
			<< right 
				<< setw(formatnum) << "Points"
				<<"\t"
			<< left
				<< setw(formatnum) << "Grade"
			<< right 
				<< setw(formatnum) << "Percent"
				<< "\t"
			<< left 
				<< setw(formatnum) << "Grade"
				<< setw(formatnum) << "Final"
			<< endl;

	for (int i = 0; i < realSize; i++) {
		outfile << fixed << setprecision(2);
		outfile << left 
				<< setw(formatname) << student[i].lastName
				<< setw(formatname) << student[i].firstName
				<< right 
					<< setw(formatnum) << student[i].score
					<< "\t"
				<< left
					<< setw(formatnum) << letterGrade(student[i].pointGrade)
				<< right 
					<< setw(formatnum) << student[i].percentage
					<< "\t"
				<< left
					<< setw(formatnum) << letterGrade(student[i].curveGrade)
					<< setw(formatnum) << letterGrade(student[i].finalGrade)
				<< endl;
	}
	outfile.close();
}

//Grade for points (un-curved)
void pointgrades(studentData student[], int realSize) {
	for (int i = 0; i < realSize; i++) {
		if (student[i].score > 93) {
			student[i].pointGrade = A;
		}
		else if (student[i].score > 90) {
			student[i].pointGrade = AMINUS;
		}
		else if (student[i].score > 87) {
			student[i].pointGrade = BPLUS;

		}
		else if (student[i].score > 83) {
			student[i].pointGrade = B;

		}
		else if (student[i].score > 80) {
			student[i].pointGrade = BMINUS;

		}
		else if (student[i].score > 77) {
			student[i].pointGrade = CPLUS;

		}
		else if (student[i].score > 73) {
			student[i].pointGrade = C;

		}
		else if (student[i].score > 70) {
			student[i].pointGrade = CMINUS;
		}
		else if (student[i].score >= 60) {
			student[i].pointGrade = D;
		}
		else if (student[i].score < 60) {
			student[i].pointGrade = F;
		}
	}
}
//Sort Functions
//sorts by score highest score to lowest then used for ranks
void percentSort(studentData student[], int realSize) {
	int minIndex;
	double minValue;
	for (int start = 0; start < (realSize - 1); start++) {
		minIndex = start;
		minValue = student[start].score;
		for (int sec = start + 1; sec < realSize; sec++) {
			if (student[sec].score > minValue) {
				minValue = student[sec].score;
				minIndex = sec;
			}
		}
		swap(student[minIndex], student[start]);
	}
}

//Sort according to last and first name used to display in output file
void alphabeticalSort(studentData student[], int realSize) {
	int minIndex;
	string minValue;
	string secondValue;
	for (int start = 0; start < (realSize - 1); start++) {
		minIndex = start;
		minValue = student[start].lastName + student[start].firstName;
		for (int sec = start + 1; sec < realSize; sec++) {
			secondValue = student[sec].lastName + student[sec].firstName;
			if (secondValue < minValue) {
				minValue = secondValue;
				minIndex = sec;
			}
		}
		swap(student[minIndex], student[start]);
	}
}

//for the percent ranking number
void ranking(studentData student[], int realSize) {
	double position = realSize;

	//sameScore counts the number of repeating scores
	int sameScore = 1;

	for (int i = 0; i < realSize; i++) {
		//figure out positions
		//if not the first student...
		if (i != 0) {
			//if score is less than the last student score
			if(student[i].score < student[i - 1].score) {
				position = position - sameScore;

				//score is not repeating so reset sameScore to 1
				sameScore = 1;
			}
			else if (student[i].score == student[i - 1].score) {
				//if scores are equal position stays the same as previous
				sameScore++;
			}
		}

		double ranks;
		//Determine rank: divides position number (received after sorting) of the student by the total number of students
		//student with the highest score has the highest position number
		ranks = position / realSize * 100;

		student[i].percentage = ranks;
	}
}

//For curved grade: uses percent score to calculate curved grade
void favorableGrading(studentData student[], int realSize) {
	for (int i = 0; i < realSize; i++) {
		if (student[i].percentage > 90) {
			student[i].curveGrade = A;
		}
		else if (student[i].percentage > 75) {
			student[i].curveGrade = AMINUS;
		}
		else if (student[i].percentage >= 60) {
			student[i].curveGrade = BPLUS;
		}
		else if (student[i].percentage > 45) {
			student[i].curveGrade = B;
		}
		else if (student[i].percentage > 35) {
			student[i].curveGrade = BMINUS;
		}
		else if (student[i].percentage > 25) {
			student[i].curveGrade = CPLUS;
		}
		else if (student[i].percentage > 15) {
			student[i].curveGrade = C;
		}
		else if (student[i].percentage > 10) {
			student[i].curveGrade = CMINUS;
		}
		else if (student[i].percentage >= 5) {
			student[i].curveGrade = D;
		}
		else if (student[i].percentage < 5) {
			student[i].curveGrade = F;
		}
	}
}

//Final Grade Calculation: Compares Curved and Un-curved grades
void finalGrade(studentData student[], int realSize) {
	for (int i = 0; i < realSize; i++) {
		if (student[i].score < bar ) {
			//Student gets F grade if their un-curved grade is below 60
			student[i].finalGrade = F;
		}
		else if (student[i].curveGrade > student[i].pointGrade) {
			student[i].finalGrade = student[i].curveGrade;
		}
		else {
			student[i].finalGrade = student[i].pointGrade;

		}
	}
}

//Converts enumerated data to string used to display grade in ouput file
string letterGrade(Grade g)
{
	string s;
	switch (g)
	{
	case F: s = "F";
		break;
	case D: s = "D";
		break;
	case CMINUS: s = "C-";
		break;
	case C: s = "C";
		break;
	case CPLUS: s = "C+";
		break;
	case BMINUS: s = "B-";
		break;
	case B: s = "B";
		break;
	case BPLUS: s = "B+";
		break;
	case AMINUS: s = "A-";
		break;
	case A: s = "A";
		break;
	default: s = "Error";
	}
	return s;
}
