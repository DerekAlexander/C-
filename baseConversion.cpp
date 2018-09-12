//--------------------------------------------------------------
// Title : Formatted Numeric Table
// Author: Derek Alexander
// date  : 3/12/2017
// descr :
//			this program converts numbers to decimal, hexadecimal,
//			octal and binary.		
//
//----------------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int skipNums(int num)
{

	int number[] = { 64 , 128 , 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };

	return number[num];

}

static char digits(int num)
{

	static char digits [] = "0123456789ABCDEF";

	return digits[num];

}


//loops through remainder of num based on the base of 2. adds the char to the result and removes the digit until the number is 0
string convertToBinary(unsigned num, unsigned base = 2)
{

	string charNum;
	string result;

	do
	{

		charNum = digits(num % base);
		result = charNum + result;
		num = num / base;
	
	} 
	while (num > 0);
	return result;

}

//

int main()
{
	//spacing for heading and also seperating = line. 
	int x = 0;
	cout << setw(8) <<  right << setfill(' ') << "decimal";
	cout << setw(12) << right << setfill(' ') << "hexadecimal";
	cout << setw(15) << right << setfill(' ') << "octal";
	cout << setw(22) << right << setfill(' ') << "binary";
	cout << endl;
	cout << setw(75) << setfill('=') << "";
	cout << endl;

	
	cout << showbase << right << showpoint;

	//formats for dec hex oct and binary with spaced padding. 
	for (int num = 0; num < 33; num++)
	{

		cout << setw(8) << setfill(' ') << dec << num;

		cout << setw(6) << setfill(' ') << "" << hex;
		cout << internal << setw(6) << setfill('0') << num << right;

		cout << setw(15) << setfill(' ') << oct << num;


		cout << setw(22) << setfill(' ') << "0b" << convertToBinary(num);
		
		cout << endl;
		
	}

	cout << setw(75) << setfill('.') << "" << endl;

	for (int num = 0; num < 11; num++)
	{
		//the number - 1
		cout << setw(8) << setfill(' ') << dec;
		cout << skipNums(num) - 1;

		cout << setw(6) << setfill(' ') << "" << hex;
		cout << internal << setw(6) << setfill('0');
		cout <<skipNums(num) - 1 << right;

		cout << setw(15) << setfill(' ') << oct;
		cout <<skipNums(num) - 1;

		cout << setw(22) << setfill(' ');
		cout << "0b" << convertToBinary(skipNums(num) - 1) << endl;

		//the number itself no plus or minus
		cout << setw(8) << setfill(' ') << dec;
		cout <<skipNums(num);

		cout << setw(6) << setfill(' ') << "" << hex;
		cout << internal << setw(6) << setfill('0');
		cout << skipNums(num) << right;

		cout << setw(15) << setfill(' ') << oct;
		cout <<skipNums(num);

		cout << setw(22) << setfill(' ');
		cout << "0b" << convertToBinary(skipNums(num)) << endl;

		//the number + 1
		cout << setw(8) << setfill(' ') << dec;
		cout <<skipNums(num) + 1;

		cout << setw(6) << setfill(' ') << "" << hex;
		cout << internal << setw(6) << setfill('0');
		cout << skipNums(num) + 1 << right;

		cout << setw(15) << setfill(' ') << oct;
		cout << skipNums(num) + 1;

		cout << setw(22) << setfill(' ');
		cout << "0b" << convertToBinary(skipNums(num) + 1) << endl;

		cout << setw(75) << setfill('.') << "" << endl;

	}
}
