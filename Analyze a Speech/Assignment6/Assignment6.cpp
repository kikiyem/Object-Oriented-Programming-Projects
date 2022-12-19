// A program that analyzes a speech in text for its word count, and phrase frequencies.

#include "Header.h"

//global variable
int word_count = 0;
int adjacent;
int uniquePhrases = 0;

const int MAX_WORDS = 5000;
const int MAX_W = 3000;

//functions
void grabData(string inputfilename, MyString words[]);
void getPhrases(MyString words[], MyString phrases[]);
void swap(MyString& x, MyString& y);
void selectionSort(MyString phrases[], int n);
void output(string outfilename, MyString phrases[]);

int main() {

	string inputfilename, outfilename;
	MyString words[MAX_WORDS];
	MyString phrases[MAX_W];

	cout << "Enter the source data file name: ";
	cin >> inputfilename;

	cout << "How many Adjacent words in a phrase, enter 1-5: ";
	cin >> adjacent;

	cout << "Enter the phrase frequency file name: ";
	cin >> outfilename;

	grabData(inputfilename, words);
	getPhrases(words, phrases);
	selectionSort(phrases, uniquePhrases);
	output(outfilename, phrases);

	return 0;
}


void grabData(string inputfilename, MyString words[]) {
	ifstream inputFile;
	inputFile.open(inputfilename, ios::in | ios::binary);

	//creates array of all the words being read
	MyString word;
	while (inputFile >> word) {

		word.ToUpper();

		words[word_count] = word;
		words[word_count].setFrequency(1);
		word_count++;
	}
	inputFile.close();

}

void getPhrases(MyString words[], MyString phrases[]) {

	MyString full;
	int times = 0;


	do {
		//create the full phrase
		//times is the index of the first word in the phrase
		full = words[times];
		for (int t = 1; t < adjacent; t++) {
			full = full + words[t + times];
		}

		//Linear search to check if the phrase is already in array
		bool found = false;
		for (int i = 0; i < uniquePhrases; i++) {
			if (full == phrases[i]) {
				found = true;
				// If found add 1 to frequency
				phrases[i].setFrequency(phrases[i].getFrequency() + 1);
				break;
			}
		}

		// If not found, add phrase to array
		if (!found) {
			phrases[uniquePhrases] = full;
			phrases[uniquePhrases].setFrequency(1);
			uniquePhrases++;
		}
		times++;

	} while (times < (word_count - adjacent + 1));
}

// Swap function used in selection sort
void swap(MyString& x, MyString& y) {
	MyString temp = x;
	x = y;
	y = temp;
}

// A function to implement selection sort max to min
void selectionSort(MyString phrases[], int n) {
	MyString maxString;

	for (int i = 0; i < n - 1; i++) {
		int maxIndex = i;
		maxString = phrases[i];
		for (int j = i + 1; j < n; j++) {
			if (phrases[j] > maxString) {
				maxString = phrases[j];
				maxIndex = j;
			}
		}
		swap(phrases[maxIndex], phrases[i]);
	}
}


void output(string outfilename, MyString phrases[]) {

	ofstream outfile;
	outfile.open(outfilename, ios::out | ios::binary);

	outfile << "The file: " << outfilename << " contains " << word_count << " Words." << endl;
	outfile << "There are " << uniquePhrases << " unique terms." << endl;
	outfile << endl;

	for (int z = 0; z < uniquePhrases; z++) {
		outfile << phrases[z] << endl;
	}

	outfile.close();
}
