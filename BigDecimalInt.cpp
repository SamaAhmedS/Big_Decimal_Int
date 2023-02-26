#include"BigDecimalInt.h"
string addition(string num, string num2);
int greaterThan(string n1, string n2);
string subtraction(string num1, string num2);
BigDecimalInt BigDecimalInt ::operator+(BigDecimalInt anotherDec) {
	string num1 = num, num2 = anotherDec.getNum();
	string reslt;
	if (sign == '+' && anotherDec.sign == '+') {//both positive
		reslt+="+";
		reslt = addition(num1, num2);

	}
	else if (sign == '-' && anotherDec.sign == '-') {
		//both negative //  -num1 - num2
		reslt+= "-";
		reslt += addition(num1, num2);
	}
	else if ((anotherDec.sign == '-') && sign == '+') {
		//num2 is negative  //num1-num2
		if (num1 == num2) {
			reslt = "0";
		}
		else if (greaterThan(num1, num2)) {//num1>num2
			reslt = subtraction(num1, num2);
			reslt+= "+";
		}
		else {//num2>num1
			reslt += "-";
			reslt += subtraction(num2, num1);
		}
	}
	else if (sign == '-' && anotherDec.sign == '+') {
		//num1 is negative //num2-num1
		if (num1 == num2) {
			reslt = "0";
		}
		else if (greaterThan(num2, num1)) {//num2>num1
			reslt = subtraction(num2, num1);
		}
		else {//num1>num2
			reslt += "-";
			reslt += subtraction(num1, num2);
		}
	}
	BigDecimalInt sum(reslt);
	return sum;
}
//this function deal with two positive numbers
string addition(string num, string num2) {
	string result;
	int sz;
	if (num2.size() < num.size()) {
		result = num;
		sz = (num.size() - num2.size());
		while (sz--)
			num2.insert(num2.begin(), '0');
	}
	else {
		result = num2;
		sz = (num2.size() - num.size());
		while (sz--)
			num.insert(num.begin(), '0');
	}
	int cary = 0;
	for (int i = num.size() - 1; i > -1; i--) {
		int sum = ((num[i] - '0') + (num2[i] - '0'));// 297+ 346= 643
		if (sum > 9) {
			if (cary) sum++;
			sum -= 10;
			result[i] = char(sum + '0');
			cary = 1; i--;
			if (i >= 0) sum = ((num[i] - '0') + (num2[i] - '0'));
		}
		if (cary) {
			if (i < 0) {
				result.insert(result.begin(), '1');
			}
			else if ((sum + 1) <= 9) {
				sum++;
				result[i] = char(sum + '0');
				cary = 0;
			}
			else {
				sum -= 9;
				result[i] = char(sum + '0');
			}
		}
		else {
			result[i] = char(sum + '0');
		}
	}
	return result;
}

char indicateSign(string num, int& st) {
	int nNgsingn = 0;
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == '-') {
			nNgsingn++;
		}
		else if (num[i] == '+')continue;
		else {
			st = i;
			break;
		}
	}
	if (nNgsingn % 2 == 0) {
		//this mean that number of negative sign is even that mean, it is positive
		return '+';
	}
	return '-';
}
int greaterThan(string n1, string n2) {
	if (n1.size() > n2.size())
		return 1;
	else if (n2.size() > n1.size())
		return 0;
	else {
		return(n1 > n2);
	}
}

string subtraction(string num1, string num2) {
	if (num2.size() < num1.size()) {
		int sz = num1.size() - num2.size();
		while (sz--) {
			num2.insert(num2.begin(), '0');
		}
	}
	string result = num1;
	for (int i = num1.size() - 1; i > -1; i--) {
		int sub = (num1[i] - '0') - (num2[i] - '0');
		if (sub > -1) {
			result[i] = char(sub + '0');
		}											//2000 -48
		else if (i > 0 && (num1[i - 1] - '0') > 0) {//199-048   =1952
			sub += 10;
			result[i] = char(sub + '0');
			num1[i - 1]--;
		}
		else {
			sub += 10;
			result[i] = char(sub + '0');
			num1[i - 1] += 9;//0
			for (int j = i - 2; j > -1; j--) {
				if ((num1[j] - '0') > 0) {
					num1[j]--;
					break;
				}
				else {
					num1[j] += 9;
				}
			}
		}
	}
	while (*result.begin() == '0')
	{
		result.erase(result.begin());
	}
	return result;
}


