//
// Created by Byron on 2/11/2016.
//

#include "Point.h"
#include "Exceptions.h"
#include <iostream>
#include <cmath>
//#include <stdlib.h>
#include <sstream>
//#include <bits/stl_algo.h>



using namespace Clustering;

namespace Clustering{


    unsigned int Point::__idGen = 0; // id generator

    static const char POINT_VALUE_DELIM = ',';

    void Point::rewindIdGen(){

        __idGen -= 1;
    }

    Point::Point(unsigned int dimensions){

        if(dimensions == 0)
        {
            throw ZeroDimensionsEx();
        }

        //Generates a unique id for each point as they are made and increments idGen for the next point.
        __id = __idGen;
        ++__idGen;

        __dim = dimensions; //Assigns the number of dimensions of the point.
        __values = new double[__dim]; //Creates a dynamically allocated array of doubles that holds each dimension

        //Initializes array to 0.
        for(int index = 0 ; index < __dim ; index++ ){

            __values[index] = 0;

        }

    }

    Point::Point(unsigned int dimensions, double * pointsA){

        if(dimensions == 0) throw ZeroDimensionsEx();

        //Generates a unique id for each point as they are made and increments idGen for the next point.
        __id = __idGen;
        ++__idGen;

        __dim = dimensions; //Assigns the number of dimensions of the point.
        __values = new double[__dim]; //Creates a dynamically allocated array of doubles that holds each dimension

        //Initializes array to 0.
        for(int index = 0 ; index < __dim ; index++ ){

            __values[index] = pointsA[index];

        }


    }
//    Point::Point(int dimensions){
//
//        //Generates a unique id for each point as they are made and increments idGen for the next point.
//        __id = __idGen;
//        ++__idGen;
//
//        __dim = dimensions; //Assigns the number of dimensions of the point.
//        __values = new double[__dim]; //Creates a dynamically allocated array of doubles that holds each dimension
//
//        //Initializes array to 0.
//        for(int index = 0 ; index < __dim ; index++ ){
//
//            __values[index] = 0;
//
//        }
//    }


//// Big three: cpy ctor, overloaded operator=, dtor

    //Copy Constructor
    Point::Point(const Point & toBeCopied){


        //Assigning all values too be copied.
        __id = toBeCopied.__id;
        __dim = toBeCopied.__dim;
        __values = new double[__dim];

        //Loop to toBeCopied to a new dynamically allocated array.
        for(int index = 0 ; index < __dim ; index++ ){

            __values[index] = toBeCopied.__values[index];

        }

    }

    //Overloaded = operator
    Point &Point::operator=(const Point & rhs){

        if(__dim != rhs.__dim)
        {
            throw DimensionalityMismatchEx(__dim, rhs.__dim);
        }

        //Checks for self-assignment
        if(this == &rhs)
            return *this;
        else
        {
            //Assigning all values too be copied.
            __id = rhs.__id;
            __dim = rhs.__dim;
            __values = new double[__dim];

            //Loop to copy rhs to a new dynamically allocated array.
            for(int index = 0 ; index < __dim ; index++ ){

                __values[index] = rhs.__values[index];

            }

        }

        return *this;
    }

    //Destructor
    Point::~Point(){

        delete[] __values;
    }

// Accessors & mutators

    int Point::getId() const{

        return __id;
    }

    unsigned int Point::getDims() const{

        return __dim;

    }

    void Point::setValue(unsigned int dimension, double value){

        if( dimension >= __dim)
        {
            throw OutOfBoundsEx( __dim, dimension);
        }

        __values[dimension] = value;

    }

    double Point::getValue( unsigned  int dimension) const{

        if( dimension >= __dim)
        {
            throw OutOfBoundsEx( __dim, dimension);
        }

        return __values[dimension];

    }

//// Functions
    double Point::distanceTo(const Point & pointDistance) const{

        if(pointDistance.__dim != __dim)
        {
            throw DimensionalityMismatchEx(pointDistance.__dim, __dim);
        }

        double aDistanceTo = 0;
        double sumOfDistance = 0;
        double finalDistance = 0;

        for (int index = 0; index < __dim ; ++index) {

            aDistanceTo = (__values[index] - pointDistance.__values[index]) * (__values[index] - pointDistance.__values[index]);

            sumOfDistance += aDistanceTo;

        }


        finalDistance = sqrt(sumOfDistance);

        return finalDistance;


    }

//// Overloaded operators
//// Members

