//
// Created by Byron on 2/11/2016.
//


#include <algorithm>
#include <sstream>
#include "Cluster.h"
#include "Exceptions.h"

using namespace std;

using namespace Clustering;

namespace Clustering {


    LNode::LNode(const Point &aPoint, LNodePtr nextNode) : point(aPoint), next(nextNode) { }

    unsigned int Cluster::__idGenerator = 0;


    void Cluster::__del() {

        while (__points != nullptr) {

            LNodePtr current = __points->next;

            delete __points;

            __points = current;

            __size--;

        }

    }

    void Cluster::__cpy(LNodePtr pts) {

        if (__size != 0) {
            LNodePtr cpyPtr = nullptr;

            LNodePtr headPtr;

            headPtr = new LNode(pts->point, cpyPtr);

            LNodePtr currentPtr = pts->next;

            __points = headPtr;

            LNodePtr currentNode = __points;

            while (currentPtr != nullptr) {

                currentNode->next = new LNode(currentPtr->point, cpyPtr);

                currentNode = currentNode->next;

                currentPtr = currentPtr->next;

            }
        }


    }

    bool Cluster::__in(const Point &p) const {

        if (this->getDimensionality() != p.getDims()) {
            throw DimensionalityMismatchEx(this->getDimensionality(), p.getDims());
        }

        bool in = false;

        LNodePtr currentPtr = __points;


        while (currentPtr != nullptr) {

            if (currentPtr->point == p) {
                in = true;
                break;
            }

            currentPtr = currentPtr->next;
        }


        return in;


    }

    //********Functions for private inner class Centroid**********

    Cluster::Centroid::Centroid(unsigned int dimensions, const Cluster &clusterF) : __p(Point(dimensions)), __c(clusterF) {

        __dimensions = dimensions;

        __valid = false;

    }

    // getters/setters

    // doesn't check for validity
    const Point Cluster::Centroid::get() const {

        return __p;
    }

    // sets to valid
    void Cluster::Centroid::set(const Point &p) {

        setValid(true);
        __p = p;

    }

    bool Cluster::Centroid::isValid() const {

        return __valid;
    }

    void Cluster::Centroid::setValid(bool valid) {

        __valid = valid;
    }


    // Functions
    void Cluster::Centroid::compute() {


        Point aPoint(__c.getDimensionality());
        Point totalOfPoints(__c.getDimensionality());

        int limit = __c.getSize();

        //Finds average of all points to place centroid.
        for (int index = 0; index < limit; ++index) {

            totalOfPoints += __c[index];

        }

        aPoint = (totalOfPoints / __c.getSize());

        set(aPoint);


    }

    bool Cluster::Centroid::equal(const Point &aPoint) const {

        bool equalState = true;

        int limit = __dimensions;

        for (int index = 0; index < limit; index++) {

            if (__p.getValue(index) != aPoint.getValue(index)) {

                equalState = false;

                return equalState;
            }

        }

        return equalState;


    }

    void Cluster::Centroid::toInfinity() {

        int limit = __dimensions;

        for (int index = 0; index < limit; index++) {

            __p[index] = std::numeric_limits<double>::max();

        }

    }


    Cluster::Cluster(unsigned int d) : centroid(d, *this) {

        __size = 0;
        __points = nullptr;
        __dimensionality = d;
        __id = __idGenerator;
        __idGenerator++;


    }



    // The big three: cpy ctor, overloaded operator=, dtor

    Cluster::Cluster(const Cluster &clusterF) : centroid(clusterF.__dimensionality, *this) {

        if (this != &clusterF)
        {

            __size = clusterF.__size;
            __dimensionality = clusterF.__dimensionality;
            __cpy(clusterF.__points);
            __id = clusterF.__id;

            centroid.compute();


        }




    }

    Cluster &Cluster::operator=(const Cluster &rhs) {

        if (this->getDimensionality() != rhs.getDimensionality()) {
            throw DimensionalityMismatchEx(this->getDimensionality(), rhs.getDimensionality());
        }

        if (this != &rhs) {

            __del();
            __size = rhs.__size;
            __dimensionality = rhs.__dimensionality;
            __cpy(rhs.__points);
            __id = rhs.__id;

            centroid.compute();

        }

        return *this;

    }

