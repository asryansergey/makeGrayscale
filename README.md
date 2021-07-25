# Make grayscale PNG

## Build project
```bash
mkdir build && cd build
cmake ..
make # -j N
```

## Build with tests
```bash
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
make # -j N
```


## Run
Build process will create binary in `/bin` directory inside `root` directory.
You can run target binary with following command:
```bash
./bin/gspng PATH_FOR_IMAGE_TO_CONVERT DESTINATION_PATH
```
## Run tests
```bash
make test
```

## Dependencies
- Clone [lodepng](https://github.com/lvandeve/lodepng.git) repository into `/libs` directory.
This is the lightweight library_(instead of opencv, libpng, etc.)_ to _read/write/decode/encode_ PNG images.
- [Google test](https://github.com/google/googletest). _Version specified in `tests/CMakeLists.txt` will be downloaded._