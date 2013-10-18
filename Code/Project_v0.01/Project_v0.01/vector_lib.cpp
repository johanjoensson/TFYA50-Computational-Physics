#include "vector_lib.h"

#include <iostream>


vector_3d vector_3d::operator* (float a)
{
	return vector_3d(a*(this->x), a*(this->y), a*(this->z));
}

vector_3d vector_3d::operator/ (float a)
{
	vector_3d res = *this;
	return 1/a*res;
}

float vector_3d::operator* (vector_3d v)
{
	return (this->x*v.x + this->y*v.y + this->z*v.z);
}

vector_3d vector_3d::operator+ (vector_3d v)
{
	return vector_3d(this->x + v.x, this->y + v.y, this->z + v.z);
}

vector_3d vector_3d::operator- (vector_3d v)
{
	return vector_3d(this->x - v.x, this->y - v.y, this->z - v.z);
}

vector_3d vector_3d::operator+= (vector_3d v)
{
	*this = *this + v;
	return *this;
}

vector_3d vector_3d::operator-= (vector_3d v)
{
	*this = *this - v;
	return *this;
}

vector_3d vector_3d::operator*= (float a)
{ 
	*this = (*this)*a;
	return *this;
}

vector_3d vector_3d::operator/= (float a)
{
	*this = (*this)/a;
	return *this;
}

int vector_3d::operator== (vector_3d v)
{
	return (this->x==v.x && this->y==v.y && this->z==v.z);
}

int vector_3d::operator!= (vector_3d v)
{
	return !(*this == v);
}

vector_3d operator* (float a, vector_3d v)
{
	return v*a;
}

vector_3d vector_3d::operator= (vector_3d v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;

	return *this;
}

vector_3d::vector_3d(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

vector_3d::vector_3d()
{
	x = 0;
	y = 0;
	z = 0;
}

/*
int main()
{
	vector_3d a,b,c,d;
	float f;
	char* state;

	a.x = 4;
	a.y = 5;
	a.z = 6;

	b.x = 1;
	b.y = 2;
	b.z = 3;

	std::cout << "Verifying operator overloading:" << std::endl;
	std::cout << "Verifying = operator:" << std::endl;
	c = a;
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ") = (" << c.x << ", " << c.y << ", " << c.z <<")" << std::endl;

	std::cout << "Verifying + operator:" << std::endl;
	c = a + b;
	std::cout << "(" << (a.x + b.x) << ", " << (a.y + b.y) << ", " << (a.z + b.z) << ") = (" << c.x << ", " << c.y << ", " << c.z <<")" << std::endl;

	std::cout << "Verifyin - operator:" << std::endl;
	c = a - b;
	std::cout << "(" << a.x - b.x << ", " << a.y - b.y << ", " << a.z - b.z << ") = (" << c.x << ", " << c.y << ", " << c.z <<")" << std::endl;

	std::cout << "Verifyin * operator:" << std::endl;
	f = 2;
	c = f*a;
	d = a*f;
	std::cout << "(" << a.x*f << ", " << a.y*f << ", " << a.z*f << ") = (" << c.x << ", " << c.y << ", " << c.z << ") = (" << d.x << ", " << d.y << ", " << d.z << ")" << std::endl;
	
	std::cout << "Verifyin / operator:" << std::endl;
	f = 2;
	c = a/f;
	std::cout << "(" << a.x/f << ", " << a.y/f << ", " << a.z/f << ") = (" << c.x << ", " << c.y << ", " << c.z << ")" << std::endl;

	std::cout << "Verifyin *-scalar mult operator:" << std::endl;
	f = a*b;
	std::cout << (a.x*b.x + a.y*b.y + a.z*b.z) << " = "<< f << std::endl;

	std::cout << "Verifyin *= operator:" << std::endl;
	f = 3;
	c = a;
	c *= f;
	std::cout << "(" << a.x*f << ", " << a.y*f << ", " << a.z*f << ") = (" << c.x << ", " << c.y << ", " << c.z << ")" << std::endl;

	std::cout << "Verifyin /= operator:" << std::endl;
	f = 3;
	d = a;
	c = a/f;
	d /= f;
	std::cout << "(" << c.x << ", " << c.y << ", " << c.z << ") = (" << d.x << ", " << d.y << ", " << d.z << ")" << std::endl;

	std::cout << "Verifyin += operator:" << std::endl;
	d = a;
	d += b;
	std::cout << "(" << a.x + b.x << ", " << a.y + b.y << ", " << a.z + b.z << ") = (" << d.x << ", " << d.y << ", " << d.z << ")" << std::endl;

	std::cout << "Verifyin -= operator:" << std::endl;
	d = a;
	d -= b;
	std::cout << "(" << a.x - b.x << ", " << a.y - b.y << ", " << a.z - b.z << ") = (" << d.x << ", " << d.y << ", " << d.z << ")" << std::endl;

	
	d = a;
	if(d == a){
		state = "TRUE";
	}else{
		state = "FALSE";
	}

	std::cout << "Verifying == operator" << std::endl;
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ") == (" << d.x << ", " << d.y << ", " << d.z << ")";
	std::cout << " is evaluated as " << state << std::endl;

	d = b;
	if(d == a){
		state = "TRUE";
	}else{
		state = "FALSE";
	}

	std::cout << "Verifying == operator" << std::endl;
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ") == (" << d.x << ", " << d.y << ", " << d.z << ")";
	std::cout << " is evaluated as " << state << std::endl;

	d = b;
	if(d != a){
		state = "TRUE";
	}else{
		state = "FALSE";
	}

	std::cout << "Verifying != operator" << std::endl;
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ") != (" << d.x << ", " << d.y << ", " << d.z << ")";
	std::cout << " is evaluated as " << state << std::endl;

	d = a;
	if(d != a){
		state = "TRUE";
	}else{
		state = "FALSE";
	}

	std::cout << "Verifying != operator" << std::endl;
	std::cout << "(" << a.x << ", " << a.y << ", " << a.z << ") != (" << d.x << ", " << d.y << ", " << d.z << ")";
	std::cout << " is evaluated as " << state << std::endl;


	system("pause");
	return 0;
}
*/