Endn
=============

[![👷 CI](https://github.com/OlivierLDff/Endn/actions/workflows/main.yml/badge.svg)](https://github.com/OlivierLDff/Endn/actions/workflows/main.yml)

A cross platform C++ library to get rid with of binary serialization issues. This library can serialize in buffer the most common types.

## Supported Types

All the types are from `cstdint`.

|      Type       |  Size (in bytes)   |      Read       |      Write      |
| :-------------: | :----------------: | :-------------: | :-------------: |
| `std::uint8_t`  |  `UINT8_SIZE` : 1  |  **GET_UINT8**  |  **SET_UINT8**  |
|  `std::int8_t`  |  `INT8_SIZE` : 1   |  **GET_INT8**   |  **SET_INT8**   |
| `std::uint16_t` | `UINT16_SIZE` : 2  | **GET_UINT16**  | **SET_UINT16**  |
| `std::int16_t`  |  `INT16_SIZE` : 2  |  **GET_INT16**  |  **SET_INT16**  |
| `std::uint32_t` | `UINT32_SIZE` : 4  | **GET_UINT32**  | **SET_UINT32**  |
| `std::int32_t`  |  `INT32_SIZE` : 4  |  **GET_INT32**  |  **SET_INT32**  |
| `std::uint48_t` | `UINT48_SIZE` : 6  | **GET_UINT48**  | **SET_UINT48**  |
| `std::int48_t`  |  `INT48_SIZE` : 6  |  **GET_INT48**  |  **SET_INT48**  |
| `std::uint64_t` | `UINT64_SIZE` : 8  | **GET_UINT64**  | **SET_UINT64**  |
| `std::int64_t`  |  `INT64_SIZE` : 8  |  **GET_INT64**  |  **SET_INT64**  |
|     `float`     | `FLOAT32_SIZE` : 4 | **GET_FLOAT32** | **SET_FLOAT32** |
|    `double`     | `FLOAT64_SIZE` : 8 | **GET_FLOAT64** | **SET_FLOAT64** |

## Quick Start

**Endn** provide 2 main namespace: `endn::little` and `endn::big`. You should use one or the other depending on which format you need to handle.

If you need to choose a format for you protocol, you should go with little endian because most cpu nowadays are little endian. This will reduce execution on most machine.

### Serialization

Both namespace provide function in the form `GET_<TYPE>`. That return a copy of the type in host ordered bytes.

Read function come with 2 signatures:

* `(const std::uint8_t* buf)` : Equivalent of second signature with `offset = 0`.
* `(const std::uint8_t* buf, const std::size_t offset)`

```c++
#include <Endn/Little.hpp>
#include <Endn/Big.hpp>

void main()
{
    std::uint8_t buffer[] = {0x12, 0x34, 0x56, 0x78};

    std::uint32_t u32;
    // Value is 0x012345678
    u32 = endn::big::GET_UINT32(buffer);
    // Value is 0x78563412
    u32 = endn::little::GET_UINT32(buffer);

    std::uint16_t u16;
    // Read at offset, value is 0x1234
    u16 = endn::big::GET_UINT16(buffer, 0);
    // Read at offset, value is 0x3456
    u16 = endn::big::GET_UINT16(buffer, 1);
    // Read at offset, value is 0x5678
    u16 = endn::big::GET_UINT16(buffer, 2);
}
```

### Deserialization

To write, both namespace provide `SET_<TYPE>` functions. They come with 3 signatures:

* `(std::uint8_t * buf, const <type> val)`: Write at offset 0 of `buf`
* `(std::uint8_t* buf, const std::size_t offset, const <type> val` : Write at offset `offset` of `buf`.
* `(std::uint8_t* buf, const std::size_t offset, const <type> val, std::size_t& length)`: Write at offset `offset` of `buf` and increment `length` of size of `<type>`. This signature is useful to chain write into a buffer.

```c++
#include <Endn/Little.hpp>
#include <Endn/Big.hpp>

void main()
{
    std::uint8_t buffer[] = {0x12, 0x34, 0x56, 0x78};

    // buffer is now {0xAB, 0xCD, 0x56, 0x78}
    endn::big::SET_UINT16(buffer, 0xABCD);
    // buffer is now {0xCD, 0xAB, 0x56, 0x78}
    endn::little::SET_UINT16(buffer, 0xABCD);

    // buffer is now {0xCD, 0xAB, 0x12, 0x34}
    endn::big::SET_UINT16(buffer, 2, 0x1234);

    // buffer is now {0xCD, 0x56, 0x78, 0x34}
    endn::little::SET_UINT16(buffer, 1, 0x5678);

    std::size_t length = 0;

    // buffer is now {0xCD, 0x56, 0x12, 0x34}
    // length is now 2
    endn::big::SET_UINT16(buffer, 2, 0x1234, length);
}
```

To read array it is possible to memcpy from buffer to a host buffer with `MEMCPY_<SIZE>` functions.

### Code depending on host endianess

When linking with LibEndian, an useful defined value can be used: `ENDN_IS_BIG_ENDIAN`. This give information about the executing host. In your code you can do thing like:

```c++
#ifdef ENDN_IS_BIG_ENDIAN
// Big endian code
#else
// Little endian code
#endif
```

## Build with CMake

**Endn** is an INTERFACE library, this mean it won't be build into a library, but carry dependencies of include, and define. Add it to your cmake project by using `add_subdirectory` or by using the `FetchContent` feature.

```cmake
# ...
include(FetchContent)
FetchContent_Declare(
    Endn
    GIT_REPOSITORY "https://github.com/OlivierLDff/Endn"
    GIT_TAG        "master"
)
# ...
FetchContent_MakeAvailable(Endn)
# ...

target_link_libraries(MyTarget Endn)
```

### Input

- **ENDN_TARGET** : Name of the library target. *Default : "LibEndian"*
- **ENDN_PROJECT** : Name of the project. *Default : "LibEndian"*
- **ENDN_ENABLE_BSWAP**: Enable build in swap function if available. *Default: ON*.
- **ENDN_ENABLE_TESTS**: Enable Endn unit tests. *Default: OFF*.

### Output

- **ENDN_TARGET** : Output target to link to.
- **ENDN_VERSION** : Current version of the library

## Revisions

* **1.0.0** : Initial work
	* **1.0.1** : Fix CMakeLists status
	* **1.0.2** : Fix CMakeLists file name
* **v1.2.0** : Hard fork of libendian
  * Drop support for class, to use namespace instead.
  * Use `std` types instead of `c` types for `*int*`.
  * Library is now an `INTERFACE` instead of a binary library.
* **v1.3.0**: Critical fix for GET_UINT16/32/48/64 (casting issue)
  * Unit tests on amd64 (windows/mac/linux)
  * Unit tests on arm64/ppc64le/s390x (linux)
