//
// Created by Byron on 3/18/2016.
//

#include <iostream>
#include "Exceptions.h"

using namespace Clustering;

namespace Clustering {

    //OutOfBoundsEx getters and overloaded ostream operator.
    OutOfBoundsEx::OutOfBoundsEx(unsigned int c, int r) {

        __current = c;
        __rhs = r;

        __name = "OutOfBoundsEx";
    }

    unsigned int  OutOfBoundsEx::getCurrent() const {

        return __current;
    }

    int OutOfBoundsEx::getRhs() const {

        return __rhs;
    }

    std::string OutOfBoundsEx::getName() const {

        return __name;
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex) {

        os << ex.getName() << " | correct exception: " << ex.getCurrent() << " | offending argument: " << ex.getRhs() <<
        std::endl;

        return os;

    }

    //DimensionalityMismatchEx getters and overloaded ostream operator.
    DimensionalityMismatchEx::DimensionalityMismatchEx(unsigned int c, unsigned int r) {

        __current = c;
        __rhs = r;

        __name = "DimensionalityMismatchEx";

    }

    unsigned int DimensionalityMismatchEx::getCurrent() const {

        return __current;
    }

    unsigned int DimensionalityMismatchEx::getRhs() const {

        return __rhs;

    }

    std::string DimensionalityMismatchEx::getName() const {

        return __name;

    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex) {

        os << ex.getName() << " | correct exception: " << ex.getCurrent() << " | offending argument: " << ex.getRhs() <<
        std::endl;

        return os;

    }

    //ZeroClustersEx() getters and overloaded ostream operator.
    ZeroClustersEx::ZeroClustersEx() {

        __name = "ZeroClustersEx";

    }

    std::string ZeroClustersEx::getName() const {

        return __name;

    }

    std::ostream &operator<<(std::ostream &os, const ZeroClustersEx &ex) {

        os << ex.getName() << std::endl;

        return os;

    }

    //DataFileOpenEx getters and overloaded ostream operator..
    DataFileOpenEx::DataFileOpenEx(std::string filename) {

        __name = "DataFileOpenEx";

        __filename = filename;

    }

    std::string DataFileOpenEx::getFilename() const {

        return __filename;

    }

    std::string DataFileOpenEx::getName() const {

        return __name;

    }

    std::ostream &operator<<(std::ostream &os, const DataFileOpenEx &ex) {

        os << ex.getName() << " | Name of File: " << ex.__filename << std::endl;

        return os;

    }

    //ZeroDimensionsEx getters and overloaded ostream operator.
    ZeroDimensionsEx::ZeroDimensionsEx() {

        __name = "ZeroDimensionsEx";

    }

    std::string ZeroDimensionsEx::getName() const {

        return __name;

    }

    std::ostream &operator<<(std::ostream &os, const ZeroDimensionsEx &ex) {

        os << ex.getName() << std::endl;

        return os;

    }

    //EmptyClusterEx getters and overloaded ostream operator.
    EmptyClusterEx::EmptyClusterEx() {

        __name = "EmptyClusterEx";

    }

    std::string EmptyClusterEx::getName() const {

        return __name;

    }

    std::ostream &operator<<(std::ostream &os, const EmptyClusterEx &ex) {

        os << ex.getName() << std::endl;

        return os;
    }

}

