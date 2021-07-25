#include <vector>

#include "exception.h"
using std::vector;

class CommandLine {
   public:
    CommandLine(const char* const argv[], int argc) {
        if (argc < 3) {
            throw ConvertorException("Missing required command line arguments. [SRC_PATH and DEST_PATH]");
        }
        if (argc > 3) {
            throw ConvertorException("Too many arguments provided. Required args: [SRC_PATH and DEST_PATH]");
        }
        args.reserve(argc);
        for (auto i = 0; i < argc; ++i) {
            args.push_back(argv[i]);
        }
    }
    string getArgument(int index) const {
        return args.at(index);
    }

   private:
    vector<string> args;
};