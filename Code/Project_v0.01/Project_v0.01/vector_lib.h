/****************************************************************************** 
* Written by:	Johan J�nsson												  *
* Date:			2013-10-17													  *
* Description:	A simple library for vector calculations					  *
*				with overloaded operators.									  *
******************************************************************************/
#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H

/******************************************************************************
* 3D vectors, useful for most things										  *
******************************************************************************/
class vector_3d{
public:
	/**************************************************************************
	* The cartesian coordinates												  *
	* x, y, z.																  *
	**************************************************************************/
	float x;
	float y;
	float z;

	/**************************************************************************
	* Empty constructor, initializes the coordinates to 0.					  *
	* I.e. x = 0, y = 0, z = 0.												  *
	**************************************************************************/
	vector_3d();
	/**************************************************************************
	* Constructor that initialisez the cartesian coordinates like this		  *
	* x = a, y = b, z = c.													  *
	**************************************************************************/
	vector_3d(float a, float b, float c);
	
	/**************************************************************************
	* Vector multiplied by a scalar											  *
	* v*a (NOTE the order, vector on the left, scalar on the right)			  *
	**************************************************************************/
	vector_3d operator* (float a);
	/**************************************************************************
	* Vector divided by a scalar											  *
	* v/a = 1/a *v															  *
	**************************************************************************/
	vector_3d operator/ (float a);
	/**************************************************************************
	* Scalar multiplication between two vectors								  *
	* (u|v) = <u|v> = u*v (whatever notation you'r used to)					  *
	* (NOTE this is an overloaded version of the *-operator, thus v*u is ok!) *
	**************************************************************************/
	float operator* (vector_3d v);
	/**************************************************************************
	* Vector addition														  *
	* u + v																	  *
	**************************************************************************/
	vector_3d operator+ (vector_3d v);
	/**************************************************************************
	* Vector subtraction													  *
	* u - v																	  *
	**************************************************************************/
	vector_3d operator- (vector_3d v);

	/**************************************************************************
	* Vector increment														  *
	* u = u + v																  *
	**************************************************************************/
	vector_3d operator+= (vector_3d v);
	/**************************************************************************
	* Vector decrement														  *
	* u = u -v																  *
	**************************************************************************/
	vector_3d operator-= (vector_3d v);
	/**************************************************************************
	* Vector scaling														  *
	* u = u*a																  *
	**************************************************************************/
	vector_3d operator*= (float a);
	/**************************************************************************
	* Vector scaling														  *
	* u = u/a																  *
	**************************************************************************/
	vector_3d operator/= (float a);
	/**************************************************************************
	* Vector comparison														  *
	* Compares the cartesian coordinates									  *
	* 1 if (u.x == v.x && u.y == v.y && u.z == v.z)							  *
	* 0 otherwise															  *
	**************************************************************************/
	int operator== (vector_3d v);
	/**************************************************************************
	* Vector comparison														  *
	* Compares the cartesian coordinates									  *
	* 1 if (u.x != v.x || u.y != v.y || u.z != v.z)							  *
	* 0 otherwise															  *
	**************************************************************************/
	int operator!= (vector_3d v);

	/**************************************************************************
	* Assignment operator													  *
	* Sets the cartesian coordinates										  *
	* u.x = v.x, u.y = v.y, u.z = v.z										  *
	**************************************************************************/
	vector_3d operator= (vector_3d);
};

/******************************************************************************
* Scalar multiplied by a vector												  *
* a*v (NOTE the order)														  *
******************************************************************************/
vector_3d operator* (float a, vector_3d v);
#endif /*VECTOR_LIB_H*/