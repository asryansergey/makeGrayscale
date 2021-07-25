#include <gtest/gtest.h>

#include <algorithm>

#include "../src/convertor.h"
#include "../src/exception.h"
namespace fs = std::filesystem;

namespace {
const fs::path testExamplesPath = std::filesystem::current_path() / "examples";
PngConvertor convertor;

TEST(ConvertPng, SuccessfullConversion) {
    try {
        const fs::path inputImg = testExamplesPath / "valid_image.png";
        const string outImgPath = testExamplesPath / "grayscale_image.png";
        convertor.convert(inputImg, outImgPath);

        const fs::path expectedGrayscale = testExamplesPath / "valid_grayscale.png";
        vector<uint8_t> convertedData{}, expectedData{};
        lodepng::load_file(convertedData, outImgPath);
        lodepng::load_file(expectedData, expectedGrayscale);

        EXPECT_EQ(convertedData.size(), expectedData.size());
        EXPECT_EQ(std::equal(convertedData.begin(), convertedData.end(),
                             expectedData.begin(), expectedData.end()),
                  true);
    } catch (const ConvertorException& e) {
        FAIL() << "Fail to load And decode image.";
    }
}
}  // namespace