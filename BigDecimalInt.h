#pragma once
#include <iostream>
#include<iomanip>
#include <sstream>
#include<vector>
#include<regex>
using namespace std;



char indicateSign(string num, int& st);
class BigDecimalInt {
	string num;
	char sign;
public:
	BigDecimalInt(string n) {
		regex validInput("[-+]*[0-9]+");
		if (!regex_match(n, validInput)) {
			exit(1);
		}
		int index = 0;
		if (n[0] >= 48) {
			if (n == "0") {
				sign = ' ';
			}
			else { sign = '+'; }
		}
		else {
			sign = indicateSign(n, index);
		}
		num = n.substr(index);
	}
	BigDecimalInt(int decInt) {
		if (decInt < 0) {
			sign = '-';
			decInt = -decInt;
		}
		else { sign = '+'; }
		num = to_string(decInt);
	}

	BigDecimalInt operator+(BigDecimalInt anotherDec);
	BigDecimalInt operator-(BigDecimalInt anotherDec);
	bool operator< (BigDecimalInt anotherDec);
	bool operator> (BigDecimalInt anotherDec);
	bool operator==(BigDecimalInt anotherDec);
	BigDecimalInt& operator= (BigDecimalInt anotherDec);
	friend ostream& operator << (ostream& out, BigDecimalInt b);
	string getNum() { return num; }
	char Sign();
	int size();
};