//cases:
//both positive(num1-num2)//num1 negative(-num1-num2)
//both negative(-num1-(-num2))=num2-num1 //num2 negative(num1-(-num2)) = num1 + num2  
BigDecimalInt BigDecimalInt :: operator-(BigDecimalInt anotherDec) {
	string num1 = num, result, num2 = anotherDec.getNum();//num1-num2
	if (sign == '+' && anotherDec.sign == '+') {
		//both positive  //num1-num2
		if ((num1.size() == num2.size()) && (num1 == num2))
			result = "0";
		else if (greaterThan(num1, num2)) { //num1>num2
			result = subtraction(num1, num2);
		}
		else {//num2>num1
			result += "-";
			result += subtraction(num2, num1);
		}
	}
	else if (sign == '+' && anotherDec.sign == '-') {
		//num1+num2 //num2 is negative, so subtraction has converted to addition 
		result = addition(num1, num2);
	}
	else if (sign == '-' && anotherDec.sign == '+') {//-num1-num2
		//num1 is negative, so subtraction has converted to addition of two negative numbers
		result += "-";
		result += addition(num1, num2);
	}
	else if (sign == '-' && anotherDec.sign == '-') {
		//both negative num2 - num1
		if ((num1.size() == num2.size()) && (num1 == num2))
			result = "0";
		else if (greaterThan(num2, num1)) { //num2>num1
			result = subtraction(num2, num1);
		}
		else {//num1>num2
			result += "-";
			result += subtraction(num1, num2);
		}
	}
	BigDecimalInt sub(result);
	return sub;
}

bool BigDecimalInt :: operator< (BigDecimalInt anotherDec) {
	string num2 = anotherDec.getNum(), num1 = num;
	int st1 = 0, st2 = 0;
	//if(num < num2) 
	if (sign == '-' && anotherDec.sign == '+')
		return 1;
	else if (sign == '+' && anotherDec.sign == '-')
		return 0;
	if (sign == '+' && anotherDec.sign == '+') {
		if (greaterThan(num2, num1))//num2 > num1
			return 1;
		else
			return 0;
	}
	else if (sign == '-' && anotherDec.sign == '-') {
		if (greaterThan(num2, num1))//num2 > num1
			return 0;
		else
			return 1;
	}
	return 0;// equal
}


bool BigDecimalInt :: operator> (BigDecimalInt anotherDec) {
	//if( num1>num2)
	string num2 = anotherDec.getNum(), num1 = num;
	int st1 = 0, st2 = 0;
	if ((!indicateSign(num2, st2)) && indicateSign(num, st1))
		return 1;
	else if ((!indicateSign(num1, st1)) && indicateSign(num2, st2))
		return 0;
	//the following 2 steps are for  removing sign
	num1 = num1.substr(st1, num1.size());
	num2 = num2.substr(st2, num2.size());
	if (sign == '+' && anotherDec.sign == '+') {
		if (greaterThan(num1, num2))//num1 > num2
			return 1;
		else
			return 0;
	}
	else if (sign == '-' && anotherDec.sign == '-') {
		if (greaterThan(num2, num1))//num2 > num1
			return 1;
		else
			return 0;
	}
	return 0;// equal
}

bool BigDecimalInt :: operator== (BigDecimalInt anotherDec) {
	string num1 = num, num2 = anotherDec.getNum();
	int st1 = 0, st2 = 0;
	// check equality of signs
	if (sign != anotherDec.sign)
		return 0;
	if (num1.size() != num2.size())
		return 0;
	//both are equal in sign and size
	else {
		if (num1 == num2)
			return 1;
		return 0;
	}
}

BigDecimalInt& BigDecimalInt :: operator= (BigDecimalInt anotherDec) {
	num = anotherDec.getNum();
	sign = anotherDec.sign;
	return *this;
}
ostream& operator << (ostream& out, BigDecimalInt b) {
	out << b.sign << b.num;
	return out;
}

char BigDecimalInt::Sign() {
	return sign;
}

int BigDecimalInt::size() {
	return num.size();
}



