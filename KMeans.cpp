//
// Created by Byron on 3/18/2016.
//
#include <fstream>
#include "KMeans.h"
#include "Point.h"
#include "Cluster.h"
#include "Exceptions.h"

using namespace Clustering;

namespace Clustering{

    KMeans::KMeans(unsigned int dim, unsigned int k, std::string filename, unsigned int maxIter){


        __dimensionality = dim;


        __k = k;
        if(__k == 0) throw ZeroDimensionsEx();


        __clusters = new Cluster*[__k];
        for (int index = 0; index < k ; index++) {

            __clusters[index] = new Cluster(__dimensionality);

        }

        __initCentroids = new Point *[__k];
        for (int index = 0; index < k ; index++) {

            __initCentroids[index] = new Point(__dimensionality);

        }

        __iFileName = filename;
        std::ifstream inputFile;
        inputFile.open(__iFileName);

        if(inputFile.fail()) throw DataFileOpenEx(__iFileName);

        __maxIter = maxIter;

        __numIter = 0;

        __numNonempty = 0;

        __numMovesLastIter = 0;


    }

    KMeans::~KMeans(){

        for (int index = 0; index < __k ; ++index) {
            delete __clusters[index];
        }

        delete[]__clusters;

        for (int index = 0; index < __k ; ++index) {
            delete __initCentroids[index];
        }

        delete[] __initCentroids;

    }

//    // accessors
    unsigned int KMeans::getMaxIter(){

        return __maxIter;

    }

    unsigned int KMeans::getNumIters(){

        return __numIter;

    }
    unsigned int KMeans::getNumNonemptyClusters(){

        return __numNonempty;

    }

    unsigned int KMeans::getNumMovesLastIter(){

        return __numMovesLastIter;

    }

    // element access (for testing, no bounds checking)

    Cluster &KMeans::operator[](unsigned int u){

        return *__clusters[u];

    }

    const Cluster &KMeans::operator[](unsigned int u) const{

        return *__clusters[u];

    }

    // write out the results to a file
    std::ostream &operator<<(std::ostream &os, const KMeans &kmeans){

        for (int index = 0; index < kmeans.__k;  index++) {
            os << kmeans[index];
        }
        return os;


    }

    // clustering functions
    void KMeans::run(){

        std::cout << "KMEANS RUN \n";
    }


}