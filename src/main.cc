#include "commandline.h"
#include "convertor.h"

int main(int argc, char* argv[]) {
    CommandLine options(argv, argc);

    PngConvertor convertor;
    try {
        convertor.loadRawSrcPng(options.getArgument(1));
        convertor.makeGrayscale();
        convertor.saveGrayscalePng(options.getArgument(2));
    } catch (const std::exception& e) {
        printf("[-] %s\n", e.what());
        return 1;
    }
    return 0;
}