    Cluster::~Cluster() {

       __del();


    }


//        // Getters/setters
    unsigned int Cluster::getSize() const {

        return __size;
    }

    unsigned int Cluster::getDimensionality() const {

        return __dimensionality;
    }

    unsigned int Cluster::getId() const {

        return __id;
    }

//
//        // Set functions: They allow calling c1.add(c2.remove(p));
    void Cluster::add(const Point &aAddedPoint) {

        if (this->getDimensionality() != aAddedPoint.getDims()) {
            throw DimensionalityMismatchEx(this->getDimensionality(), aAddedPoint.getDims());
        }


        LNodePtr node= new LNode(aAddedPoint, nullptr);
        if (__points == nullptr)
        {
            __points = node;

        }
        else
        {

            LNodePtr currentPtr = __points;
            LNodePtr prevPtr = nullptr;
            while (currentPtr != nullptr) {


                if (currentPtr->point > aAddedPoint)
                {
                    break;
                }
                else
                {
                    prevPtr = currentPtr;
                    currentPtr = currentPtr->next;
                }
            }
            if (currentPtr == __points)
            {

                node->next = __points;
                __points = node;

            }
            else
            {

                node->next = currentPtr;
                prevPtr->next = node;

            }

        }
        __size++;
        centroid.setValid(false);


    }

    const Point &Cluster::remove(const Point &aRemovedPoint) {

        if(this->getDimensionality() != aRemovedPoint.getDims())
        {
            throw DimensionalityMismatchEx(this->getDimensionality(), aRemovedPoint.getDims());
        }

        LNodePtr prevPtr = nullptr;
        LNodePtr currentPtr = __points;

        if (currentPtr !=nullptr && currentPtr->point == aRemovedPoint)
        {
            __points = __points->next;
            delete currentPtr;
            __size--;
            centroid.setValid(false);
            return aRemovedPoint;
        }
        while (currentPtr != nullptr && aRemovedPoint != currentPtr->point)
        {
            prevPtr = currentPtr;
            currentPtr = currentPtr->next;
        }

        prevPtr->next = currentPtr->next;

        delete currentPtr;

        __size--;

        centroid.setValid(false);

        return aRemovedPoint;



    }

    bool Cluster::contains(const Point &aPoint) const {

        if (this->getDimensionality() != aPoint.getDims()) {
            throw DimensionalityMismatchEx(this->getDimensionality(), aPoint.getDims());
        }

        LNodePtr currentN = __points;

        bool containts = false;

        for (; currentN != nullptr; currentN = currentN->next) {

            if (currentN->point == aPoint) {
                containts = true;
                break;
            }
        }

        return containts;

    }

    // Centroid functions
    // pick k initial centroids
    void Cluster::pickCentroids(unsigned int k, Point **pointArray) {

        std::cout << "NEED TOO DO pickCentroids\n";

    }

//
//        // Overloaded operators
//
//        // Members: Subscript
    //  notice: const
    const Point &Cluster::operator[](unsigned int index) const {


        if (__size == 0) throw EmptyClusterEx();
        if (index >= __size) throw OutOfBoundsEx(__size, index);


        LNodePtr cursor = __points;

        for (int count = 0; (count < index) && (cursor->next != nullptr); count++)

            cursor = cursor->next;

        return cursor->point;

    }

//        // Members: Compound assignment (Point argument)
    Cluster &Cluster::operator+=(const Point &aPoint) {

        if (__dimensionality != aPoint.getDims()) {
            throw DimensionalityMismatchEx(__dimensionality, aPoint.getDims());
        }

        if (!__in(aPoint)) {
            add(aPoint);
        }

        return *this;


    }

    Cluster &Cluster::operator-=(const Point &aPoint) {

        if (__dimensionality != aPoint.getDims())
            throw DimensionalityMismatchEx(__dimensionality, aPoint.getDims());

        remove(aPoint);

        return *this;

    }


