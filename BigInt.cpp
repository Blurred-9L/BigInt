#include "BigInt.h"

#include <climits>

#include <iostream>
using std::cout;
using std::endl;
using std::ios_base;

#include <cctype>
using std::isdigit;

BigInt::BigInt(){
	body_.push_back( 0 );
	sign_ = false;
}

BigInt::BigInt( const BigInt& b ){
	set( b );
}

BigInt::BigInt( short num ){
	set( num );
}

BigInt::BigInt( unsigned short num ){
	set( num );
}

BigInt::BigInt( long num ){
	set( num );
}

BigInt::BigInt( unsigned long num ){
	set( num );
}

BigInt::BigInt( unsigned int num ){
	set( num );
}

BigInt::BigInt( int num ){
	set( num );
}

BigInt::BigInt( unsigned long long num ){
	set( num );
}

BigInt::BigInt( long long num ){
	set( num );
}

BigInt::BigInt( const string& num ){
	set( num );
}

void BigInt::set( const BigInt& b ){
	sign_ = b.sign();
	body_ = b.body();
}

BigInt::~BigInt(){
	body_.clear();
}

void BigInt::set( short num ){
	body_.clear();
	if( num >= 0 ){
		sign_ = false;
		body_.push_back( num );
	}
	else{
		sign_ = true;
		body_.push_back( num * -1 );
	}
}

void BigInt::set( unsigned short num ){
	body_.clear();
	body_.push_back( num );
	sign_ = false;
}

void BigInt::set( long num ){
	body_.clear();
	if( num >= 0 ){
		sign_ = false;
	}
	else{
		sign_ = true;
		num *= -1;
	}
	if( num > 0 ){
		while( num > 0 ){
			body_.push_back( (short)( num & 0xFFFF ) );
			num >>= 16;
		}
	}
	else{
		body_.push_back( (short)0 );
	}
}

void BigInt::set( unsigned long num ){
	body_.clear();
	if( num > 0 ){
		while( num > 0 ){
			body_.push_back( (short)( num & 0xFFFF ) );
			num >>= 16;
		}
	}
	else{
		body_.push_back( (short)0 );
	}
	sign_ = false;
}

void BigInt::set( unsigned int num ){
	body_.clear();
	if( num > 0 ){
		while( num > 0 ){
			body_.push_back( (short)( num & 0xFFFF ) );
			num >>= 16;
		}
	}
	else{
		body_.push_back( (short)0 );
	}
	sign_ = false;
}

void BigInt::set( int num ){
	body_.clear();
	if( num >= 0 ){
		sign_ = false;
	}
	else{
		sign_ = true;
		num *= -1;
	}
	if( num > 0 ){
		while( num > 0 ){
			body_.push_back( (short)( num & 0xFFFF ) );
			num >>= 16;
		}
	}
	else{
		body_.push_back( (short)0 );
	}
}

void BigInt::set( unsigned long long num ){
	body_.clear();
	if( num > 0 ){
		while( num > 0 ){
			body_.push_back( (short)( num & 0xFFFF ) );
			num >>= 16;
		}
	}
	else{
		body_.push_back( (short)0 );
	}
	sign_ = false;
}

void BigInt::set( long long num ){
	body_.clear();
	if( num >= 0 ){
		sign_ = false;
	}
	else{
		sign_ = true;
		num *= -1;
	}
	if( num > 0 ){
		while( num > 0 ){
			body_.push_back( (short)( num & 0xFFFF ) );
			num >>= 16;
		}
	}
	else{
		body_.push_back( (short)0 );
	}
}

/*Sets the BigInt value using a string representing a base 10 number.
  If the string is not a valid integer, it simply sets its value to 0.*/
void BigInt::set( const string& num ){
	unsigned long i = 0;
	unsigned long size = num.size();
	
	body_.clear();
	body_.push_back( 0 );
	sign_ = false;
	if( BigInt::isInteger( num ) ){
		if( num[0] == '-' ){
			sign_ = true;
			i++;
		}
		else if( num[0] == '+' ){
			i++;
		}
		while( i < size ){
			operator*=( 10 );
			operator+=( num[i] - '0' );
			i++;
		}
	}
}

const vector<unsigned short>& BigInt::body() const{
	return body_;
}

bool BigInt::sign() const{
	return sign_;
}

void BigInt::setSign( bool sign ){
	sign_ = sign;
}

void BigInt::showBits() const{
	unsigned short bitMask;
	
	for( long long i = body_.size() - 1; i >= 0; i-- ){
		bitMask = 0x8000;
		while( bitMask > 0 ){
			if( ( bitMask & body_[i] ) != 0 ){
				cout << "1";
			}
			else{
				cout << "0";
			}
			bitMask >>= 1;
		}
		cout << " ";
	}
	cout << endl;
}

