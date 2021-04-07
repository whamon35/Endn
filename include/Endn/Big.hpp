/**
 * \file Big.hpp
 * \brief Serialize binary data in Big Endian way
 */
#ifndef __ENDN_BIG_HPP__
#define __ENDN_BIG_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Library Headers
#include <Endn/Endn.hpp>
#include <Endn/Helpers.hpp>

// C++ Headers
#include <cstdint>
#include <cstddef>
#include <cstring>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

namespace endn {
namespace big {

// ─────────────────────────────────────────────────────────────
//                  CLASS
// ─────────────────────────────────────────────────────────────

/**
 * \brief Deserialize an std::uint8_t from buffer
 * \param buf Pointer to the std::uint8_t
 * \return The deserialized data
 */
inline std::uint8_t GET_UINT8(const std::uint8_t* buf)
{
    return ((std::uint8_t)buf[0]);
}

/**
 * \brief Deserialize an std::uint16_t from buffer
 * \param buf Pointer to the std::uint16_t
 * \return The deserialized data
 */
inline std::uint16_t GET_UINT16(const std::uint8_t* buf)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_16_ALIGNED(std::uintptr_t(buf)))
        return std::uint16_t(*(const std::uint16_t*)(buf));
#    else
    if(IS_16_ALIGNED(std::uintptr_t(buf)))
        return bswap_16(std::uint16_t(*buf));
#    endif
#endif
    return ((std::uint16_t)buf[0] << 8) | ((std::uint16_t)buf[1]);
}

/**
 * \brief Deserialize an std::uint32_t from buffer
 * \param buf Pointer to the std::uint32_t
 * \return The deserialized data
 */
inline std::uint32_t GET_UINT32(const std::uint8_t* buf)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_32_ALIGNED(std::uintptr_t(buf)))
        return std::uint32_t(*(const std::uint32_t*)(buf));
#    else
    if(IS_32_ALIGNED(std::uintptr_t(buf)))
        return bswap_32(std::uint32_t(*buf));
#    endif
#endif
    return ((std::uint32_t)buf[0] << 24) | ((std::uint32_t)buf[1] << 16) | ((std::uint32_t)buf[2] << 8) | ((std::uint32_t)buf[3]);
}

/**
 * \brief Deserialize an std::uint48_t from buffer.
 * \note It is return on a std::uint64_t for convenience
 * \param buf Pointer to the std::uint48_t
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT48(const std::uint8_t* buf)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
        return std::uint64_t(*(const std::uint64_t*)(buf)) & std::uint64_t(0xFFFFFFFFFFFF);
#    else
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
        return bswap_64(std::uint64_t(*buf)) & std::uint64_t(0xFFFFFFFFFFFF);
#    endif
#endif
    return ((std::uint64_t)buf[0] << 40) | ((std::uint64_t)buf[1] << 32) | ((std::uint64_t)buf[2] << 24) | ((std::uint64_t)buf[3] << 16)
           | ((std::uint64_t)buf[4] << 8) | ((std::uint64_t)buf[5]);
}

/**
 * \brief Deserialize an std::uint64_t from buffer
 * \param buf Pointer to the std::uint64_t
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT64(const std::uint8_t* buf)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
        return std::uint64_t(*(const std::uint64_t*)(buf));
#    else
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
        return bswap_64(std::uint64_t(*buf));
#    endif
#endif
    return ((std::uint64_t)buf[0] << 56) | ((std::uint64_t)buf[1] << 48) | ((std::uint64_t)buf[2] << 40) | ((std::uint64_t)buf[3] << 32)
           | ((std::uint64_t)buf[4] << 24) | ((std::uint64_t)buf[5] << 16) | ((std::uint64_t)buf[6] << 8) | ((std::uint64_t)buf[7]);
}

/**
 * \brief Deserialize an int8_t from buffer
 * \param buf Pointer to the int8_t
 * \return The deserialized data
 */
inline int8_t GET_INT8(const std::uint8_t* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int8_t*)(&value);
}

/**
 * \brief Deserialize an int16_t from buffer
 * \param buf Pointer to the int16_t
 * \return The deserialized data
 */
inline int16_t GET_INT16(const std::uint8_t* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int16_t*)(&value);
}

