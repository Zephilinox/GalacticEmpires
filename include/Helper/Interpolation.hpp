#ifndef INTERPOLATION_HPP
#define INTERPOLATION_HPP

/* Needed on some platforms for access to the M_PI constant" */
#define _USE_MATH_DEFINES
#include <cmath>

class Interpolation
{
    public:
        template <typename T>
        static T linear(T lower, T upper, T time);

        template <typename T>
        static T cosine(T lower, T upper, T time);
};

/* See here: http://en.wikipedia.org/wiki/Linear_interpolation#Programming_language_support */
template <typename T>
T Interpolation::linear(T lower, T upper, T time)
{
    return (1 - time) * lower + time * upper;
}

/* See here: http://paulbourke.net/miscellaneous/interpolation/ */
template <typename T>
T Interpolation::cosine(T lower, T upper, T time)
{
    T tmp = (1 - std::cos(time * M_PI)) / 2;
    return (lower * (1 - tmp) + upper * tmp);
}

#endif
