//     This program reads test scores from a file. Then shows the total 
//     score for each test, each student, average result, 
//     as well as the top student.
//
//****************************************************************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const int NUM_TESTS = 8;
const int NUMSTDS = 10;


void readTestScores(const string&, int[][NUM_TESTS], int);
void displayTestScores(const int[][NUM_TESTS], int);
int totalOneTest(const int[][NUM_TESTS], int, int);
int totalOneStudent(const int[][NUM_TESTS], int, int);
double averageOneTest(const int[][NUM_TESTS], int, int);
double averageOneStudent(const int[][NUM_TESTS], int, int);
int highestOneStudent(const int[][NUM_TESTS], int, int);
int topStudent(const int[][NUM_TESTS], int);
bool searchStudents(const int[][NUM_TESTS], int, double);
bool searchTests(const int[][NUM_TESTS], int, double);

//****************************************************************************************************

int main()
{
	int scores[NUMSTDS][NUM_TESTS];
	int testNumber = 8,
		studentNumber = 1;
	double average = 0;
	const string fileName = "GradesData.txt";

	readTestScores(fileName, scores, NUMSTDS);
	displayTestScores(scores, NUMSTDS);

	cout << "Press Enter to Continue..." << endl;
	cin.get(); // Wait for Enter key

	cout << fixed << setprecision(2);

	for (int i = 0; i < NUM_TESTS; i++)
	{
		cout << "Total for Test #" << (i + 1) << " is: " 
			<< totalOneTest(scores, NUMSTDS, i + 1) << endl;
	}

	cout << "Press Enter to Continue..." << endl;
	cin.get();

	for (int i = 0; i < NUM_TESTS; i++)
	{
		cout << "Average for Test #" << (i + 1) << ": " 
			<< averageOneTest(scores, NUMSTDS, i + 1) << endl;
	}

	cout << "Press Enter to Continue..." << endl;
	cin.get();

	for (int i = 0; i < NUMSTDS; i++)
	{
		cout << "Total for Student #" << (i + 1) << " is: " 
			<< totalOneStudent(scores, NUMSTDS, i + 1) << endl;
	}

	cout << "Press Enter to Continue..." << endl;
	cin.get(); 

	for (int i = 0; i < NUMSTDS; i++)
	{
		cout << "Average for Student #" << (i + 1) << ": " 
			<< averageOneStudent(scores, NUMSTDS, i + 1) << endl;
	}

	cout << "Press Enter to Continue..." << endl;
	cin.get(); 

	for (int i = 0; i < NUMSTDS; i++)
	{
		cout << "Highest test score for Student #" << (i + 1) << ": " 
			<< highestOneStudent(scores, NUMSTDS, i + 1) << endl;
	}

	cout << "Press Enter to Continue..." << endl;
	cin.get(); 

	int top = topStudent(scores, NUMSTDS);
	cout << "The top Student: Student #" << top << endl;

	cout << "Enter the average score." << endl;
	cin >> average;
	cin.get();
	bool studentFound = searchStudents(scores, NUMSTDS, average);

	cout << "Press Enter to Continue..." << endl;
	cin.ignore(); 
	
	bool testFound = searchTests(scores, NUMSTDS, average);
	cout << "Press Enter to Continue..." << endl;
    cin.ignore(); 

	return 0;
}

//****************************************************************************************************

//Read all test scores from the file and store in the array
void readTestScores(const string& fileName, int scores[][NUM_TESTS], 
	int NUMSTDS)
{
	ifstream GradesData_file(fileName);

	if (!GradesData_file) 
	{
		cout << "Unable to open file " << fileName << endl;
		return;
	}

	for (int i = 0; i < NUMSTDS; i++) 
	{
		for (int j = 0; j < NUM_TESTS; j++) 
		{
			if (!(GradesData_file >> scores[i][j])) 
			{
				cout << "Failed to read data from file " << fileName << endl;
				GradesData_file.close();
				return;
			}
		}
	}

	GradesData_file.close();
}


//****************************************************************************************************

//Display all test scores stored in the array
void displayTestScores(const int scores[][NUM_TESTS], int NUMSTDS)
{
	cout << "Test Scores: " << endl;
	for (int i = 0; i < NUMSTDS; i++) 
	{
		for (int j = 0; j < NUM_TESTS; j++) 
		{
			cout << scores[i][j] << " ";
		}
		cout << endl;
	}	
}

//****************************************************************************************************

//Return the total for the test specified in the third argument
int totalOneTest(const int scores[][NUM_TESTS], int NUMSTDS, int testNumber)
{
	int total = 0;
	for (int i = 0; i < NUMSTDS; i++) 
	{
		total += scores[i][testNumber - 1];
	}
	return total;
}

//****************************************************************************************************

//Return the total for the student specified in the third argument
int totalOneStudent(const int scores[][NUM_TESTS], int NUMSTDS,
	int studentNumber)
{
	int total = 0;
	for (int j = 0; j < NUM_TESTS; j++) 
	{
		total += scores[studentNumber - 1][j];
	}
	return total;
}

