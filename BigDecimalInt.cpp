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


