#ifndef BIG_INT_H
#define BIG_INT_H

#include <iostream>
using std::istream;
using std::ostream;

#include <vector>
using std::vector;

#include <string>
using std::string;

#define N_BITS 16

/*This is the BigInt class. This was a personal project to emulate python's
  long integer type using C++. Of course, my C++ BigInt class is not as
  effective as python's. Still, I guess this was good practice. Basically,
  the BigInt represents an arbitrary length integer using a vector of
  unsigned short ints. It also uses a sign-and-magnitude method to represent
  the integer, so it might still have some bugs regarding its screen printing.
  Aside from that, I think it works just fine. Although it might be a bit
  inneficient though...
  Programming - Rodrigo Fuentes Hernandez A.K.A Blurred.
  :P You might use this, please don't claim it as your own...
  else I'll get really angry. >.>*/

class BigInt{
	public:
		BigInt();
		BigInt( const BigInt& b );
		BigInt( short num );
		BigInt( unsigned short num );
		BigInt( long num );
		BigInt( unsigned long num );
		BigInt( unsigned int num );
		BigInt( int num );
		BigInt( unsigned long long num );
		BigInt( long long num );
		BigInt( const string& num );
		~BigInt();
		void set( const BigInt& b );
		void set( short num );
		void set( unsigned short num );
		void set( long num );
		void set( unsigned long num );
		void set( unsigned int num );
		void set( int num );
		void set( unsigned long long num );
		void set( long long num );
		void set( const string& num );
		const vector<unsigned short>& body() const;
		bool sign() const;
		void setSign( bool sign );
		void showBits() const;
		const BigInt& operator=( const BigInt& b );
		const BigInt& operator<<=( unsigned int y );
		BigInt operator<<( unsigned int y ) const;
		const BigInt& operator>>=( unsigned int y );
		BigInt operator>>( unsigned int y ) const;
		const BigInt& operator&=( const BigInt& b );
		BigInt operator&( const BigInt& b ) const;
		const BigInt& operator|=( const BigInt& b );
		BigInt operator|( const BigInt& b ) const;
		const BigInt& operator^=( const BigInt& b );
		BigInt operator^( const BigInt& b ) const;
		BigInt operator~() const;
		const BigInt& operator+=( const BigInt& b );
		BigInt operator+( const BigInt& b ) const;
		const BigInt& operator-=( const BigInt& b );
		BigInt operator-( const BigInt& b );
		BigInt operator*=( const BigInt& b );
		BigInt operator*( const BigInt& b );
		const BigInt& operator/=( const BigInt& b );
		BigInt operator/( const BigInt& b );
		const BigInt& operator%=( const BigInt& b );
		BigInt operator%( const BigInt& b );
		bool operator==( const BigInt& b ) const;
		bool operator!=( const BigInt& b ) const;
		bool operator<( const BigInt& b ) const;
		bool operator>( const BigInt& b ) const;
		bool operator<=( const BigInt& b ) const;
		bool operator>=( const BigInt& b ) const;
		static bool isInteger( const string& inputStr );
		friend ostream& operator<<( ostream& salida, const BigInt& b );
		friend istream& operator>>( istream& input, BigInt& b );
		
	private:
		bool sign_; //true if number is negative.
		vector<unsigned short> body_; //Lower indexes mean least significant bits.
		
		bool isZero() const;
		void leftShift();
		void rightShift();
		void setUShort( unsigned short uShort, unsigned long pos );
		unsigned short getUShort( unsigned long pos );
		unsigned short addUShort( unsigned short a, unsigned short b, bool& carry );
		int compare( const BigInt& b ) const;
		static int changeState( char input, int state );
};

#endif //BIG_INT_H
