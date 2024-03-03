cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ipprint VERSION ${PROJECT_VESRION})

add_executable(ipprint_cli main.cpp)

set_target_properties(ipprint_cli PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ipprint_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(ipprint_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(ipprint_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ipprint_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)