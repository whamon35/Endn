/**
 * \file Endn.hpp
 * \brief Common define for the library
 */
#ifndef __ENDN_HPP__
#define __ENDN_HPP__

#include <cstdint>

namespace endn {

/** Size of std::uint8_t variable (1 byte) */
static const std::uint8_t UINT8_SIZE = 1;
/** Size of uint16_t variable (2 bytes) */
static const std::uint8_t UINT16_SIZE = 2;
/** Size of uint32_t variable (4 bytes) */
static const std::uint8_t UINT32_SIZE = 4;
/** Size of uint48_t variable (6 bytes) */
static const std::uint8_t UINT48_SIZE = 6;
/** Size of uint64_t variable (8 bytes) */
static const std::uint8_t UINT64_SIZE = 8;

/** Size of int8_t variable (1 byte) */
static const std::uint8_t INT8_SIZE = 1;
/** Size of int16_t variable (2 bytes) */
static const std::uint8_t INT16_SIZE = 2;
/** Size of int32_t variable (4 bytes) */
static const std::uint8_t INT32_SIZE = 4;
/** Size of int48_t variable (6 bytes) */
static const std::uint8_t INT48_SIZE = 6;
/** Size of int64_t variable (8 bytes) */
static const std::uint8_t INT64_SIZE = 8;

/** Size of float variable (6 bytes) */
static const std::uint8_t FLOAT32_SIZE = 4;
/** Size of double variable (8 bytes) */
static const std::uint8_t FLOAT64_SIZE = 8;

inline bool IS_16_ALIGNED(const std::uintptr_t ptr)
{
    return ptr % 2 == 0;
}
inline bool IS_32_ALIGNED(const std::uintptr_t ptr)
{
    return ptr % 4 == 0;
}
inline bool IS_64_ALIGNED(const std::uintptr_t ptr)
{
    return ptr % 8 == 0;
}

inline bool IS_16_ALIGNED(const std::uint8_t* ptr)
{
    return IS_16_ALIGNED(std::uintptr_t(ptr));
}
inline bool IS_32_ALIGNED(const std::uint8_t* ptr)
{
    return IS_32_ALIGNED(std::uintptr_t(ptr));
}
inline bool IS_64_ALIGNED(const std::uint8_t* ptr)
{
    return IS_64_ALIGNED(std::uintptr_t(ptr));
}

inline bool OVERLAP(const std::uintptr_t ptr1, const std::uintptr_t ptr2, const std::uint64_t count)
{
    return (ptr1 <= ptr2 && ptr1 + count > ptr2) || (ptr2 <= ptr1 && ptr2 + count > ptr1);
}

}

#endif
