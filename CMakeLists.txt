cmake_minimum_required(VERSION 3.12)
project(TrajectorySim)
set(CMAKE_CXX_STANDARD 17)


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


imgui_bundle_add_app(TrajectorySim ${APP_SOURCES})

include_directories(include/)

if (APPLE)
endif()

if (UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(TrajectorySim PRIVATE ${OPENGL_LIBRARY})
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(TrajectorySim PRIVATE "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux, do nothing!")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(OpenGL REQUIRED)
    message("include dir: ${OPENGL_INCLUDE_DIR}")
    message("link libraries(new): ${OPENGL_gl_LIBRARY}")
    message("link libraries(old): ${OPENGL_LIBRARY}")
    target_link_libraries(TrajectorySim ${OPENGL_LIBRARY})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Now you can build your app with
#     mkdir build && cd build && cmake .. && cmake --build .