/**
 * \brief Deserialize an int32_t from buffer
 * \param buf Pointer to the int32_t
 * \return The deserialized data
 */
inline int32_t GET_INT32(const std::uint8_t* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int32_t*)(&value);
}

/**
 * \brief Deserialize an int48_t from buffer.
 * \note It is return on a int64_t for convenience
 * \param buf Pointer to the std::uint48_t
 * \return The deserialized data
 */
inline int64_t GET_INT48(const std::uint8_t* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int64_t*)(&value);
}

/**
 * \brief Deserialize an int64_t from buffer
 * \param buf Pointer to the int64_t
 * \return The deserialized data
 */
inline int64_t GET_INT64(const std::uint8_t* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int64_t*)(&value);
}

/**
 * \brief Deserialize an float from buffer
 * \param buf Pointer to the float
 * \return The deserialized data
 */
inline float GET_FLOAT32(const std::uint8_t* buf)
{
    const std::uint32_t value = GET_UINT32(buf);
    return *(float*)(&value);
}

/**
 * \brief Deserialize an double from buffer
 * \param buf Pointer to the double
 * \return The deserialized data
 */
inline double GET_FLOAT64(const std::uint8_t* buf)
{
    const std::uint64_t value = GET_UINT64(buf);
    return *(double*)(&value);
}

/**
 * \brief Deserialize an std::uint8_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint8_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint8_t GET_UINT8(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_UINT8(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint16_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint16_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint16_t GET_UINT16(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_UINT16(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint32_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint32_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint32_t GET_UINT32(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_UINT32(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint48_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint48_t* (in bytes)
 * \note Store in a std::uint64_t for convenience
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT48(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_UINT48(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint64_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint64_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT64(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_UINT64(&buf[offset]);
}

/**
 * \brief Deserialize an int8_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int8_t* (in bytes)
 * \return The deserialized data
 */
inline int8_t GET_INT8(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_INT8(&buf[offset]);
}

/**
 * \brief Deserialize an int16_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int16_t* (in bytes)
 * \return The deserialized data
 */
inline int16_t GET_INT16(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_INT16(&buf[offset]);
}

/**
 * \brief Deserialize an int32_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int32_t* (in bytes)
 * \return The deserialized data
 */
inline int32_t GET_INT32(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_INT32(&buf[offset]);
}

/**
 * \brief Deserialize an int48_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int48_t* (in bytes)
 * \note Store in a int64_t for convenience
 * \return The deserialized data
 */
inline int64_t GET_INT48(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_INT48(&buf[offset]);
}

/**
 * \brief Deserialize an int64_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int64_t* (in bytes)
 * \return The deserialized data
 */
inline int64_t GET_INT64(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_INT64(&buf[offset]);
}

/**
 * \brief Deserialize an float from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an float* (in bytes)
 * \return The deserialized data
 */
inline float GET_FLOAT32(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_FLOAT32(&buf[offset]);
}

/**
 * \brief Deserialize an double from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an double  (in bytes)
 * \return The deserialized data
 */
inline double GET_FLOAT64(const std::uint8_t* buf, const std::size_t offset)
{
    return GET_FLOAT64(&buf[offset]);
}

/**
 * \brief Serialize a std::uint8_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT8(std::uint8_t* buf, const std::uint8_t val)
{
    buf[0] = (std::uint8_t)(val & 0xFF);
}

/**
 * \brief Serialize a std::uint16_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT16(std::uint8_t* buf, const std::uint16_t val)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_16_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint16_t*)buf) = val;
        return;
    }
#    else
    if(IS_16_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint16_t*)buf) = bswap_16(val);
        return;
    }
#    endif
#endif
    buf[0] = (std::uint8_t)((val >> 8) & 0xFF);
    buf[1] = (std::uint8_t)(val & 0xFF);
}

/**
 * \brief Serialize a std::uint32_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT32(std::uint8_t* buf, const std::uint32_t val)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_32_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint32_t*)buf) = val;
        return;
    }
#    else
    if(IS_32_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint32_t*)buf) = bswap_32(val);
        return;
    }
#    endif
#endif
    buf[0] = (std::uint8_t)((val >> 24) & 0xFF);
    buf[1] = (std::uint8_t)((val >> 16) & 0xFF);
    buf[2] = (std::uint8_t)((val >> 8) & 0xFF);
    buf[3] = (std::uint8_t)(val & 0xFF);
}

/**
 * \brief Serialize a std::uint48_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 * \note For convenience the std::uint48 is stored into a std::uint64_t
 */
