#ifndef CMAKE_TEMPLATE_LIB_HPP
#define CMAKE_TEMPLATE_LIB_HPP

#include <vector>
#include <tuple>

/**
 * @brief
 * Accumulate a vector to produce the mean and the first moment of the distribution.
 * This computes the mean and the first moment of a vector of double values.
 *
 * @param values The vector of values
 * @return
 */
std::tuple<double, double> accumulate_vector(const std::vector<double>& values);

#endif //CMAKE_TEMPLATE_LIB_HPP