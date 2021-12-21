#ifndef VIRTUAL_GALAXY_BASE_HPP
#define VIRTUAL_GALAXY_BASE_HPP

#include <memory>
#include <functional>
#include <utility>
#include <string>

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

/**
 * @brief Cannot be copied nor moved to a different owner
 */
class NoCopyNoMove {
public:
    NoCopyNoMove(const NoCopyNoMove&) = delete;

    NoCopyNoMove& operator=(const NoCopyNoMove&) = delete;

    NoCopyNoMove(NoCopyNoMove&&) = delete;

    NoCopyNoMove& operator=(NoCopyNoMove&&) = delete;

    virtual ~NoCopyNoMove() = default;

protected:
    NoCopyNoMove() = default;
};

#endif //VIRTUAL_GALAXY_BASE_HPP
