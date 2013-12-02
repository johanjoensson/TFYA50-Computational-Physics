#include "vector_lib.h"

#include <cmath>

/******************************************************************************
* Normalise the vector, so that it has absolute value 1						  *
* Sets (x,y,z) = (x,y,z)/((x^2 + y^2 + z^2)^1/2)							  *
******************************************************************************/
void vector_3d::normalise()
{
	float norm = this->abs();
	if( norm != 0){
		*this /= norm;
	}
}

/******************************************************************************
* Calculate the absolute value of the vector (the norm)						  *
* returns (x^2 + y^2 + z^2)^1/2												  *
******************************************************************************/
float vector_3d::abs()
{
	return sqrt(x*x + y*y + z*z);
}

vector_3d vector_3d::operator* (float a)
{
	return vector_3d(a*(this->x), a*(this->y), a*(this->z));
}

vector_3d vector_3d::operator/ (float a)
{
	vector_3d res = *this;
	return (1/a)*res;
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

float vector_3d::distance(vector_3d atom2_pos, float x_tot, float y_tot, float z_tot)
{
	vector_3d dist = this->diff(atom2_pos, x_tot, y_tot, z_tot);
	return sqrt(dist*dist);
}

vector_3d vector_3d::diff(vector_3d atom2_pos, float x_tot, float y_tot, float z_tot)
{
	/* r = x2 - x1 , vector from current atom to the other atom*/
	vector_3d dist = atom2_pos - *this;
	int d = 0;
	if(dist.x*dist.x > 0.25*x_tot*x_tot){
		d = (int)dist.x/x_tot;
		if(dist.x > 0){
			d++;
		}else{
			d--;
		}
		dist.x -= d*x_tot;
	}
	if(dist.y*dist.y > 0.25*y_tot*y_tot)
	{
		d = (int)dist.y/y_tot;
		if(dist.y > 0){
			d++;
		}else{
			d--;
		}
		dist.y -= d*y_tot;
	}	
	if(dist.z*dist.z > 0.25*z_tot*z_tot)
	{
		d = (int)dist.z/z_tot;
		if(dist.z > 0){
			d++;
		}else{
			d--;
		}
		dist.z -= d*z_tot;
	}	
	return dist;
}

void vector_3d::place(float x_tot, float y_tot, float z_tot)
{
	int d = this->x/x_tot;
	if(this->x < 0){
		d--;
	}
	this->x -= d*x_tot;

	d = this->y/y_tot;
	if(this->y < 0){
		d--;
	}
	this->y -= d*y_tot;

	d = this->z/z_tot;
	if(this->z < 0){
		d--;
	}
	this->z -= d*z_tot;
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
