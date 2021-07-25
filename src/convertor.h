#pragma once

#include <lodepng.h>

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#include "exception.h"

using std::string;
using std::vector;

class PngConvertor {
   public:
    struct LUMINANCE_WEIGHTS {
        constexpr static float RED{0.2126};
        constexpr static float GREEN{0.7152};
        constexpr static float BLUE{0.0722};
    };

    void loadRawSrcPng(const string& srcPath);
    void makeGrayscale();
    void saveGrayscalePng(const string& destPngPath);
    void convert(const string&, const string&);
    bool maxImageSizeExceed(const string& path) const;

    PngConvertor() = default;
    ~PngConvertor() = default;

   private:
    vector<uint8_t> srcPng;
    vector<uint8_t> rawGrayscalePng;
    unsigned width{};
    unsigned height{};
    const unsigned long kMaxImageSize{6291456};  // 6MB in bytes
    uint8_t getGrayscalePixel(const unsigned x, const unsigned y) const;
};