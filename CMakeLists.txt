cmake_minimum_required(VERSION 3.12)
project(TrajectorySim)
set(CMAKE_CXX_STANDARD 17)


# Add imgui_bundle
# =================
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

# Build your app
# ==============
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")
file(GLOB_RECURSE APP_HEADERS "include/*.h")




imgui_bundle_add_app(TrajectorySim ${APP_SOURCES} ${APP_HEADERS})

if (APPLE)
    target_link_libraries(TrajectorySim PRIVATE "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
endif()



# imgui_bundle_add_app is a helper function, similar to cmake's "add_executable"
# Usage:
# imgui_bundle_add_app(app_name file1.cpp file2.cpp ...)
#
# Features:
# * It will automatically link the target to the required libraries (hello_imgui, OpenGl, glad, etc)
# * It will embed the assets (for desktop, mobile, and emscripten apps)
# * It will perform additional customization (app icon and name on mobile platforms, etc)
#
# Now you can build your app with
#     mkdir build && cd build && cmake .. && cmake --build .