const BigInt& BigInt::operator=( const BigInt& b ){
	sign_ = b.sign();
	body_ = b.body();
	
	return *this;
}

const BigInt& BigInt::operator<<=( unsigned int y ){
	while( y > 0 ){
		leftShift();
		y--;
	}
	
	return *this;
}

BigInt BigInt::operator<<( unsigned int y ) const{
	BigInt rBigInt( *this );
	
	rBigInt <<= y;
	
	return rBigInt;
}

const BigInt& BigInt::operator>>=( unsigned int y ){
	while( y > 0 ){
		rightShift();
		y--;
	}
	
	return *this;
}

BigInt BigInt::operator>>( unsigned int y ) const{
	BigInt rBigInt( *this );

	rBigInt >>= y;
	
	return rBigInt;
}

const BigInt& BigInt::operator&=( const BigInt& b ){
	unsigned long mySize = body_.size();
	unsigned long otherSize = b.body().size();
	unsigned long i;
	
	for( i = 0; i < mySize; i++ ){
		body_[i] &= b.body()[i];
	}
	if( mySize > otherSize ){
		while( i < otherSize ){
			body_[i] &= 0;
			i++;
		}
	}
	
	return *this;
}

BigInt BigInt::operator&( const BigInt& b ) const{
	BigInt rBigInt( *this );
	
	rBigInt &= b;
	
	return rBigInt;
}

const BigInt& BigInt::operator|=( const BigInt& b ){
	unsigned long mySize = body_.size();
	unsigned long otherSize = b.body().size();
	unsigned long i;
	
	if( mySize >= otherSize ){
		for( i = 0; i < otherSize; i++ ){
			body_[i] |= b.body()[i];
		}
	}
	else{
		for( i = 0; i < mySize; i++ ){
			body_[i] |= b.body()[i];
		}
		while( i < otherSize ){
			body_.push_back( b.body()[i] );
			i++;
		}
	}
	
	return *this;
}

BigInt BigInt::operator|( const BigInt& b ) const{
	BigInt rBigInt( *this );
	
	rBigInt |= b;
	
	return rBigInt;
}

const BigInt& BigInt::operator^=( const BigInt& b ){
	unsigned long mySize = body_.size();
	unsigned long otherSize = b.body().size();
	unsigned long i;
	
	if( mySize >= otherSize ){
		for( i = 0; i < otherSize; i++ ){
			body_[i] ^= b.body()[i];
		}
	}
	else{
		for( i = 0; i < mySize; i++ ){
			body_[i] ^= b.body()[i];
		}
		while( i < otherSize ){
			body_.push_back( b.body()[i] );
			i++;
		}
	}
	
	return *this;
}

BigInt BigInt::operator^( const BigInt& b ) const{
	BigInt rBigInt( *this );
	
	rBigInt ^= b;
	
	return rBigInt;
}

BigInt BigInt::operator~() const{
	BigInt rBigInt( *this );
	unsigned long size = body_.size();
	
	for( unsigned long i = 0; i < size; i++ ){
		rBigInt.setUShort( ~body_[i], i );
	}
	
	return rBigInt;
}

const BigInt& BigInt::operator+=( const BigInt& b ){
	unsigned long mySize = body_.size();
	unsigned long otherSize = b.body().size();
	unsigned long i, j;
	bool carry;
	BigInt auxBigInt( b );
	BigInt auxBigInt2( *this );
	
	//Both BigInts are positive or negative.
	if( sign_ == b.sign() ){
		if( mySize <= otherSize ){
			carry = false;
			for( i = 0; i < mySize; i++ ){
				body_[i] = addUShort( body_[i], b.body()[i], carry );
			}
			while( i < otherSize ){
				body_.push_back( addUShort( 0, b.body()[i], carry ) );
				i++;
			}
			if( carry ){
				body_.push_back( 1 );
			}
		}
		else{
			carry = false;
			for( i = 0; i < otherSize; i++ ){
				body_[i] = addUShort( body_[i], b.body()[i], carry );
			}
			while( i < mySize ){
				body_[i] = addUShort( body_[i], 0, carry );
				i++;
			}
			if( carry ){
				body_.push_back( 1 );
			}
		}
	}
	//This BigInt is negative.
	else if( !sign_ ){
		auxBigInt.setSign( false );
		*this -= auxBigInt;
	}
	else{
		auxBigInt2.setSign( false );
		auxBigInt -= auxBigInt2;
		*this = auxBigInt;
	}
	
	return *this;
}

BigInt BigInt::operator+( const BigInt& b ) const{
	BigInt rBigInt( *this );
	
	rBigInt += b;
	
	return rBigInt;
}

