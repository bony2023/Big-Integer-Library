#include <iostream>
#include "BigInt.h"
using namespace std;

int main(void)
{
	BigInt Fib[5000+5];
	Fib[0]=0;
	Fib[1]=1;
	
	for(int i=2; i<=5000; i++)
	{
		Fib[i]=Fib[i-1]+Fib[i-2];
	}
	
	cout<<"5000th Fibonacci Number is = "<<Fib[5000]<<endl;
	
	return (0);
}