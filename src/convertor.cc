#include "convertor.h"

void PngConvertor::loadRawSrcPng(const string& srcPath) {
    if (!std::filesystem::exists(srcPath)) {
        const string message = string("Source image doesn't exists: ") + srcPath;
        throw ConvertorException(message);
    }
    if (maxImageSizeExceed(srcPath)) {
        string message = string("Image size exceeded max accepted size: ");
        message += std::to_string(kMaxImageSize);
        throw ConvertorException(message);
    }
    vector<uint8_t> basePng{};
    if (0 != lodepng::load_file(basePng, srcPath)) {
        const string message = string("Error while loading .png file: ") + srcPath;
        throw ConvertorException(message);
    }
    if (0 != lodepng::decode(srcPng, width, height, basePng)) {
        const string message = string("Error while decoding .png file: ") + srcPath;
        throw ConvertorException(message);
    }
    rawGrayscalePng.clear();
    rawGrayscalePng.resize(width * height);
}

uint8_t PngConvertor::getGrayscalePixel(const unsigned x, const unsigned y) const {
    unsigned startIdx = 4 * width * y + 4 * x;
    assert(srcPng.size() > startIdx + 2);
    const float componentRed{LUMINANCE_WEIGHTS::RED * srcPng[startIdx]};
    const float componentGreen{LUMINANCE_WEIGHTS::GREEN * srcPng[startIdx + 1]};
    const float componentBlue{LUMINANCE_WEIGHTS::BLUE * srcPng[startIdx + 2]};
    return componentRed + componentGreen + componentBlue;
}

// TODO(asryansergey): Make pixel value computation parallel.
void PngConvertor::makeGrayscale() {
    assert(rawGrayscalePng.size() == width * height);
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            rawGrayscalePng[width * y + x] = getGrayscalePixel(x, y);
        }
    }
}

void PngConvertor::saveGrayscalePng(const string& destPngPath) {
    assert(rawGrayscalePng.size() == width * height);
    vector<uint8_t> grayscalePng{};
    if (0 != lodepng::encode(grayscalePng, rawGrayscalePng, width, height, LodePNGColorType::LCT_GREY, 8)) {
        throw ConvertorException("Error while encoding grayscale image");
    }
    lodepng::save_file(grayscalePng, destPngPath);
    printf("[!] Done. Path to grayscale image: \"%s\"\n", destPngPath.c_str());
}

void PngConvertor::convert(const string& srcImgPath, const string& destImgPath) {
    loadRawSrcPng(srcImgPath);
    makeGrayscale();
    saveGrayscalePng(destImgPath);
}

bool PngConvertor::maxImageSizeExceed(const string& path) const {
    return std::filesystem::file_size(path) > kMaxImageSize;
}