const BigInt& BigInt::operator-=( const BigInt& b ){
	BigInt auxBigInt( b );
	BigInt auxBigInt2( *this );
	long i, j;
	
	if( sign_ == b.sign() ){
		//Both are positive.
		if( !sign_ ){
			auxBigInt = ~auxBigInt + 1;
			auxBigInt2 += auxBigInt;
			//Gets rid of leading 0...
			i = auxBigInt2.body().size() - 1;
			while( i >= 0 && auxBigInt2.body()[i] == 0 ){
				i--;
			}
			//This while is probably useless...
			j = body_.size() - 1;
			while( j >= 0 && body_[j] == 0 ){
				j--;
			}
			if( auxBigInt2.body()[i] == 1 ){
				auxBigInt2.setUShort( 0, i );
				*this = auxBigInt2;
			}
			else{
				auxBigInt2 = ~auxBigInt2 + 1;
				*this = auxBigInt2;
				sign_ = true;
			}
		}
		//Both are negative.
		else{
			auxBigInt.setSign( false );
			auxBigInt += *this;
			*this = auxBigInt;
		}
	}
	//This BigInt is negative.
	else if( !sign_ ){
		auxBigInt.setSign( false );
		*this += auxBigInt;
	}
	else{
		auxBigInt.setSign( true );
		*this += auxBigInt;
	}
	
	return *this;
}

BigInt BigInt::operator-( const BigInt& b ){
	BigInt rBigInt( *this );
	
	rBigInt -= b;
	
	return rBigInt;
}

BigInt BigInt::operator*=( const BigInt& b ){
	BigInt y( b );
	BigInt aux;
	BigInt count;
	BigInt result;
	bool previousSign = sign_;
	
	y.setSign( false );
	while( y > 0 && *this != 0 ){
		aux = *this;
		count = 1;
		while( ( count << 1 ) <= y ){
			count <<= 1;
			aux <<= 1;
		}
		result += aux;
		y -= count;
	}
	*this = result;
	sign_ = previousSign ^ b.sign();
	
	return *this;
}

BigInt BigInt::operator*( const BigInt& b ){
	BigInt rBigInt( *this );
	
	rBigInt *= b;
	
	return rBigInt;
}

const BigInt& BigInt::operator/=( const BigInt& b ){
	BigInt x( *this );
	BigInt y( b );
	BigInt aux1, aux2;
	BigInt count;
	BigInt quotient( 0 );
	bool previousSign = sign_;
	
	x.setSign( false );
	y.setSign( false );
	while( x >= y ){
		aux1 = x >> 1;
		aux2 = y;
		count = 1;
		while( aux1 >= aux2 ){
			count <<= 1;
			aux2 <<= 1;
		}
		x -= aux2;
		quotient += count;
	}
	
	*this = quotient;
	sign_ = previousSign ^ b.sign();
	
	return *this;
}

BigInt BigInt::operator/( const BigInt& b ){
	BigInt rBigInt( *this );
	
	rBigInt /= b;
	
	return rBigInt;
}

const BigInt& BigInt::operator%=( const BigInt& b ){
	BigInt x( *this );
	BigInt y( b );
	BigInt aux1, aux2;
	BigInt count;
	BigInt quotient( 0 );
	bool previousSign = sign_;
	
	x.setSign( false );
	y.setSign( false );
	while( x >= y ){
		aux1 = x >> 1;
		aux2 = y;
		count = 1;
		while( aux1 >= aux2 ){
			count <<= 1;
			aux2 <<= 1;
		}
		x -= aux2;
		quotient += count;
	}
	
	*this = x;
	sign_ = previousSign;
	
	return *this;
}

BigInt BigInt::operator%( const BigInt& b ){
	BigInt rBigInt( *this );
	
	rBigInt %= b;
	
	return rBigInt;
}

bool BigInt::operator==( const BigInt& b ) const{
	int compareResult = compare( b );
	
	return ( sign_ == b.sign() && compareResult == 0 );
}

bool BigInt::operator!=( const BigInt& b ) const{
	return not ( *this == b );
}

bool BigInt::operator<( const BigInt& b ) const{
	int compareResult = compare( b );
	
	if( sign_ == b.sign() ){
		if( !sign_ ){
			return compareResult == -1;
		}
		else{
			return compareResult == 1;
		}
	}
	else if( !sign_ ){
		return false;
	}
	else{
		return true;
	}
		
}

bool BigInt::operator>( const BigInt& b ) const{
	return b < *this;
}

bool BigInt::operator<=( const BigInt& b ) const{
	int compareResult = compare( b );
	
	if( sign_ == b.sign() ){
		if( !sign_ ){
			return compareResult == -1 || compareResult == 0;
		}
		else{
			return compareResult == 1 || compareResult == 0;
		}
	}
	else if( !sign_ ){
		return false;
	}
	else{
		return true;
	}
}

