// This file is part of CNCSVision, a computer vision related library
// This software is developed under the grant of Italian Institute of Technology
//
// Copyright (C) 2010-2014 Carlo Nicolini <carlo.nicolini@iit.it>
//
//
// CNCSVision is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// CNCSVision is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// CNCSVision. If not, see <http://www.gnu.org/licenses/>.

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <typeinfo>


#define _USE_MATH_DEFINES
#include <math.h>

#include "Mathcommon.h"

using namespace std;

namespace mathcommon
{
/** \ingroup Mathcommon
* \brief Convert input double from radians to degree
**/
double toDegrees(double x)
{  return x * 57.2957795130823;   // 180 / PI
}

Eigen::Vector3d toDegrees( const Eigen::Vector3d &x )
{  return x*57.2957795130823;   //180/Pi
}
/**
* \ingroup Mathcommon
* \brief  Convert input double from degree to radians
**/
double toRadians(double x)
{  return x * 0.0174532925199433; // ( x * PI / 180 )
}

Eigen::Vector3d toRadians( const Eigen::Vector3d &x )
{  return x*0.0174532925199433;
}
/**
* \ingroup Mathcommon
* \brief Generate a random number between 0 and 1
* \return a uniform number in [0,1].
**/
double unifRand()
{  
	return double(std::rand()) / RAND_MAX;
}
/**
* \ingroup Mathcommon
* \brief Generate a random number in a real interval.
* \param a one end point of the interval
* \param b the other end of the interval
* \return a uniform rand number \f$\in [a,b]\f$.
*
**/
double unifRand(double a, double b)
{
	return unifRand()*(b - a) + a;
}

/**
* \ingroup Mathcommon
* \brief Generate a random number in a real interval.
* \param range The range of the [0,range) range
* \return a uniform rand number \f$\in [0,end)\f$.
*
**/
double unifRandExc(double range)
{  
	return unifRand()*range;
}

/**
* \ingroup Mathcommon
* \brief Generate a random number in a integer interval.
* \param a one end point of the interval
* \param b the other end of the interval
* \return a uniform rand number \f$\in [a,b]\f$.
*
**/
int unifRand(int a, int b)
{  
	return unifRand()*(b - a) + a;
}



/**
* \ingroup Mathcommon
*\brief Randomize the seed for every run. Seeds the random number generator with the current time.
**/
void randomizeStart()
{  std::srand(time(0));
   cerr << "Seed set to " << static_cast<unsigned long >(rand()) << endl;
}

/** \ingroup Mathcommon
* \return True if the marker has coordinates less than 10^10 millimeters, False otherwise
**/
bool isVisible(const Vector3d &v)
{  return  ( abs(v.coeffRef(0)) < 1E10 ) ;
}

/**
\ingroup Mathcommon
Mapping Function:  mod (X, Y)
Compute the modulo of X and Y.  Conceptually this is given by
x - y .* floor (x ./ y)

and is written such that the correct modulus is returned for
integer types.  This function handles negative values correctly.
That is, `mod (-1, 3)' is 2, not -1, as `rem (-1, 3)' returns.
`mod (X, 0)' returns X.

An error results if the dimensions of the arguments do not agree,
or if either of the arguments is complex.
**/
double mod(double x, double y)
{  return x - y*floor(x/y);
}

/** \ingroup Mathcommon
* \brief Compute the sawtooth function of x
* \param x Input
* \param period Period of the sawtooth function
* \return y = sawtooth (x,period) see wikipedia for details
**/
double sawtooth(double x, double period)
{  return 2*(x/period - floor(x/period+0.5));
}

/** \ingroup Mathcommon
* \brief Compute the triangle wave function of x
* \param x Input
* \param period Period of the sawtooth function
* \return y = trianglewave (x,period) see wikipedia for details
**/
double trianglewave(double t, double period)
{  return 2.0/period*( t-period*floor(t/period + 0.5) )*pow(-1.0,floor(t/period - 0.5));
}

double ellipseCircumferenceBetter(double a, double b)
{
    double f = SQR((a-b)/(a+b));
    return M_PI*(a+b)*(1.0+ 3.0*f/(10.0+sqrt(4.0-3.0*f)));
}

double getParaboloidArea(double radius, double curvature)
{
	double height = radius*radius*curvature;
	double a = M_PI/6.0*(radius/(height*height))*(pow(radius*radius+4*height*height,3.0/2.0) -radius*radius*radius);
	return a;
}

}