//// FCAI – Object-Oriented Programming 1 – 2022 - Assignment 1
//// Program Name: BigDecimalInt
//// Last Modification Date: 13/10/2022
//// Author1 and ID and Group: Basmala Mohamed Sayed Gad  ID: 20210090 (a, b, c)
//// Author2 and ID and Group: Aya Ali Hassan  ID: 20210083 (d, e)
//// Author3 and ID and Group: Mohamed Ashraf Fahim  ID: 20210329 (f, i, j , k)
///*
//description: In this problem we developed a new C++ type (class).
//that can hold unlimited decimal integer values and performs arithmetic operations on them.
//such as: +, -, <, and >.
// */
//
//#include "BankAccount.h"
//
// // regex function that checks the validation of the input.
//bool BigDecimalInt::checkValidInput(string input)
//{
//    regex validInput("[-+]?[0-9]+");
//    return regex_match(input, validInput);
//}
//
//// constructor that takes a string as an input.
//void BigDecimalInt::setNumber(string num)
//{
//    bool validNumber = checkValidInput(num);
//    if (validNumber)
//    {
//        number = num;
//        if (number[0] == '+')
//        {
//            number.erase(0, 1);
//            signNumber = '+';
//        }
//        else if (number[0] == '-')
//        {
//            number.erase(0, 1);
//            signNumber = '-';
//        }
//        else
//        {
//            signNumber = '+';
//        }
//    }
//    else
//    {
//        cout << "Invalid" << "\n";
//        exit(1);
//    }
//}
//
//// operator < overloading function.
//bool BigDecimalInt :: operator < (const BigDecimalInt& anotherDec)
//{
//    string comp1 = "", comp2 = "";
//    long long len1 = number.length(), len2 = anotherDec.number.length();
//
//    while (len1 < len2) {
//        comp1 += '0';
//        len1++;
//    }
//    while (len2 < len1) {
//        comp2 += '0';
//        len2++;
//    }
//    comp1 += number;
//    comp2 += anotherDec.number;
//
//    if (signNumber == '-' && anotherDec.signNumber == '+')
//    {
//        return true;
//    }
//    else if (signNumber == '+' && anotherDec.signNumber == '-')
//    {
//        return false;
//    }
//    else if (signNumber == '+' && anotherDec.signNumber == '+')
//    {
//        return comp1 < comp2;
//    }
//    else
//    {
//        return comp1 > comp2;
//    }
//}
//
//// operator > overloading function.
//bool BigDecimalInt :: operator > (const BigDecimalInt& anotherDec)
//{
//    string comp1 = "", comp2 = "";
//    long long len1 = number.length(), len2 = anotherDec.number.length();
//
//    while (len1 < len2) {
//        comp1 += '0';
//        len1++;
//    }
//    while (len2 < len1) {
//        comp2 += '0';
//        len2++;
//    }
//    comp1 += number;
//    comp2 += anotherDec.number;
//
//    if (signNumber == '-' && anotherDec.signNumber == '+')
//    {
//        return false;
//    }
//    else if (signNumber == '+' && anotherDec.signNumber == '-')
//    {
//        return true;
//    }
//    else if (signNumber == '+' && anotherDec.signNumber == '+')
//    {
//        return comp1 > comp2;
//    }
//    else
//    {
//        return comp1 < comp2;
//    }
//}
//
//// operator == overloading function.
//bool BigDecimalInt :: operator == (const BigDecimalInt anotherDec)
//{
//    if (signNumber == anotherDec.signNumber && number == anotherDec.number)
//    {
//        return true;
//
//    }
//    else
//    {
//        return false;
//    }
//}
//
//// operator = overloading function.
//BigDecimalInt& BigDecimalInt :: operator = (BigDecimalInt anotherDec)
//{
//    signNumber = anotherDec.signNumber;
//    number = anotherDec.number;
//    return *this;
//}
//
////addition implementation.
//string addition(string num1, string num2)
//{
//    auto it1 = num1.rbegin();
//    auto it2 = num2.rbegin();
//    string res = "";
//    int carry = 0;
//    while (it1 != num1.rend())
//    {
//        int twoDigitsSum;
//        carry = 0;
//        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
//        if (twoDigitsSum >= 10)
//        {
//            carry = 1;
//        }
//        res = char((twoDigitsSum % 10) + '0') + res;
//        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
//        it1++;
//        it2++;
//    }
//    if (carry)
//    {
//        res = char((carry)+'0') + res;
//    }
//    return res;
//}
//
////subtraction implementation
//string subtraction(string num1, string num2) {
//    deque<long long>d;
//    string res;
//
//    for (long long i = num1.length() - 1; i >= 0; i--)
//    {
//        if (num1[i] < num2[i])
//        {
//            num1[i] = char(((num1[i] - '0') + 10) + '0');
//            num1[i - 1] = char(((num1[i - 1] - '0') - 1) + '0');
//            d.push_front((num1[i] - '0') - (num2[i] - '0'));
//        }
//        else
//        {
//            d.push_front((num1[i] - '0') - (num2[i] - '0'));
//        }
//    }
//
//    for (auto i : d)
//    {
//        res += to_string(i);
//    }
//    return res;
//}
//
//// // operator + overloading function.
//BigDecimalInt BigDecimalInt :: operator + (BigDecimalInt number2)
//{
//    BigDecimalInt result;
//    char signNumber1 = signNumber, signNumber2 = number2.signNumber;
//    string num1 = number, num2 = number2.number;
//    BigDecimalInt number1 = *this;
//
//    while (num1.length() < num2.length()) {
//        num1 = '0' + num1;
//    }
//    while (num2.length() < num1.length()) {
//        num2 = '0' + num2;
//    }
//
//    if (signNumber1 == signNumber2) {
//        result.signNumber = signNumber1;
//        result.number = addition(num1, num2);
//
//    }
//    else {
//
//        if (number1.signNumber == '-')
//        {
//            number1.signNumber = '+';
//            result = (number2 - number1);
//        }
//        else {
//            number2.signNumber = '+';
//            result = (number1 - number2);
//        }
//    }
//    return result;
//}
//
//// operator - overloading function.
//BigDecimalInt BigDecimalInt :: operator - (BigDecimalInt anotherDec)
//{
//    BigDecimalInt obj;
//    deque<long long> d;
//    string strmin = "", res = "";
//    string num1 = number, num2 = anotherDec.number;
//    char sign1 = signNumber, sign2 = anotherDec.signNumber;
//
//    if (number.length() > anotherDec.number.length())
//    {
//        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++)
//        {
//            strmin += '0';
//        }
//        strmin += anotherDec.number;
//        num2 = strmin;
//    }
//    else if (number.length() < anotherDec.number.length())
//    {
//        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++)
//        {
//            strmin += '0';
//        }
//        strmin += number;
//        num1 = strmin;
//    }
//
//    bool ok = false, is_determined = false;
//    if (num1 < num2)
//    {
//        swap(num1, num2);
//        swap(sign1, sign2);
//        ok = true;
//    }
//
//    if (sign1 == sign2)
//    {
//        res = subtraction(num1, num2);
//
//        if (sign1 == '-')ok = !ok;
//    }
//    else
//    {
//        res = addition(num1, num2);
//        if (signNumber == '-')
//        {
//            obj.signNumber = '-';
//            is_determined = true;
//        }
//        else
//        {
//            obj.signNumber = '+';
//            is_determined = true;
//        }
//
//    }
//
//    bool right = false;
//    for (long long i = 0; i < res.length(); i++)
//    {
//        if (res[i] != '-' && res[i] != '0')
//        {
//            right = true;
//        }
//        if (!right && res[i] == '0')
//        {
//            res.erase(i, 1);
//            i--;
//        }
//    }
//
//    if (res.empty()) res = "0";
//    if (!is_determined && (ok))
//    {
//        obj.signNumber = '-';
//    }
//    else if (!is_determined)
//    {
//        obj.signNumber = '+';
//    }
//
//    obj.number = res;
//    return obj;
//}
//
//// function to return the size of number.
//int BigDecimalInt::size()
//{
//    return number.size();
//}
//
//// function returns the sign.
//int BigDecimalInt::sign()
//{
//    if (signNumber == '+')
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//}
//
//// operator << overloading function.
//ostream& operator << (ostream& out, BigDecimalInt num)
//{
//    if (num.signNumber == '+')
//    {
//        out << num.number;
//    }
//    else
//    {
//        if (num.number == "0")
//        {
//            out << num.number;
//        }
//        else
//        {
//            out << num.signNumber << num.number;
//        }
//    }
//    return out;
//}