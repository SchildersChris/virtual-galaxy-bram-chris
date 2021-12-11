#ifndef VIRTUAL_GALAXY_BASE_HPP
#define VIRTUAL_GALAXY_BASE_HPP

#include <memory>
#include <functional>
#include <utility>
#include <cstring>

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

template<class T>
using Ref = std::shared_ptr<T>;

template<class T>
using Weak = std::weak_ptr<T>;

template<class T, typename ...TArgs>
constexpr Ref<T> CreateRef(TArgs&& ...args) {
    return std::make_shared<T>(std::forward<TArgs>(args)...);
}

template<class T>
constexpr Ref<T> MakeRef(T* instance) {
    return std::shared_ptr<T>(instance);
}

template<class T>
using Unique = std::unique_ptr<T>;

template<class T>
using UniqueDel = std::unique_ptr<T, std::function<void(T*)>>;

template<class T, typename ...TArgs>
constexpr Unique<T> CreateUnique(TArgs&& ...args) {
    return std::make_unique<T>(std::forward<TArgs>(args)...);
}

template<class T>
constexpr Unique<T> MakeUnique(T* instance) {
    return std::unique_ptr<T>(instance);
}

template<class T>
constexpr UniqueDel<T> MakeUnique(T* instance, std::function<void(T*)> deleter) {
    return UniqueDel<T>(instance, deleter);
}

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