    Point &Point::operator*=(double aValue ){

        for (int index = 0; index < __dim; ++index) {

            __values[index] *= aValue;

        }

        return *this;

    }


    Point &Point::operator/=(double aValue){

        for (int index = 0; index < __dim ; ++index) {

            __values[index] /= aValue;

        }

        return *this;

    }


    const Point Point::operator*(double aValue) const{

        Point aPoint(*this); //Makes a new point with the dim of the current point

        aPoint *= aValue; // * the current point by the value

        return aPoint; // returns the point

    }


    const Point Point::operator/(double aValue) const{

        Point aPoint(*this);

        aPoint /= aValue;

        return aPoint;
    }


    double &Point::operator[](unsigned int index){

        if( index >= __dim) throw OutOfBoundsEx( __dim, index);

        return this->__values[index];

    }


    const double &Point::operator[](unsigned int index) const{

        if( index >= __dim) throw OutOfBoundsEx( __dim, index);

        return this->__values[index];

    }

//// Friends
    Point& operator+=(Point& lhsPoint, const Point& rhsPoint){

        if(lhsPoint.__dim != rhsPoint.__dim) throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);


        for(int index = 0; index < lhsPoint.__dim; index++){

            lhsPoint.__values[index] = lhsPoint.__values[index] + rhsPoint.getValue(index);
        }

//        int lhsDims = 0, //Holds the total dimensions of lhs Point.
//                rhsDims = 0, //Holds the total dimensions of rhs Point.
//                biggestDims = 0; //Holds the larger of the 2 dimensions between rhs and lhs Points.
//
//        lhsDims = lhsPoint.getDims();
//        rhsDims = rhsPoint.getDims();
//
//        if (rhsDims > lhsDims)
//            biggestDims = rhsDims;
//        else
//            biggestDims = lhsDims;
//
//        if (lhsDims < rhsDims)
//        {
//            delete [] lhsPoint.__values;
//
//            lhsPoint.__values = new double[rhsDims];
//        }
//
//        for (unsigned int index = 0; index < biggestDims ; ++index) {
//
//            lhsPoint[index]= lhsPoint[index] + rhsPoint.getValue(index);
//
//        }

        return lhsPoint;

    }

    Point & operator-=(Point & lhsPoint, const Point & rhsPoint){

        if(lhsPoint.__dim != rhsPoint.__dim) throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);


        for(int index = 0; index < lhsPoint.__dim; index++){

            lhsPoint.__values[index] = lhsPoint.__values[index] - rhsPoint.getValue(index);
        }

//        int lhsDims = 0, //Holds the total dimensions of lhs Point.
//                rhsDims = 0, //Holds the total dimensions of rhs Point.
//                biggestDims = 0; //Holds the larger of the 2 dimensions between rhs and lhs Points.
//
//        lhsDims = lhsPoint.getDims();
//        rhsDims = rhsPoint.getDims();
//
//        if (rhsDims > lhsDims)
//            biggestDims = rhsDims;
//        else
//            biggestDims = lhsDims;
//
//        if (lhsDims < rhsDims)
//        {
//            delete [] lhsPoint.__values;
//
//            lhsPoint.__values = new double[rhsDims];
//        }
//
//        for (unsigned int index = 0; index < biggestDims ; ++index) {
//
//            lhsPoint[index]= lhsPoint[index] - rhsPoint.getValue(index);
//
//        }

        return lhsPoint;

    }

    const Point operator+(const Point & lhsPoint, const Point & rhsPoint){

        if(lhsPoint.__dim != rhsPoint.__dim) throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);

        Point aPoint(lhsPoint);

        aPoint += rhsPoint;

        return aPoint;

    }

    const Point operator-(const Point & lhsPoint, const Point & rhsPoint){

        if(lhsPoint.__dim != rhsPoint.__dim) throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);

        Point aPoint(lhsPoint);

        aPoint -= rhsPoint;

        return aPoint;

    }

    bool operator==(const Point & lhsPoint, const Point & rhsPoint){


        if(lhsPoint.__dim != rhsPoint.__dim) throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);

        bool notEqual = false;
        bool equal = true;

        int biggestDims = lhsPoint.getDims(); //Holds the larger of the 2 dimensions between rhs and lhs Points.

        /*lhsDims = 0, //Holds the total dimensions of lhs Point.
                rhsDims = 0, //Holds the total dimensions of rhs Point.*/


