#include <gtest/gtest.h>

#include "../src/commandline.h"
#include "../src/exception.h"

const unsigned maxArgCount = 3;
namespace {
TEST(ValidateCmdLineArgs, MissingArguments) {
    const char* args[] = {"binary_name", "src_path"};
    EXPECT_THROW(CommandLine options(args, maxArgCount - 1), ConvertorException);
}

TEST(ValidateCmdLineArgs, TooManyArguments) {
    const char* args[] = {"binary_name", "src_path", "dest_path", "extra_argument"};
    EXPECT_THROW(CommandLine options(args, maxArgCount + 1), ConvertorException);
}

TEST(ValidateCmdLineArgs, CorrectArgumentList) {
    const char* args[] = {"binary_name", "src_path", "dest_path"};
    EXPECT_NO_THROW(CommandLine options(args, maxArgCount));
}

TEST(ValidateCmdLineArgs, ArgumentIndexOutOfRange) {
    const char* args[] = {"binary_name", "src_path", "dest_path"};
    CommandLine options(args, maxArgCount);
    EXPECT_THROW(options.getArgument(maxArgCount), std::out_of_range);
}
}  // namespace