#include <algorithm>
#include <sstream>
#include <string>
#define MAX 10000
using namespace std;
#include "FFTM.h"

class BigInt
{
	string Number;
	bool sign; // True if Negative Number
	
	public:
	
	// Constructors
	BigInt();
	BigInt(string&);
	BigInt(BigInt&);
	BigInt(long long);
	
	// Operator Overloading
	// I/O
	friend istream& operator >>(istream&, BigInt&);
	friend ostream& operator <<(ostream&, BigInt&);
	
	// Comparision
	bool operator ==(const BigInt&);
	bool operator ==(const string&);
	bool operator != (const BigInt&);
	bool operator != (const string&);
	bool operator <(const BigInt&);
	bool operator >(const BigInt&);
	bool operator <=(const BigInt&);
	bool operator >=(const BigInt&);
	void operator =(int);
	void operator =(long long);
	
	// Arithmetic
	// Binary
	BigInt operator +(const BigInt&);
	BigInt operator -(const BigInt&);
	BigInt operator *(const BigInt&);
	BigInt operator /(const BigInt &);
	BigInt operator %(const BigInt&);
	// Unary
	BigInt operator ++(int);
	BigInt operator --(int);
	BigInt& operator ++();
	BigInt& operator --();
	BigInt operator -();
	void operator +=(const BigInt&);
	void operator -=(const BigInt&);
	void operator *=(const BigInt&);
	void operator /=(const BigInt&);
	void operator %=(const BigInt&);
	
	// Other Useful Functions
	friend BigInt gcd(BigInt, BigInt);
	friend BigInt pow(BigInt, int);
	friend BigInt factorial(long long);
	friend BigInt abs(BigInt);
	friend BigInt min(BigInt, BigInt);
	friend BigInt max(BigInt, BigInt);
	friend void swap(BigInt&, BigInt&);
};

BigInt::BigInt() // Default Constructor
{
	Number="0";
	sign=false;
}

BigInt::BigInt(string& x) // string to BigInt
{
	sign=false;
	Number=x;
	
	if(x[0]=='-')
	{
		sign=true;
		Number.erase(0, 1);
	}
}

BigInt::BigInt(BigInt& x) // Copy Constructor
{
	Number=x.Number;
	sign=x.sign;
}

BigInt::BigInt(long long x) // long long to BigInt
{
	(*this).sign=false;
	
	if(x<0)
	{
		x*=-1;
		(*this).sign=true;
	}
	
	stringstream S;
	S<<x;
	S>>(*this).Number;
}

istream& operator >>(istream& P, BigInt& x) // Input BigInt
{
	P>>x.Number;
	x.sign=false;
	
	if(x.Number[0]=='-')
	{
		x.sign=true;
		x.Number.erase(0, 1);
	}
	
	return P;
}

ostream& operator <<(ostream& P, BigInt& x) // Output BigInt
{
	if(x.sign) P<<"-";
	P<<x.Number;
	
	return P;
}

bool BigInt::operator ==(const BigInt& x) // IsEqualToBigInt
{
	if((*this).Number==x.Number && (*this).sign==x.sign)
	return true;
	
	return false;
}

bool BigInt::operator ==(const string& x) // isEqualToString
{
	string t=x;
	
	if(x[0]=='-')
	{
		t.erase(0, 1);
		
		if(!((*this).sign))
		return false;
	}
	else if((*this).sign)
	return false;
	else
	return ((*this).Number==t);
}

bool BigInt::operator !=(const BigInt& x) // notEqualBigInt
{
	return !((*this)==x);
}

bool BigInt::operator !=(const string& x) // notEqualString
{
	return !((*this)==x);
}

bool BigInt::operator <(const BigInt& x) // lessThan
{
	if((*this).sign && !x.sign)
	return true;
	else if((*this).sign==x.sign)
	{
		if(x.Number.size() != (*this).Number.size())
		{
			if(x.sign)
			return (*this).Number.size()>x.Number.size();
			else
			return (*this).Number.size()<x.Number.size();
		}
		else
		if(!x.sign)
		return (*this).Number<x.Number;
		else
		return x.Number<(*this).Number;
	}
	else
	return false;
}

bool BigInt::operator >(const BigInt& x) // greaterThan
{
	if(!((*this).sign) && x.sign)
	return true;
	else if((*this).sign==x.sign)
	{
		if(x.Number.size() != (*this).Number.size())
		{
			if(x.sign)
			return (*this).Number.size()<x.Number.size();
			else
			return (*this).Number.size()>x.Number.size();
		}
		else
		if(x.sign)
		return (*this).Number<x.Number;
		else
		return (*this).Number>x.Number;
	}
	else 
	return false;
}

bool BigInt::operator <=(const BigInt& x) // lessOrEqual
{
	if((*this).sign && !x.sign)
	return true;
	else if((*this).sign==x.sign)
	{
		if(x.Number.size() != (*this).Number.size())
		{
			if(x.sign)
			return (*this).Number.size()>x.Number.size();
			else
			return (*this).Number.size()<x.Number.size();
		}
		else
		if(!x.sign)
		return (*this).Number<=x.Number;
		else
		return x.Number<=(*this).Number;
	}
	else
	return false;
}