inline void SET_UINT48(std::uint8_t* buf, const std::uint64_t val)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint64_t*)buf) = val & std::uint64_t(0xFFFFFFFFFFFF);
        return;
    }
#    else
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint64_t*)buf) = bswap_64(val) & std::uint64_t(0xFFFFFFFFFFFF);
        return;
    }
#    endif
#endif
    buf[0] = (std::uint8_t)((val >> 40) & 0xFF);
    buf[1] = (std::uint8_t)((val >> 32) & 0xFF);
    buf[2] = (std::uint8_t)((val >> 24) & 0xFF);
    buf[3] = (std::uint8_t)((val >> 16) & 0xFF);
    buf[4] = (std::uint8_t)((val >> 8) & 0xFF);
    buf[5] = (std::uint8_t)(val & 0xFF);
}

/**
 * \brief Serialize a std::uint64_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT64(std::uint8_t* buf, const std::uint64_t val)
{
#ifdef ENDN_ENABLE_BSWAP
#    ifdef ENDN_IS_BIG_ENDIAN
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint64_t*)buf) = val;
        return;
    }
#    else
    if(IS_64_ALIGNED(std::uintptr_t(buf)))
    {
        (*(std::uint64_t*)buf) = bswap_64(val);
        return;
    }
#    endif
#endif
    buf[0] = (std::uint8_t)((val >> 56) & 0xFF);
    buf[1] = (std::uint8_t)((val >> 48) & 0xFF);
    buf[2] = (std::uint8_t)((val >> 40) & 0xFF);
    buf[3] = (std::uint8_t)((val >> 32) & 0xFF);
    buf[4] = (std::uint8_t)((val >> 24) & 0xFF);
    buf[5] = (std::uint8_t)((val >> 16) & 0xFF);
    buf[6] = (std::uint8_t)((val >> 8) & 0xFF);
    buf[7] = (std::uint8_t)(val & 0xFF);
}

/**
 * \brief Serialize a int8_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT8(std::uint8_t* buf, const int8_t val)
{
    SET_UINT8(buf, *(const std::uint8_t*)&val);
}

/**
 * \brief Serialize a int16_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT16(std::uint8_t* buf, const int16_t val)
{
    SET_UINT16(buf, *(const std::uint16_t*)&val);
}

/**
 * \brief Serialize a int32_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT32(std::uint8_t* buf, const int32_t val)
{
    SET_UINT32(buf, *(const std::uint32_t*)&val);
}

/**
 * \brief Serialize a int48 in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 * \note For convenience the int48 is stored into a int64_t
 */
