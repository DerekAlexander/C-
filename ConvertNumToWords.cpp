//--------------------------------------------------------------
// Title : convertNumToWordsv3
// Author: Derek Alexander
// date  : 3/5/2017
// descr :
//			This is a program that takes an infintely large dollar/cent
//			numeric amount and converts it to words. and adds any needed
//			appedixies, signs or prefixes to the returned words. 
//			
//----------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std;

//gets the value left of the decimal place by casting the num to an int. 
int getsDollars(double num)
{

	return num;

}

//gets the value right of the decimal place. and converts it 
//to a whole number to work with as an int later on. 
int getsCents(double num)
{

	int result;
	double dResult;

	dResult = num - getsDollars(num);
	result = dResult * 100;
	return result;

}


//convert the ones place digit to the corelated word. 
string convertToWords(int num)
{


	static string stringDigit[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine", };

	return stringDigit[num];

}

//convert teen numbers to corelated word.  
string TeensToWords(int num)
{

	static string TeensToWords[] = { "" , "Eleven" , "Tweleve" , "Thirteen" , "Fourteen" , "Fifteen" ,
		"Sixteen" , "Seventeen" ,"Eightteen" , "Nineteen" };
	return TeensToWords[num];

}

//convert the tens place digit to the corelated word. 
string numPrefix(int num)
{

	static string stringPrefix[] = { "" , "Ten" , "Twenty" , "Thirty" , "Forty" , "Fifty" ,
		"Sixty" , "Seventy" ,"eighty" , "ninty" };
	return stringPrefix[num];

}

//adds appendixies for numbers larger than 999. 
string numAppendix(int num)
{

	static string stringAppendix[] = { "" , "Thousand", "Million", "Billion", "Trillion" };

	return stringAppendix[num];

}

int getThreeLowestDigits(int num)
{

	return num % 1000;

}

int removeThreeLowestDigits(int num)
{

	return num / 1000;

}

int getOnes(int num)
{

	num = num % 10;
	return num = num / 1;

}

int getTens(int num)
{

	num = num % 100;
	return num = num / 10;
}

int getHundereds(int num)
{

	num = num % 1000;
	return num = num / 100;

}

//creates a formatted string of numbers to words with all appendixies and prefixes from the three digits recieved.
string convertThreeDigitsToWords(int threeDigitNum, int counter)
{
	string result;
	string teenNum;
	string hundered;

	//check to see if three digits includes a teen number.
	if (((threeDigitNum % 100) > 10) && ((threeDigitNum % 100) < 20))
	{
		teenNum = TeensToWords(getOnes(threeDigitNum));
		removeThreeLowestDigits(getTens(threeDigitNum));

	}

	//adds a "hundered" word if the hundereds place is not 0;
	if (getHundereds(threeDigitNum) != 0)
	{

		hundered = "hundered";

	}

	//checks if number is a teen and creates a string including teen numbers. 
	if (teenNum != "")
	{

		result = convertToWords(getHundereds(threeDigitNum)) + " " + hundered + " " + teenNum + " " + numAppendix(counter);

	}

	//checks if number is less than 100 threfore does not need hundereds digit place or word. 
	else if (threeDigitNum < 100 && threeDigitNum != 0)
	{

		result = numPrefix(getTens(threeDigitNum)) + " " + convertToWords(getOnes(threeDigitNum)) + " " + numAppendix(counter);

	}

	//check if number is greater than 100 threfore needing hundered appended.
	else if (threeDigitNum >= 100)
	{

		result = convertToWords(getHundereds(threeDigitNum)) + " " + hundered + " " + numPrefix(getTens(threeDigitNum))
			+ " " + convertToWords(getOnes(threeDigitNum)) + " " + numAppendix(counter);

	}

	return result;
}

//loops through the number in three digit segments to create the entire string of numbers to words. 
string convertNumToWords(int userNumber)
{
	string result;
	int appendixCounter = 0;

	if (userNumber == 0)
		return "Zero";

	if (userNumber < 0)
		return 0;

	while (userNumber > 0)
	{

		int threeDigits = getThreeLowestDigits(userNumber);

		string words = convertThreeDigitsToWords(threeDigits, appendixCounter);

		if (userNumber > 999) appendixCounter++;

		userNumber = removeThreeLowestDigits(userNumber);

		result = words + result;

	}

	return result;

}
//takes in the users input, puts it through number coverting functions, and lastly combines everything together formatted.
int main()
{

	double amount;
	do
	{

		cout << "enter a dollar amount: ";
		cin >> amount;
		//checks if number is small enough for to fit in a double but not a negative. 
		if (amount < 0.00 || amount > 399999999.99)
		{

			cin.clear();
			cout << "the Number you have entered is out of bounds only numbers between 0 and 3,999,999,999.99 may be entered. " << endl;
			continue;

		}

		//checks if the user failed.
		if (cin.fail())
		{

			cin.clear();

			string errstr;

			cin >> errstr;

			cout << "you entered [" << errstr << "] only numbers and one decimal place may be entered. please try again using a number like: 123.56 " << endl;

			continue;
		}

		cout << fixed << setprecision(2) << setfill('0');

		if (getsCents(amount) == 1)
		{
			cout << "$" << amount << " " << convertNumToWords(getsDollars(amount)) << " dollars" << " and " << convertNumToWords(getsCents(amount)) << "cent";
		}
		else
		{
			cout << "$" << amount << " " << convertNumToWords(getsDollars(amount)) << " dollars" << " and " << convertNumToWords(getsCents(amount)) << "cents";
		}

		cout << setfill(' ') << setw(2) << endl;

	} while (true);

}
