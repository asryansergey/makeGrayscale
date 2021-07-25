#include <gtest/gtest.h>

#include "../src/convertor.h"
#include "../src/exception.h"
namespace fs = std::filesystem;

namespace {
const fs::path testExamplesPath = std::filesystem::current_path() / "examples";
PngConvertor convertor;

TEST(LoadInputImage, InvalidInputPath) {
    EXPECT_THROW(convertor.loadRawSrcPng("invalid_image_path"), ConvertorException);
}

TEST(LoadInputImage, MaxImageSizeExceeded) {
    const fs::path inputImg = testExamplesPath / "size_exceeded.png";
    EXPECT_EQ(convertor.maxImageSizeExceed(inputImg), true);
}

TEST(LoadInputImage, InvalidPngToDecode) {
    const fs::path inputImg = testExamplesPath / "invalid_image.png";
    EXPECT_THROW(convertor.loadRawSrcPng(inputImg), ConvertorException);
}

TEST(LoadInputImage, SuccessfullLoad) {
    const fs::path inputImg = testExamplesPath / "valid_image.png";
    EXPECT_NO_THROW(convertor.loadRawSrcPng(inputImg));
}
}  // namespace