inline void SET_INT48(std::uint8_t* buf, const int64_t val)
{
    SET_UINT48(buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a int64_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT64(std::uint8_t* buf, const int64_t val)
{
    SET_UINT64(buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a float in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_FLOAT32(std::uint8_t* buf, const float val)
{
    SET_UINT32(buf, *(const std::uint32_t*)&val);
}

/**
 * \brief Serialize a double in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_FLOAT64(std::uint8_t* buf, const double val)
{
    SET_UINT64(buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a std::uint8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT8(std::uint8_t* buf, const std::size_t offset, const std::uint8_t val)
{
    SET_UINT8(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT16(std::uint8_t* buf, const std::size_t offset, const std::uint16_t val)
{
    SET_UINT16(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT32(std::uint8_t* buf, const std::size_t offset, const std::uint32_t val)
{
    SET_UINT32(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 * \note For convenience the std::uint48 is stored into a std::uint64_t
 */
inline void SET_UINT48(std::uint8_t* buf, const std::size_t offset, const std::uint64_t val)
{
    SET_UINT48(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT64(std::uint8_t* buf, const std::size_t offset, const std::uint64_t val)
{
    SET_UINT64(&buf[offset], val);
}

/**
 * \brief Serialize a int8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT8(std::uint8_t* buf, const std::size_t offset, const int8_t val)
{
    SET_INT8(&buf[offset], val);
}

/**
 * \brief Serialize a int16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT16(std::uint8_t* buf, const std::size_t offset, const int16_t val)
{
    SET_INT16(&buf[offset], val);
}

/**
 * \brief Serialize a int32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT32(std::uint8_t* buf, const std::size_t offset, const int32_t val)
{
    SET_INT32(&buf[offset], val);
}

/**
 * \brief Serialize a int48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 * \note For convenience the int48 is stored into a int64_t
 */
inline void SET_INT48(std::uint8_t* buf, const std::size_t offset, const int64_t val)
{
    SET_INT48(&buf[offset], val);
}

/**
 * \brief Serialize a int64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT64(std::uint8_t* buf, const std::size_t offset, const int64_t val)
{
    SET_INT64(&buf[offset], val);
}

/**
 * \brief Serialize a float in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_FLOAT32(std::uint8_t* buf, const std::size_t offset, const float val)
{
    SET_FLOAT32(&buf[offset], val);
}

/**
 * \brief Serialize a double in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_FLOAT64(std::uint8_t* buf, const std::size_t offset, const double val)
{
    SET_FLOAT64(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint8_t
 * \param val Value to serialize
 */
inline void SET_UINT8(std::uint8_t* buf, const std::size_t offset, const std::uint8_t val, std::size_t& length)
{
    SET_UINT8(buf, offset, val);
    length += UINT8_SIZE;
}

/**
 * \brief Serialize a std::uint16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint16_t
 * \param val Value to serialize
 */
inline void SET_UINT16(std::uint8_t* buf, const std::size_t offset, const std::uint16_t val, std::size_t& length)
{
    SET_UINT16(buf, offset, val);
    length += UINT16_SIZE;
}

/**
 * \brief Serialize a std::uint32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint32_t
 * \param val Value to serialize
 */
inline void SET_UINT32(std::uint8_t* buf, const std::size_t offset, const std::uint32_t val, std::size_t& length)
{
    SET_UINT32(buf, offset, val);
    length += UINT32_SIZE;
}

/**
 * \brief Serialize a std::uint48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint48_t
 * \note For convenience the std::uint48 is stored into a std::uint64_t
 * \param val Value to serialize
 */
inline void SET_UINT48(std::uint8_t* buf, const std::size_t offset, const std::uint64_t val, std::size_t& length)
{
    SET_UINT48(buf, offset, val);
    length += UINT48_SIZE;
}

/**
 * \brief Serialize a std::uint64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint64_t
 * \param val Value to serialize
 */
inline void SET_UINT64(std::uint8_t* buf, const std::size_t offset, const std::uint64_t val, std::size_t& length)
{
    SET_UINT64(buf, offset, val);
    length += UINT64_SIZE;
}

/**
 * \brief Serialize a int8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int8_t
 * \param val Value to serialize
 */
inline void SET_INT8(std::uint8_t* buf, const std::size_t offset, const int8_t val, std::size_t& length)
{
    SET_INT8(buf, offset, val);
    length += INT8_SIZE;
}

/**
 * \brief Serialize a int16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int16_t
 * \param val Value to serialize
 */
inline void SET_INT16(std::uint8_t* buf, const std::size_t offset, const int16_t val, std::size_t& length)
{
    SET_INT16(buf, offset, val);
    length += INT16_SIZE;
}

/**
 * \brief Serialize a int32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int32_t
 * \param val Value to serialize
 */
inline void SET_INT32(std::uint8_t* buf, const std::size_t offset, const int32_t val, std::size_t& length)
{
    SET_INT32(buf, offset, val);
    length += INT32_SIZE;
}

/**
 * \brief Serialize a int48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int48_t
 * \note For convenience the int48 is stored into a int64_t
 * \param val Value to serialize
 */
inline void SET_INT48(std::uint8_t* buf, const std::size_t offset, const int64_t val, std::size_t& length)
{
    SET_INT48(buf, offset, val);
    length += INT48_SIZE;
}

/**
 * \brief Serialize a int64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int64_t
 * \param val Value to serialize
 */
inline void SET_INT64(std::uint8_t* buf, const std::size_t offset, const int64_t val, std::size_t& length)
{
    SET_INT64(buf, offset, val);
    length += INT64_SIZE;
}

/**
 * \brief Serialize a float in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of float
 * \param val Value to serialize
 */
inline void SET_FLOAT32(std::uint8_t* buf, const std::size_t offset, const float val, std::size_t& length)
{
    SET_FLOAT32(buf, offset, val);
    length += UINT32_SIZE;
}

/**
 * \brief Serialize a double in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of double
 * \param val Value to serialize
 */
inline void SET_FLOAT64(std::uint8_t* buf, const std::size_t offset, const double val, std::size_t& length)
{
    SET_FLOAT64(buf, offset, val);
    length += UINT64_SIZE;
}

/**
 * \brief memcpy from a big endian 16 bits to a local buffer
 * \param dest ptr to local std::uint16_t buffer, that contains std::uint16_t
 * \param src ptr to big endian buffer of std::uint16_t that need to be deserialized in dest
 * \param count Number of std::uint16_t in src
 */
inline void MEMCPY_UINT16(std::uint16_t* dest, const std::uint8_t* src, const std::size_t count)
{
#ifndef ENDN_IS_BIG_ENDIAN
    if(IS_16_ALIGNED(src))
    {
        for(int i = 0; i < count; i += 2)
            dest[i] = GET_UINT16(src, i);
        return;
    }
#endif
    if(OVERLAP(std::uintptr_t(dest), std::uintptr_t(src), count * 2))
        memmove(dest, src, count * 2);
    else
        memcpy(dest, src, count * 2);
}

/**
 * \brief memcpy from a big endian 32 bits to a local buffer
 * \param dest ptr to local std::uint32_t buffer, that contains std::uint32_t
 * \param src ptr to big endian buffer of std::uint32_t that need to be deserialized in dest
 * \param count Number of std::uint32_t in src
 */
inline void MEMCPY_UINT32(std::uint32_t* dest, const std::uint8_t* src, const std::size_t count)
{
#ifndef ENDN_IS_BIG_ENDIAN
    if(IS_32_ALIGNED(src))
    {
        for(int i = 0; i < count; i += 4)
            dest[i] = GET_UINT32(src, i);
        return;
    }
#endif
    if(OVERLAP(std::uintptr_t(dest), std::uintptr_t(src), count * 4))
        memmove(dest, src, count * 4);
    else
        memcpy(dest, src, count * 4);
}

/**
 * \brief memcpy from a big endian 64 bits to a local buffer
 * \param dest ptr to local std::uint64_t buffer, that contains std::uint64_t
 * \param src ptr to big endian buffer of std::uint64_t that need to be deserialized in dest
 * \param count Number of std::uint64_t in src
 */
inline void MEMCPY_UINT64(std::uint64_t* dest, const std::uint8_t* src, const std::size_t count)
{
#ifndef ENDN_IS_BIG_ENDIAN
    if(IS_64_ALIGNED(src))
    {
        for(int i = 0; i < count; i += 8)
            dest[i] = GET_UINT64(src, i);
        return;
    }
#endif
    if(OVERLAP(std::uintptr_t(dest), std::uintptr_t(src), count * 8))
        memmove(dest, src, count * 8);
    else
        memcpy(dest, src, count * 8);
}

/**
 * \brief Deserialize an std::uint8_t from buffer
 * \param buf Pointer to the std::uint8_t
 * \return The deserialized data
 */
inline std::uint8_t GET_UINT8(const char* buf)
{
    return GET_UINT8((const std::uint8_t*)buf);
}

/**
 * \brief Deserialize an std::uint16_t from buffer
 * \param buf Pointer to the std::uint16_t
 * \return The deserialized data
 */
inline std::uint16_t GET_UINT16(const char* buf)
{
    return GET_UINT16((const std::uint8_t*)buf);
}

/**
 * \brief Deserialize an std::uint32_t from buffer
 * \param buf Pointer to the std::uint32_t
 * \return The deserialized data
 */
inline std::uint32_t GET_UINT32(const char* buf)
{
    return GET_UINT32((const std::uint8_t*)buf);
}

/**
 * \brief Deserialize an std::uint48_t from buffer.
 * \note It is return on a std::uint64_t for convenience
 * \param buf Pointer to the std::uint48_t
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT48(const char* buf)
{
    return GET_UINT48((const std::uint8_t*)buf);
}

/**
 * \brief Deserialize an std::uint64_t from buffer
 * \param buf Pointer to the std::uint64_t
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT64(const char* buf)
{
    return GET_UINT64((const std::uint8_t*)buf);
}

/**
 * \brief Deserialize an int8_t from buffer
 * \param buf Pointer to the int8_t
 * \return The deserialized data
 */
inline int8_t GET_INT8(const char* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int8_t*)(&value);
}

/**
 * \brief Deserialize an int16_t from buffer
 * \param buf Pointer to the int16_t
 * \return The deserialized data
 */
inline int16_t GET_INT16(const char* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int16_t*)(&value);
}

/**
 * \brief Deserialize an int32_t from buffer
 * \param buf Pointer to the int32_t
 * \return The deserialized data
 */
inline int32_t GET_INT32(const char* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int32_t*)(&value);
}

/**
 * \brief Deserialize an int48_t from buffer.
 * \note It is return on a int64_t for convenience
 * \param buf Pointer to the std::uint48_t
 * \return The deserialized data
 */
inline int64_t GET_INT48(const char* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int64_t*)(&value);
}

/**
 * \brief Deserialize an int64_t from buffer
 * \param buf Pointer to the int64_t
 * \return The deserialized data
 */
inline int64_t GET_INT64(const char* buf)
{
    const std::uint8_t value = GET_UINT8(buf);
    return *(int64_t*)(&value);
}

/**
 * \brief Deserialize an float from buffer
 * \param buf Pointer to the float
 * \return The deserialized data
 */
inline float GET_FLOAT32(const char* buf)
{
    const std::uint32_t value = GET_UINT32(buf);
    return *(float*)(&value);
}

/**
 * \brief Deserialize an double from buffer
 * \param buf Pointer to the double
 * \return The deserialized data
 */
inline double GET_FLOAT64(const char* buf)
{
    const std::uint64_t value = GET_UINT64(buf);
    return *(double*)(&value);
}

/**
 * \brief Deserialize an std::uint8_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint8_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint8_t GET_UINT8(const char* buf, const std::size_t offset)
{
    return GET_UINT8(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint16_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint16_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint16_t GET_UINT16(const char* buf, const std::size_t offset)
{
    return GET_UINT16(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint32_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint32_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint32_t GET_UINT32(const char* buf, const std::size_t offset)
{
    return GET_UINT32(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint48_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint48_t* (in bytes)
 * \note Store in a std::uint64_t for convenience
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT48(const char* buf, const std::size_t offset)
{
    return GET_UINT48(&buf[offset]);
}

/**
 * \brief Deserialize an std::uint64_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an std::uint64_t* (in bytes)
 * \return The deserialized data
 */
inline std::uint64_t GET_UINT64(const char* buf, const std::size_t offset)
{
    return GET_UINT64(&buf[offset]);
}

/**
 * \brief Deserialize an int8_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int8_t* (in bytes)
 * \return The deserialized data
 */
inline int8_t GET_INT8(const char* buf, const std::size_t offset)
{
    return GET_INT8(&buf[offset]);
}

/**
 * \brief Deserialize an int16_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int16_t* (in bytes)
 * \return The deserialized data
 */
inline int16_t GET_INT16(const char* buf, const std::size_t offset)
{
    return GET_INT16(&buf[offset]);
}

/**
 * \brief Deserialize an int32_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int32_t* (in bytes)
 * \return The deserialized data
 */
inline int32_t GET_INT32(const char* buf, const std::size_t offset)
{
    return GET_INT32(&buf[offset]);
}

/**
 * \brief Deserialize an int48_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int48_t* (in bytes)
 * \note Store in a int64_t for convenience
 * \return The deserialized data
 */
inline int64_t GET_INT48(const char* buf, const std::size_t offset)
{
    return GET_INT48(&buf[offset]);
}

/**
 * \brief Deserialize an int64_t from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an int64_t* (in bytes)
 * \return The deserialized data
 */
inline int64_t GET_INT64(const char* buf, const std::size_t offset)
{
    return GET_INT64(&buf[offset]);
}

/**
 * \brief Deserialize an float from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an float* (in bytes)
 * \return The deserialized data
 */
inline float GET_FLOAT32(const char* buf, const std::size_t offset)
{
    return GET_FLOAT32(&buf[offset]);
}

/**
 * \brief Deserialize an double from buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer to access to an double  (in bytes)
 * \return The deserialized data
 */
inline double GET_FLOAT64(const char* buf, const std::size_t offset)
{
    return GET_FLOAT64(&buf[offset]);
}

/**
 * \brief Serialize a std::uint8_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT8(char* buf, const std::uint8_t val)
{
    SET_UINT8((std::uint8_t*)buf, *(const std::uint8_t*)&val);
}

/**
 * \brief Serialize a std::uint16_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT16(char* buf, const std::uint16_t val)
{
    SET_UINT16((std::uint8_t*)buf, *(const std::uint16_t*)&val);
}

/**
 * \brief Serialize a std::uint32_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT32(char* buf, const std::uint32_t val)
{
    SET_UINT32((std::uint8_t*)buf, *(const std::uint32_t*)&val);
}

/**
 * \brief Serialize a std::uint48_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 * \note For convenience the std::uint48 is stored into a std::uint64_t
 */
inline void SET_UINT48(char* buf, const std::uint64_t val)
{
    SET_UINT48((std::uint8_t*)buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a std::uint64_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_UINT64(char* buf, const std::uint64_t val)
{
    SET_UINT64((std::uint8_t*)buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a int8_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT8(char* buf, const int8_t val)
{
    SET_UINT8(buf, *(const std::uint8_t*)&val);
}

/**
 * \brief Serialize a int16_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT16(char* buf, const int16_t val)
{
    SET_UINT16(buf, *(const std::uint16_t*)&val);
}

/**
 * \brief Serialize a int32_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT32(char* buf, const int32_t val)
{
    SET_UINT32(buf, *(const std::uint32_t*)&val);
}

/**
 * \brief Serialize a int48 in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 * \note For convenience the int48 is stored into a int64_t
 */
inline void SET_INT48(char* buf, const int64_t val)
{
    SET_UINT48(buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a int64_t in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_INT64(char* buf, const int64_t val)
{
    SET_UINT64(buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a float in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_FLOAT32(char* buf, const float val)
{
    SET_UINT32(buf, *(const std::uint32_t*)&val);
}

/**
 * \brief Serialize a double in the buffer
 * \param buf Pointer to the buffer
 * \param val Value to serialize
 */
inline void SET_FLOAT64(char* buf, const double val)
{
    SET_UINT64(buf, *(const std::uint64_t*)&val);
}

/**
 * \brief Serialize a std::uint8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT8(char* buf, const std::size_t offset, const std::uint8_t val)
{
    SET_UINT8(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT16(char* buf, const std::size_t offset, const std::uint16_t val)
{
    SET_UINT16(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT32(char* buf, const std::size_t offset, const std::uint32_t val)
{
    SET_UINT32(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 * \note For convenience the std::uint48 is stored into a std::uint64_t
 */
inline void SET_UINT48(char* buf, const std::size_t offset, const std::uint64_t val)
{
    SET_UINT48(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_UINT64(char* buf, const std::size_t offset, const std::uint64_t val)
{
    SET_UINT64(&buf[offset], val);
}

/**
 * \brief Serialize a int8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT8(char* buf, const std::size_t offset, const int8_t val)
{
    SET_INT8(&buf[offset], val);
}

/**
 * \brief Serialize a int16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT16(char* buf, const std::size_t offset, const int16_t val)
{
    SET_INT16(&buf[offset], val);
}

/**
 * \brief Serialize a int32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT32(char* buf, const std::size_t offset, const int32_t val)
{
    SET_INT32(&buf[offset], val);
}

/**
 * \brief Serialize a int48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 * \note For convenience the int48 is stored into a int64_t
 */
inline void SET_INT48(char* buf, const std::size_t offset, const int64_t val)
{
    SET_INT48(&buf[offset], val);
}

/**
 * \brief Serialize a int64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_INT64(char* buf, const std::size_t offset, const int64_t val)
{
    SET_INT64(&buf[offset], val);
}

/**
 * \brief Serialize a float in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_FLOAT32(char* buf, const std::size_t offset, const float val)
{
    SET_FLOAT32(&buf[offset], val);
}

/**
 * \brief Serialize a double in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param val Value to serialize
 */
inline void SET_FLOAT64(char* buf, const std::size_t offset, const double val)
{
    SET_FLOAT64(&buf[offset], val);
}

/**
 * \brief Serialize a std::uint8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint8_t
 * \param val Value to serialize
 */
inline void SET_UINT8(char* buf, const std::size_t offset, const std::uint8_t val, std::size_t& length)
{
    SET_UINT8(buf, offset, val);
    length += UINT8_SIZE;
}

/**
 * \brief Serialize a std::uint16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint16_t
 * \param val Value to serialize
 */
inline void SET_UINT16(char* buf, const std::size_t offset, const std::uint16_t val, std::size_t& length)
{
    SET_UINT16(buf, offset, val);
    length += UINT16_SIZE;
}

/**
 * \brief Serialize a std::uint32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint32_t
 * \param val Value to serialize
 */
inline void SET_UINT32(char* buf, const std::size_t offset, const std::uint32_t val, std::size_t& length)
{
    SET_UINT32(buf, offset, val);
    length += UINT32_SIZE;
}

/**
 * \brief Serialize a std::uint48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint48_t
 * \note For convenience the std::uint48 is stored into a std::uint64_t
 * \param val Value to serialize
 */
inline void SET_UINT48(char* buf, const std::size_t offset, const std::uint64_t val, std::size_t& length)
{
    SET_UINT48(buf, offset, val);
    length += UINT48_SIZE;
}

/**
 * \brief Serialize a std::uint64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of std::uint64_t
 * \param val Value to serialize
 */
inline void SET_UINT64(char* buf, const std::size_t offset, const std::uint64_t val, std::size_t& length)
{
    SET_UINT64(buf, offset, val);
    length += UINT64_SIZE;
}

/**
 * \brief Serialize a int8_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int8_t
 * \param val Value to serialize
 */
inline void SET_INT8(char* buf, const std::size_t offset, const int8_t val, std::size_t& length)
{
    SET_INT8(buf, offset, val);
    length += INT8_SIZE;
}

/**
 * \brief Serialize a int16_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int16_t
 * \param val Value to serialize
 */
inline void SET_INT16(char* buf, const std::size_t offset, const int16_t val, std::size_t& length)
{
    SET_INT16(buf, offset, val);
    length += INT16_SIZE;
}

/**
 * \brief Serialize a int32_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int32_t
 * \param val Value to serialize
 */
inline void SET_INT32(char* buf, const std::size_t offset, const int32_t val, std::size_t& length)
{
    SET_INT32(buf, offset, val);
    length += INT32_SIZE;
}

/**
 * \brief Serialize a int48_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int48_t
 * \note For convenience the int48 is stored into a int64_t
 * \param val Value to serialize
 */
inline void SET_INT48(char* buf, const std::size_t offset, const int64_t val, std::size_t& length)
{
    SET_INT48(buf, offset, val);
    length += INT48_SIZE;
}

/**
 * \brief Serialize a int64_t in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of int64_t
 * \param val Value to serialize
 */
inline void SET_INT64(char* buf, const std::size_t offset, const int64_t val, std::size_t& length)
{
    SET_INT64(buf, offset, val);
    length += INT64_SIZE;
}

/**
 * \brief Serialize a float in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of float
 * \param val Value to serialize
 */
inline void SET_FLOAT32(char* buf, const std::size_t offset, const float val, std::size_t& length)
{
    SET_FLOAT32(buf, offset, val);
    length += UINT32_SIZE;
}

/**
 * \brief Serialize a double in the buffer
 * \param buf Pointer to the buffer
 * \param offset Offset in the buffer (in bytes)
 * \param length Auto Increment this variable by the size of double
 * \param val Value to serialize
 */
inline void SET_FLOAT64(char* buf, const std::size_t offset, const double val, std::size_t& length)
{
    SET_FLOAT64(buf, offset, val);
    length += UINT64_SIZE;
}

}
}

#endif
