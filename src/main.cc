#include <filesystem>

#include "convertor.h"

bool fileExists(const std::filesystem::path& path) {
    if (std::filesystem::exists(path)) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("[-] %s\n", "Missing command line arguments. [src_png_path and dest_png_path]");
        return 1;
    }

    string srcImagePath{argv[1]};
    if (!fileExists(srcImagePath)) {
        printf("[-] %s: \"%s\"\n", "Invalid path for source image to convert", srcImagePath.c_str());
        return 1;
    }
    string destImagePath{argv[2]};

    PngConvertor convertor(srcImagePath, destImagePath);
    if (0 != convertor.loadRawSrcPng()) {
        return 1;
    }

    convertor.makeGrayscale();

    convertor.saveGrayscalePng();
    return 0;
}