//        lhsDims = lhsPoint.getDims();
//        rhsDims = rhsPoint.getDims();
//
//        if (rhsDims > lhsDims)
//            biggestDims = rhsDims;
//        else
//            biggestDims = lhsDims;


        if (lhsPoint.__id == rhsPoint.__id)
        {
            for (int index = 0; index < biggestDims ; ++index) {

                if (lhsPoint.__values[index] != rhsPoint.__values[index]){
                    return notEqual;
                }
            }
        }
        else
        {
            return notEqual;
        }

        return equal;
    }

    bool operator!=(const Point & lhsPoint, const Point & rhsPoint){

        if(lhsPoint.__dim != rhsPoint.__dim)
        {
            throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);
        }

        return !(lhsPoint == rhsPoint);
    }

    bool operator<(const Point & lhsPoint, const Point & rhsPoint){

        if(lhsPoint.__dim != rhsPoint.__dim)
        {
            throw DimensionalityMismatchEx(lhsPoint.__dim, rhsPoint.__dim);
        }

        for (int index = 0; index < lhsPoint.__dim; ++index)
        {
            if (lhsPoint.__values[index] < rhsPoint.__values[index])
            {
                return true;
            }

            else if (lhsPoint.__values[index] > rhsPoint.__values[index])
            {
                return false;
            }

        }
        return false;


//        bool notEqual = false;
//        bool equal = true;
//
//        int lhsDims = 0, //Holds the total dimensions of lhs Point.
//            rhsDims = 0, //Holds the total dimensions of rhs Point.
//            biggestDims = 0; //Holds the larger of the 2 dimensions between rhs and lhs Points.
//
//        lhsDims = lhsPoint.getDims();
//        rhsDims = rhsPoint.getDims();
//
//        if (rhsDims > lhsDims)
//            biggestDims = rhsDims;
//        else
//            biggestDims = lhsDims;
//
//        for (int index = 0; index < biggestDims ; ++index) {
//
//            if (lhsPoint.getValue(index) != rhsPoint.getValue(index)) {
//
//                return equal;
//
//            }
//        }
//
//        return notEqual;
    }

    bool operator>(const Point & lhsPoint, const Point & rhsPoint){

        return (rhsPoint < lhsPoint);


    }

    bool operator<=(const Point & lhsPoint, const Point &rhsPoint){

        if (lhsPoint > rhsPoint)
        {
            return false;
        }

        else
        {
            return true;
        }


    }

    bool operator>=(const Point & lhsPoint, const Point &rhsPoint){

        if (lhsPoint < rhsPoint)
        {
            return false;
        }

        else
        {
            return true;
        }

    }

    std::ostream &operator<<(std::ostream & pointsOut, const Point & aPoint){

        pointsOut <<  aPoint.__values[0];

        for (int  index = 1; index < aPoint.__dim ; ++index) {
            pointsOut << ", " << aPoint.__values[index];
        }

        return pointsOut;
    }

    std::istream &operator>>(std::istream & pointsIn, Point &aPoint){

        std::string data;

        int counter = 0;

        while(std::getline(pointsIn, data, POINT_VALUE_DELIM))
        {
            aPoint.__values[counter] = std::stod(data);

            ++counter;
        }

        if(aPoint.__dim != counter) throw DimensionalityMismatchEx(aPoint.__dim, counter);

        return pointsIn;


    }



}