bool BigInt::operator>=( const BigInt& b ) const{
	return b <= *this;
}

//Private methods start here...

//Checks if BigInt's value is 0.
bool BigInt::isZero() const{
	unsigned long size = body_.size();
	bool isZero = true;
	
	for( unsigned long i = 0; i < size && isZero; i++ ){
		if( body_[i] != 0 ){
			isZero = false;
		}
	}
	
	return isZero;
}

void BigInt::leftShift(){
	unsigned long index;
	bool bit = false;
	bool nextBit;
	
	for( index = 0; index < body_.size(); index++ ){
		nextBit = body_[index] & ( 1 << ( N_BITS - 1 ) );
		body_[index] <<= 1;
		body_[index] |= bit;
		bit = nextBit;
	}
	if( bit ){
		body_.push_back( 1 );
	}
}

void BigInt::rightShift(){
	long index;
	bool bit = false;
	bool nextBit;
	
	for( index = body_.size() - 1; index >= 0; index-- ){
		nextBit = body_[index] & 1;
		body_[index] >>= 1;
		body_[index] |= bit << ( N_BITS - 1 );
		bit = nextBit;
	}
}

void BigInt::setUShort( unsigned short uShort, unsigned long pos ){
	body_[pos] = uShort;
}

unsigned short BigInt::getUShort( unsigned long pos ){
	return body_[pos];
}

unsigned short BigInt::addUShort( unsigned short a, unsigned short b, bool& carry ){
	bool aBit, bBit, output;
	unsigned long auxBit = 1;
	unsigned long j = 0;
	unsigned short newValue = 0;
	
	while( auxBit < USHRT_MAX ){
		aBit = a & auxBit;
		bBit = b & auxBit;
		output = aBit ^ bBit ^ carry;
		carry = ( aBit & bBit ) | ( carry & ( aBit ^ bBit ) );
		newValue |= output << j++;
		auxBit <<= 1;
	}
	
	return newValue;
}

//Compares this BigInt with another BigInt's. Uses the absolute value only.
//Returns 0 if they are equal, 1 if it is bigger and -1 if it is smaller. 
int BigInt::compare( const BigInt& b ) const{
	long i, j;
	int compareResult = 0;
	
	//Gets rid of leading 0s...
	i = body_.size() - 1;
	j = b.body().size() - 1;
	while( i > j && compareResult == 0 && i >= 0 ){
		if( body_[i] == 0 ){
			i--;
		}
		else{
			compareResult = 1;
		}
	}
	while( j > i && compareResult == 0 && j >= 0 ){
		if( b.body()[j] == 0 ){
			j--;
		}
		else{
			compareResult = -1;
		}
	}
	while( compareResult == 0 && i >= 0 && j >= 0 ){
		compareResult = ( body_[i] > b.body()[j] )? 1 : ( ( body_[i] < b.body()[j] )? -1 : 0 );
		i--;
		j--;
	}
	
	return compareResult;
}

bool BigInt::isInteger( const string& inputStr ){
	int currentState = 0;
	int i = 0;
	int size = inputStr.size();
	bool validInput = true;
	
	while( i < size && validInput ){
		currentState = BigInt::changeState( inputStr[i], currentState );
		if( currentState < 0 ){
			validInput = false;
		}
		i++;
	}
	
	return validInput;
}

int BigInt::changeState( char input, int state ){
	const int transitions[3][3] = { {  1, 2, -2 },
									{ -1, 2, -2 },
									{ -1, 2, -2 } };
	enum inputs{ SIGN, DIGIT, OTHER };
	int newState;
	
	switch( input ){
		case '+': case '-':
			newState = transitions[state][SIGN];
			break;
		default:
			if( isdigit( input ) ){
				newState = transitions[state][DIGIT];
			}
			else{
				newState = transitions[state][OTHER];
			}
			break;
	}
	
	return newState;
}

//friend methods start here...

ostream& operator<<( ostream& output, const BigInt& b ){
	BigInt auxBigInt( b );
	string outStr = "";
	bool negative = false;
	
	if( b != 0 ){
		if( auxBigInt < 0 ){
			negative = true;
			auxBigInt.setSign( false );
		}
		while( auxBigInt > 0 ){
			outStr += ( auxBigInt % 10 ).getUShort( 0 ) + '0';
			auxBigInt /= 10;
		}
		if( negative ){
			output << "-";
		}
		for( int i = outStr.size() - 1; i >= 0; i-- ){
			output << outStr[i];
		}
	}
	else{
		output << "0";
	}
	
	return output;
}

//Does not change istream's state if the string read is not a valid integer.
istream& operator>>( istream& input, BigInt& b ){
	string inputString;
	
	input >> inputString;
	b.set( inputString );
	
	return input;
}
