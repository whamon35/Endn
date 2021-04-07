#include <Endn/Big.hpp>
#include <gtest/gtest.h>

using namespace endn::big;

TEST(Big, GET_UINT8)
{
    std::uint8_t buffer[1] = {0x12};
    ASSERT_EQ(GET_UINT8(buffer), 0x12);
}

TEST(Big, GET_UINT16)
{
    {
        std::uint8_t buffer[2] = {0x12, 0x34};
        ASSERT_EQ(GET_UINT16(buffer), 0x1234);
    }

    {
        std::uint8_t buffer[3] = {0x00, 0x12, 0x34};
        ASSERT_EQ(GET_UINT16(buffer, 1), 0x1234);
    }
}

TEST(Big, GET_UINT32)
{
    {
        std::uint8_t buffer[4] = {0x12, 0x34, 0x56, 0x78};
        ASSERT_EQ(GET_UINT32(buffer), 0x12345678);
    }

    {
        std::uint8_t buffer[5] = {0x00, 0x12, 0x34, 0x56, 0x78};
        ASSERT_EQ(GET_UINT32(buffer, 1), 0x12345678);
    }
}

TEST(Big, GET_UINT48)
{
    {
        std::uint8_t buffer[6] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
        ASSERT_EQ(GET_UINT48(buffer), 0x123456789ABC);
    }

    {
        std::uint8_t buffer[7] = {0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
        ASSERT_EQ(GET_UINT48(buffer, 1), 0x123456789ABC);
    }
}

TEST(Big, GET_UINT64)
{
    {
        std::uint8_t buffer[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
        ASSERT_EQ(GET_UINT64(buffer), 0x123456789ABCDEF0);
    }

    {
        std::uint8_t buffer[9] = {0x00, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
        ASSERT_EQ(GET_UINT64(buffer, 1), 0x123456789ABCDEF0);
    }
}