//****************************************************************************************************

//Return the average of the test specified in the third argument
double averageOneTest(const int scores[][NUM_TESTS], int NUMSTDS, 
	int testNumber)
{
	int total = totalOneTest(scores, NUMSTDS, testNumber);
	return static_cast<double>(total) / NUMSTDS;
}

//****************************************************************************************************

//Return the average for the student specified in the third argument
double averageOneStudent(const int scores[][NUM_TESTS], int NUMSTDS,
	int studentNumber)
{
	int total = totalOneStudent(scores, NUMSTDS, studentNumber);
	return static_cast<double>(total) / NUM_TESTS;
}

//****************************************************************************************************

//Return the highest result for the student specified in the third argument
int highestOneStudent(const int scores[][NUM_TESTS], int NUMSTDS,
	int studentNumber)
{
	int highestScore = scores[studentNumber - 1][0];
	for (int j = 1; j < NUM_TESTS; ++j) 
	{
		if (scores[studentNumber - 1][j] > highestScore) 
		{
			highestScore = scores[studentNumber - 1][j];
		}
	}
	return highestScore;
}

//****************************************************************************************************

//Return the Student number with the highest average test score
int topStudent(const int scores[][NUM_TESTS], int NUMSTDS)
{
	double highestAverage = averageOneStudent(scores, NUMSTDS, 1);
	int topStudent = 1;
	for (int i = 2; i <= NUMSTDS; i++) 
	{
		double studentAverage = averageOneStudent(scores, NUMSTDS, i);
		if (studentAverage > highestAverage) 
		{
				highestAverage = studentAverage;
				topStudent = i;
		}
	}

	return topStudent;
}

//****************************************************************************************************

bool searchStudents(const int scores[][NUM_TESTS], int NUMSTDS, double average)
{
	for (int i = 0; i < NUMSTDS; i++)
	{
		double studentAverage = averageOneStudent(scores, NUMSTDS, i+1);
		if (studentAverage > average)
		{
			cout << "A student has an average score greater than " << average << ": " 
				<< studentAverage << endl;
			return true;
		}
	}

	cout << "No student has an average score greater than " << average << endl;
	return false;
}


bool searchTests(const int scores[][NUM_TESTS], int NUMSTDS, double average)
{
	for (int i = 0; i < NUM_TESTS; i++)
	{
		double testAverage = averageOneTest(scores, NUMSTDS, i++);
		if (testAverage > average)
		{
			cout << "A test has an average score greater than " << average << ": " 
				<< testAverage << endl;
			return true;
		}
	}

	cout << "No test has an average score greater than " << average << endl;
	return false;
}

/*
Test Scores:
87 90 65 45 88 89 75 80
89 85 78 56 90 91 99 82
80 90 72 95 99 66 77 88
90 65 80 98 99 76 77 88
55 75 66 99 99 56 87 86
30 60 80 90 99 56 67 88
90 55 95 35 98 86 37 88
99 97 99 98 98 96 87 83
90 65 80 98 99 76 87 88
35 75 60 99 99 56 87 88
Press Enter to Continue...

Total for Test #1 is: 745
Total for Test #2 is: 757
Total for Test #3 is: 775
Total for Test #4 is: 813
Total for Test #5 is: 968
Total for Test #6 is: 748
Total for Test #7 is: 780
Total for Test #8 is: 859
Press Enter to Continue...

Average for Test #1: 74.50
Average for Test #2: 75.70
Average for Test #3: 77.50
Average for Test #4: 81.30
Average for Test #5: 96.80
Average for Test #6: 74.80
Average for Test #7: 78.00
Average for Test #8: 85.90
Press Enter to Continue...

Total for Student #1 is: 619
Total for Student #2 is: 670
Total for Student #3 is: 667
Total for Student #4 is: 673
Total for Student #5 is: 623
Total for Student #6 is: 570
Total for Student #7 is: 584
Total for Student #8 is: 757
Total for Student #9 is: 683
Total for Student #10 is: 599
Press Enter to Continue...

Average for Student #1: 77.38
Average for Student #2: 83.75
Average for Student #3: 83.38
Average for Student #4: 84.12
Average for Student #5: 77.88
Average for Student #6: 71.25
Average for Student #7: 73.00
Average for Student #8: 94.62
Average for Student #9: 85.38
Average for Student #10: 74.88
Press Enter to Continue...

Highest test score for Student #1: 90
Highest test score for Student #2: 99
Highest test score for Student #3: 99
Highest test score for Student #4: 99
Highest test score for Student #5: 99
Highest test score for Student #6: 99
Highest test score for Student #7: 98
Highest test score for Student #8: 99
Highest test score for Student #9: 99
Highest test score for Student #10: 99
Press Enter to Continue...

The top Student: Student #8
Enter the average score.
80
A student has an average score greater than 80.00: 83.75
Press Enter to Continue...

A test has an average score greater than 80.00: 81.30
Press Enter to Continue...

*/
