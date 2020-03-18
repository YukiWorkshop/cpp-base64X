cmake_minimum_required(VERSION 3.2)
project(cpp-base64X)

set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/base64_default_config.h ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/base64/lib/config.h COPYONLY)

set(SOURCE_FILES_BASE64
        3rdParty/base64/lib/arch/avx2/codec.c 3rdParty/base64/lib/arch/generic/codec.c
        3rdParty/base64/lib/arch/neon32/codec.c 3rdParty/base64/lib/arch/neon64/codec.c
        3rdParty/base64/lib/arch/ssse3/codec.c 3rdParty/base64/lib/arch/sse41/codec.c
        3rdParty/base64/lib/arch/sse42/codec.c 3rdParty/base64/lib/arch/avx/codec.c
        3rdParty/base64/lib/tables/tables.c
        3rdParty/base64/lib/lib.c 3rdParty/base64/lib/codec_choose.c)
add_library(cpp-base64X ${SOURCE_FILES_BASE64})
SET_TARGET_PROPERTIES(cpp-base64X PROPERTIES COMPILE_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

add_executable(cpp-base64X-Test test.cpp)
target_link_libraries(cpp-base64X-Test cpp-base64X)