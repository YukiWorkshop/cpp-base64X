# cpp-base64X
[![pipeline status](https://gitlab.com/ReimuNotMoe/cpp-base64X/badges/master/pipeline.svg)](https://gitlab.com/ReimuNotMoe/cpp-base64X/commits/master)
[![coverage report](https://gitlab.com/ReimuNotMoe/cpp-base64X/badges/master/coverage.svg)](https://gitlab.com/ReimuNotMoe/cpp-base64X/commits/master)

Probably the most convenient & powerful C++ base64 library.

## Features
- Elegant & intuitive API
- Converts from/to different types
- Streamed operation
- Hardware accelerated

## Requirements
Reasonably new versions of:
-  C++17 compatible compiler
-  CMake

## Install
Use of the [CPM](https://github.com/TheLartians/CPM.cmake) package manager is recommended:

```cmake
include(cmake/CPM.cmake)

CPMAddPackage(
        NAME cpp-base64X
        GITHUB_REPOSITORY YukiWorkshop/cpp-base64X
        VERSION 0.0.1
)

target_include_directories(your_project PUBLIC ${cpp-base64X_SOURCE_DIR})
target_link_libraries(your_project cpp-base64X)
```

Or manually clone & add:
```shell script
mkdir cpp_modules && cd cpp_modules
git clone --recursive https://github.com/YukiWorkshop/cpp-base64X
```

```cmake
add_subdirectory(cpp_modules/cpp-base64X)
target_include_directories(your_project PUBLIC cpp_modules/cpp-base64X)
target_link_libraries(your_project cpp-base64X)
```

## Usage
```cpp
#include <cpp-base64X.hpp>

using namespace YukiWorkshop;
```

One-time conversion:
```cpp
std::string s = Base64X::encode("Hello");
std::string s2 = Base64X::decode(s);
```

You can use different input/output types. But the return type is limited to `std::string` and `std::vector<uint8_t>`.

Note that you can only decode vectors which element size is 1 (`uint8_t`, `char`, etc).

From vectors instead of strings:
```cpp
std::vector<uint8_t> v = {0xaa, 0x55, 0x01, 0x02, 0x03};
std::vector<uint8_t> s = Base64X::encode(v);
std::string v2 = Base64X::decode(s);
```

And even vectors with doubles inside:
```cpp
std::vector<double> v = {3.14159265357, 42.42, 233.233, 666.666};
std::vector<uint8_t> s = Base64X::encode(v);
std::vector<uint8_t> v2 = Base64X::decode(s);
for (size_t i=0; i<4; i++) {
    std::cout << ((double *)v2.data())[i] << " ";
}
```

Stream operators:
```cpp
std::string out;
Base64X::Encoder<std::string> e;
e >> out; // Set output target
e << "Hey guys, "
  << "this is Austin!"
  << nullptr; // Use nullptr for EOF
```

The classic equivalent of above: 
```cpp
std::string out;
Base64X::Encoder<std::string> e;
out += e.encode("Hey guys, ");
out += e.encode("this is Austin!");
out += e.finalize();
```

## License
MIT

## Acknowledgements
This library makes use of [aklomp/base64](https://github.com/aklomp/base64), which is a great C base64 library.