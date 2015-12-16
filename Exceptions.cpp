//
// Created by Julian Abbott-Whitley on 12/15/15.
//


#include <iostream>
#include "Exceptions.h"
#include "Game.h"

namespace Gaming {


    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight,
                             unsigned width, unsigned height) :
            __exp_width(expWidth),
            __exp_height(expHeight),
            __width(width),
            __height(height)
    {}


    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight,
                                                       unsigned width, unsigned height) :
            DimensionEx::DimensionEx(minWidth, minHeight, width, height) {
        __name = "InsufficientDimensionsEx";
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {

    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight,
                                 unsigned width, unsigned height) :
            DimensionEx(Game::MIN_WIDTH,
                        Game::MIN_HEIGHT,
                        Game::MIN_WIDTH,
                        Game::MIN_HEIGHT) {
        __name = "OutOfBoundsEx";
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {

    }


    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        os << ex.__name;
        return os;
    }

}