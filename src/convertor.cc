#include "convertor.h"

unsigned PngConvertor::loadRawSrcPng() {
    vector<uint8_t> basePng{};
    if (0 != load_file(basePng, srcPngPath)) {
        printf("[-] %s: \"%s\"\n", "Error while loading .png file.", srcPngPath.c_str());
        return 1;
    }
    if (0 != decode(srcPng, width, height, basePng)) {
        printf("[-] %s: \"%s\"\n", "Error while decoding .png file.", srcPngPath.c_str());
        return 2;
    }
    destGrayscalePng.clear();
    destGrayscalePng.resize(width * height);
    return 0;
}

uint8_t PngConvertor::getGrayscalePixel(const unsigned x, const unsigned y) const {
    unsigned startIdx = 4 * width * y + 4 * x;
    const float componentRed{LUMINANCE_WEIGHTS::RED * srcPng[startIdx]};
    const float componentGreen{LUMINANCE_WEIGHTS::GREEN * srcPng[startIdx + 1]};
    const float componentBlue{LUMINANCE_WEIGHTS::BLUE * srcPng[startIdx + 2]};
    return componentRed + componentGreen + componentBlue;
}

void PngConvertor::makeGrayscale() {
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            destGrayscalePng[width * y + x] = getGrayscalePixel(x, y);
        }
    }
}

void PngConvertor::saveGrayscalePng() {
    vector<uint8_t> grayscalePng{};
    encode(grayscalePng, destGrayscalePng, width, height, LodePNGColorType::LCT_GREY, 8);
    save_file(grayscalePng, destPngPath);
    printf("[!] Done. Path to image: \"%s\"\n", destPngPath.c_str());
}
