#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0) ;
#include<iostream>
#include<string>
#define ll  long long
#define endl '\n'
#include"BigDecimalInt.h"
using namespace std;
int main() {
    BigDecimalInt n1("5980067"), n2(123467),n3=n2;
    cout <<"Frist number =" << n1<<"\nSecond number ="<<n2<<"\nThird number which is equal to second number ="<<n3;
    cout << "\nn1 + n2 =" << (n1 + n2) << "\nn1 - n2 =" << (n1 - n2) << "\nprint if(n2 == n3) "
        << (n2 == n3) << "\t Printif(n1 == n2) " << (n1 == n2);
    cout <<"\nif(n1 > n2)"<<(n1>n2)<<"\t if(n1 < n2)"<<(n1<n2);
}