bool BigInt::operator >=(const BigInt& x) // greaterOrEqual
{
	if(!((*this).sign) && x.sign)
	return true;
	else if((*this).sign==x.sign)
	{
		if(x.Number.size() != (*this).Number.size())
		{
			if(x.sign)
			return (*this).Number.size()<x.Number.size();
			else
			return (*this).Number.size()>x.Number.size();
		}
		else
		if(x.sign)
		return (*this).Number<=x.Number;
		else
		return (*this).Number>=x.Number;
	}
	else 
	return false;
}

void BigInt::operator =(int x) // Assigns IntToBigInt
{
	(*this).sign=false;
	
	if(x<0)
	{
		x*=-1;
		(*this).sign=true;
	}
	
	stringstream S;
	S<<x;
	S>>(*this).Number;
}

void BigInt::operator =(long long x) // assignsIntToBigInt
{
	(*this).sign=false;
	
	if(x<0)
	{
		x*=-1;
		(*this).sign=true;
	}
	
	stringstream S;
	S<<x;
	S>>(*this).Number;
}

BigInt BigInt::operator +(const BigInt& x) //Addition
{
	BigInt ret;
	BigInt A, B;
	A=(*this);
	B=x;
	char *a, *b;
	char C[MAX]={0};
	int carry=0;
	
	if((*this).sign==x.sign)
	{
		if(x.sign)
		{
			ret.sign=true;
		}
		else
		{
			ret.sign=false;
		}

        a=(char*)A.Number.c_str();
        b=(char*)B.Number.c_str();
        reverse(a, a+strlen(a));
        reverse(b, b+strlen(b));
        
    	const int f_len=strlen(a);
    	const int s_len=strlen(b);
    	const int vysledek_len=strlen(C);
    	const int null=0;
	
    	int max_len;
    	if(s_len<(f_len + null))
    	max_len=f_len + null;
    	else
    	max_len=s_len;
	
    	int s_idx = 0, f_idx = 0;
    	int last = 0, idx_null = null;
    	int nula = -1, n;
	
    	while (f_idx < max_len)
    	{
    		n = ((s_len > s_idx) ?     (b[s_idx] - '0') : 0) + ((idx_null > 0) ?     0 : ((f_len > f_idx) ? (a[f_idx] - '0') :     0)) + last;
		
    		if (n > 9)
    		{
    			last = 1;
    			n -= 10;
    		}
    		else
    			last = 0;
			
    		C[s_idx] = n + '0';
		
    		if (!n && s_idx > 0)
    		{
    			if (nula == -1)
    				nula = s_idx;
    		}
    		else
    			nula = -1;
    		++s_idx;
    		if (idx_null-- <= 0)
    			++f_idx;
    	}
    	if (last)
    	{
    		C[s_idx++] = '1';
    		nula = -1;
    	}
    	if (nula > 0)
    		s_idx = nula;
    	C[s_idx] = '\0';
    	
    	reverse(C, C+strlen(C));
		ret.Number=string(C);
		reverse(a, a+strlen(a));
        reverse(b, b+strlen(b));
	}
	
	else if((*this).Number==x.Number)
	{
		ret.sign=false;
		ret.Number="0";
	}
	else
	{
		if(A.sign)
		{
			A.sign=false;
			
			if(A>B)
			{
				ret.sign=true;
				a=(char*)A.Number.c_str();
                b=(char*)B.Number.c_str();
            	reverse(a, a+strlen(a));
            	reverse(b, b+strlen(b));
			}
			else
			{
				ret.sign=false;
         	   a=(char*)B.Number.c_str();
            	b=(char*)A.Number.c_str();
            	reverse(a, a+strlen(a));
                reverse(b, b+strlen(b));
			}
			
			A.sign=true;
		}
		else if(B.sign)
		{
			B.sign=false;
			
			if(B>A)
			{
				ret.sign=true;
	    
	            a=(char*)B.Number.c_str();
	            b=(char*)A.Number.c_str();
                reverse(a, a+strlen(a));
                reverse(b, b+strlen(b));
			}
			else
			{
				ret.sign=false;
         	   a=(char*)A.Number.c_str();
            	b=(char*)B.Number.c_str();
            	reverse(a, a+strlen(a));
                reverse(b, b+strlen(b));
			}
		}
		
		int max_len;
    	int f_len=strlen(a);
    	int s_len=strlen(b);
	
    	if(s_len < f_len)
    	max_len=f_len;
    	else
    	max_len=s_len;
	
    	int idx = -1, last = 0, null_idx = -1;
    	int n;
	
    	while (++idx < max_len)
    	{
    		n = (a[idx] - '0') - ((s_len > idx) ? (b[idx] - '0') : 0) - last;
		
    		if (n < 0)
    		{
    			last = 1;
    			n += 10;
    		}
		
    		else
    			last = 0;
			
    		C[idx] = n + '0';
		
    		if (!n && idx > 0)
    		{
    			if (null_idx == -1)
    				null_idx = idx;
    		}
    		else
    			null_idx = -1;
    	}
    	if (null_idx > 0)
    		idx = null_idx;
		
    	C[idx] = '\0';
    	
    	reverse(C, C+strlen(C));
    	ret.Number=string(C);
		
		reverse(a, a+strlen(a));
        reverse(b, b+strlen(b));
	}
	
	return ret;
}

