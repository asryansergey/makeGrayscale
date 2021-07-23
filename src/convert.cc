#include <lodepng.h>

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using std::string;
using std::vector;
using namespace lodepng;

struct LUMINANCE_WEIGHTS {
    constexpr static float RED{0.2126};
    constexpr static float GREEN{0.7152};
    constexpr static float BLUE{0.0722};
};

uint8_t
getGrayscalePixel(const vector<uint8_t>& imageInfo, unsigned x, unsigned y, unsigned rowLength) {
    unsigned startIdx = 4 * rowLength * y + 4 * x;
    const float componentRed{LUMINANCE_WEIGHTS::RED * imageInfo[startIdx]};
    const float componentGreen{LUMINANCE_WEIGHTS::GREEN * imageInfo[startIdx + 1]};
    const float componentBlue{LUMINANCE_WEIGHTS::BLUE * imageInfo[startIdx + 2]};

    return componentRed + componentGreen + componentBlue;
}

void convertToGrayScale(vector<uint8_t>& rawOut, const vector<uint8_t>& rawIn, unsigned width, unsigned height) {
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            rawOut[width * y + x] = getGrayscalePixel(rawIn, x, y, width);
        }
    }
}

void saveImage(const vector<uint8_t>& rawGrayscalePNG, unsigned width, unsigned height, const string& outputFile) {
    vector<uint8_t> grayscalePNG{};
    encode(grayscalePNG, rawGrayscalePNG, width, height, LodePNGColorType::LCT_GREY, 8);
    save_file(grayscalePNG, outputFile);
}

int main() {
    vector<uint8_t> basePNG{};
    if (0 != load_file(basePNG, "cornell_box.png")) {
        printf("%s\n", "[-] Error while loading .png file.");
        return 1;
    }

    vector<uint8_t> rawPNG{};
    unsigned width{}, height{};
    if (0 != decode(rawPNG, width, height, basePNG)) {
        printf("%s\n", "[-] Error while decoding .png file.");
        return 1;
    }

    vector<uint8_t> rawGrayscalePNG(width * height);
    convertToGrayScale(rawGrayscalePNG, rawPNG, width, height);

    saveImage(rawGrayscalePNG, width, height, "sample_output.png");
    return 0;
}