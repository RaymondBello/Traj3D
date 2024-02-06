cmake_minimum_required(VERSION 3.12)
project(TrajectorySim)
set(CMAKE_CXX_STANDARD 17)


# ==============
# Add ImGui
# ==============
# 1/  Option 1: if you added imgui_bundle in a subfolder, you can add it to your project with:
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui_bundle)
    add_subdirectory(external/imgui_bundle)
endif()

## 2/  Option 2: simply fetch imgui_bundle during the build
if (NOT TARGET imgui_bundle)
    message(STATUS "Fetching imgui_bundle...")
    include(FetchContent)
    Set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(imgui_bundle GIT_REPOSITORY https://github.com/pthom/imgui_bundle.git GIT_TAG main)
    FetchContent_MakeAvailable(imgui_bundle)

endif()


# Set Assimp build flags
option(ASSIMP_BUILD_ZLIB  "Build ZLIB support in Assimp" ON)
option(ASSIMP_BUILD_TESTS "Build test suite for Assimp"  OFF)

# Use the option value in your configuration
if(ASSIMP_BUILD_ZLIB)
    add_definitions(-DASSIMP_BUILD_ZLIB=ON)
else()
    add_definitions(-DASSIMP_BUILD_ZLIB=OFF)
endif()

if(ASSIMP_BUILD_TESTS)
    add_definitions(-DASSIMP_BUILD_TESTS=ON)
else()
    add_definitions(-DASSIMP_BUILD_TESTS=OFF)
endif()

# ==============
# Add Math & Utility Libraries
# ==============
add_subdirectory(lib/glm)
add_subdirectory(lib/entt)
add_subdirectory(lib/assimp)


# ==============
# Build your app
# ==============
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")
file(GLOB_RECURSE APP_HEADERS "include/*.h")

imgui_bundle_add_app(${PROJECT_NAME} ${APP_SOURCES})

include_directories(include/)

include_directories(lib/assimp/include)

# Link 3d Math library
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

# Link entt
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)

# Link assimp
target_link_libraries(${PROJECT_NAME} PRIVATE assimp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Now you can build your app with
#     mkdir build && cd build && cmake .. && cmake --build .

# Build with emscripten
#     emcmake cmake ..
#     make -j4
#     emrun --browser chrome TrajectorySim.html