BigInt BigInt::operator -(const BigInt& x) // Subtraction
{
	BigInt a, b, c;
	a=(*this);
	b=x;
	b.sign=1-b.sign;
	c=a+b;
	
	return c;
}

BigInt BigInt::operator *(const BigInt& x) // Multiplication
{
	string ans;
	const char *tmp;
	char num1[MAX], num2[MAX];
	
	tmp=(*this).Number.c_str();
	strcpy(num1, tmp);
	tmp=x.Number.c_str();
	strcpy(num2, tmp);
	
	ans=FFTMultiply(num1, num2);
	
	BigInt ret(ans);
	
	if((*this).sign!=x.sign)
	ret.sign=true;
	
	return ret;
}

BigInt BigInt::operator /(const BigInt& x) // Rounded Division [sizeof(denominator)<=long long]
{
	long long M;
	char C[MAX]={0};
	int carry=0, k=0;
	
	sscanf(x.Number.c_str(), "%lld", &M);
	
	for(int i=0; i<(*this).Number.size(); i++)
	{
		int Next=(*this).Number[i]-'0';
		int N=carry*10+Next;
		
		C[k++]=(N/M)+'0';
		
		carry=N%M;
	}
	
	C[k]='\0';
	string p(C);
	
	while(p[0]=='0')
	p.erase(0, 1);
	
	if(!p.size())
	p="0";
	BigInt ret(p);
	
	if(x.sign!=(*this).sign)
	ret.sign=true;
	
	return ret;
}

BigInt BigInt::operator %(const BigInt& x) //N(mod)M
// M must fit in long long
{
	long long M;
	const char* shrt=x.Number.c_str();
	
	sscanf(shrt, "%lld", &M);
	
	const char* lng=(*this).Number.c_str();
	
	long long prev=0, T=0;
	
	for(int i=0; i<(*this).Number.size(); i++)
	{
		T=lng[i]-'0';
		T=(prev*10)+T;
		prev=T%M;
	}
	
	string P;
	stringstream S;
	S<<prev;
	S>>P;
	BigInt ret(P);
	
	return ret;
}

BigInt BigInt::operator ++(int x) // Postfix Increment
{
	BigInt T((*this));
	
	(*this)=(*this)+1;
	
	return (T);
}

BigInt BigInt::operator --(int x) // Postfix Decrement
{
	BigInt T((*this));
	
	(*this)=(*this)-1;
	
	return (T);
}

BigInt& BigInt::operator ++() // Prefix Increment
{
	BigInt ret(1);
	(*this)=(*this)+ret;
	
	return (*this);
}

BigInt& BigInt::operator --() // Prefix Decrement
{
	BigInt ret(1);
	(*this)=(*this)-ret;
	
	return (*this);
}

BigInt BigInt::operator -() // Negation
{
	BigInt T((*this));
	T.sign=1-T.sign;
	return T;
}

void BigInt::operator +=(const BigInt& x) // ShortHand Addition
{
	(*this)=(*this)+x;
}

void BigInt::operator -=(const BigInt& x) // ShortHand Subtraction
{
	(*this)=(*this)-x;
}

void BigInt::operator *=(const BigInt& x) // ShortHand Multiplication
{
	(*this)=(*this)*x;
}

void BigInt::operator /=(const BigInt& x) // ShortHand Division
{
	(*this)=(*this)/x;
}

void BigInt::operator %=(const BigInt& x) // ShortHand MOD
{
	(*this)=(*this)%x;
}

BigInt gcd(BigInt a, BigInt b) // Greatest Common Divisor
{
	BigInt t;
	
	while(b != "0")
	{
		t=a;
		a=b;
		b=t%b;
	}
	
	return a;
}

BigInt pow(BigInt a, int b) // BigInt power int
{
	if(b<0)
	{
		BigInt ret(0);
		return ret;
	}
	
	BigInt ret(1);
	bool isNegative=false;
	
	if(a.sign && b%2)
	isNegative=true;
	
	while(b--)
	{
		ret*=a;
	}
	
	if(isNegative)
	ret.sign=true;
	
	return ret;
}

BigInt factorial(long long x) //Must fit in long long
{
	BigInt fact(1);
	
	if(x==0 || x==1)
	return fact;
	
	for(int i=x; i>=1; i--)
	{
		fact*=i;
	}
	
	return fact;
}

BigInt abs(BigInt x) // Absolute Value
{
	if(x.sign)
	x.sign=false;
	
	return x;
}

BigInt min(BigInt a, BigInt b) // Minimum of two
{
	return (a<=b)?a:b;
}

BigInt max(BigInt a, BigInt b) // Maximum of Two
{
	return (a>=b)?a:b;
}

void swap(BigInt& a, BigInt& b) // Swaps the two values
{
	BigInt tmp(a);
	a=b;
	b=tmp;
}