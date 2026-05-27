#include <gtest/gtest.h>
#include <log.hpp>

TEST(LogTest, InitLogNoChannel)
{
    EXPECT_NO_THROW(goodlog::logInit("/tmp/logtest/", 2, 2, 1, 3));
}

TEST(LogTest, InitLogWithChannel)
{
    EXPECT_NO_THROW(goodlog::logInit("/tmp/logtest/", 2, 2, 1, 3, "test_channel"));
}

TEST(LogTest, RejectsInvalidEncryptionKey)
{
    goodlog::LogOptions options;
    options.encryption = goodlog::EncryptionMode::Aes256Gcm;
    options.encryption_key_hex = "short-key";

    EXPECT_THROW(goodlog::logInit("/tmp/logtest/", 2, 2, 1, 3, options), std::invalid_argument);
}

TEST(LogTest, GetFileNameMacro)
{
    std::string path = "/home/user/test.cpp";
    EXPECT_EQ(GetFileName(path), "test.cpp");
    EXPECT_EQ(GetFileName("test.cpp"), "test.cpp");
}
