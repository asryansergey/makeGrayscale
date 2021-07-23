#pragma once

#include <lodepng.h>

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using std::string;
using std::vector;

using namespace lodepng;

class PngConvertor {
   public:
    struct LUMINANCE_WEIGHTS {
        constexpr static float RED{0.2126};
        constexpr static float GREEN{0.7152};
        constexpr static float BLUE{0.0722};
    };
    PngConvertor(const string& srcPath, const string& destPath) : srcPngPath(srcPath), destPngPath(destPath) {
    }
    ~PngConvertor(){};
    unsigned loadRawSrcPng();
    void makeGrayscale();
    void saveGrayscalePng();

   private:
    vector<uint8_t> srcPng;
    vector<uint8_t> destGrayscalePng;
    string srcPngPath{};
    string destPngPath{};
    unsigned width{};
    unsigned height{};

    uint8_t getGrayscalePixel(const unsigned x, const unsigned y) const;
};