    // Members: Compound assignment (Cluster argument)
//     union
    Cluster &Cluster::operator+=(const Cluster &clusterF) {

        if (__dimensionality != clusterF.__dimensionality) {
            throw DimensionalityMismatchEx(__dimensionality, clusterF.__dimensionality);
        }


        for (int index = 0; index < clusterF.__size; index++) {

            if (!contains(clusterF[index])) {

                add(clusterF[index]);

            }
        }

        return *this;


    }

    // (asymmetric) difference
    Cluster &Cluster::operator-=(const Cluster &clusterF) {

        if (__dimensionality != clusterF.__dimensionality)
            throw DimensionalityMismatchEx(__dimensionality, clusterF.__dimensionality);

        LNodePtr currentN = clusterF.__points;

        for (; currentN != nullptr; currentN = currentN->next) {

            if (contains(currentN->point)) {
                remove(currentN->point);
            }
        }

        return *this;
    }

//
//        // Friends: IO
    std::ostream &operator<<(std::ostream &outPoints, const Cluster &clusterF) {

        LNodePtr currentN = clusterF.__points;

        for (; currentN != nullptr; currentN = currentN->next) {

            outPoints << currentN->point;
            outPoints << '\n';

        }

        return outPoints;


    }

    std::istream &operator>>(std::istream &inPoint, Cluster &clusterF) {

        std::string holder;
        while (getline(inPoint, holder)) {
            if (holder.empty()) {
                return inPoint;
            }
            int count = std::count(holder.begin(), holder.end(), ',');
            Point ptr(count + 1);
            std::istringstream ss(holder);
            ss >> ptr;
            clusterF.add(ptr);
        }
        return inPoint;

    }

//
//        // Friends: Comparison
    bool operator==(const Cluster &lhClust, const Cluster &rhClust) {

        if (lhClust.__dimensionality != rhClust.__dimensionality)
        {
            throw DimensionalityMismatchEx(lhClust.__dimensionality, rhClust.__dimensionality);
        }

        LNodePtr headLhs = lhClust.__points;
        LNodePtr headRhs = rhClust.__points;

        bool theEnd = true;




        while (headLhs != nullptr && headRhs != nullptr) {

            if (headLhs->point != headRhs->point) {
                bool state = false;

                return state;
            }
            else {
                headRhs = headRhs->next;

                headLhs = headLhs->next;
            }

        }

        if (headLhs != nullptr || headRhs != nullptr) {
            theEnd = false;

            return theEnd;
        }
        else {
            return theEnd;
        }


    }

    bool operator!=(const Cluster &lhClust, const Cluster &rhClust) {


        bool state = false;

        if (lhClust == rhClust) {
            return state;
        }
        else {
            state = true;

            return state;
        }


    }

//
//        // Friends: Arithmetic (Cluster and Point)
    const Cluster operator+(const Cluster &lhClust, const Point &rhPoint) {

        Cluster clusterF(lhClust);
        clusterF += rhPoint;

        return clusterF;


    }

    const Cluster operator-(const Cluster &lhClust, const Point &rhPoint) {

        Cluster clusterF(lhClust);

        clusterF -= rhPoint;

        return clusterF;

    }

//
//        // Friends: Arithmetic (two Clusters)
    const Cluster operator+(const Cluster &lhClust, const Cluster &rhClust) {

        Cluster clusterF(lhClust);

        clusterF += rhClust;

        return clusterF;

    }

    const Cluster operator-(const Cluster &lhClust, const Cluster &rhClust) {

        Cluster clusterF(lhClust);

        clusterF -= rhClust;

        return clusterF;

    }


    //Move class functions.
    Cluster::Move::Move(const Point &p, Cluster &from, Cluster &to) : __p(p), __from(from), __to(to) { }

    void Cluster::Move::perform() {

        __to.add(__from.remove(__p));

        __to.centroid.setValid(false);

        __from.centroid.setValid(false);

        if (__to.__size == 0)
            __to.centroid.toInfinity();
        if (__from.__size == 0)
            __from.centroid.toInfinity();

    }


}