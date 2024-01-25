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


imgui_bundle_add_app(${PROJECT_NAME} ${APP_SOURCES})

include_directories(include/)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux, do nothing!")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
    find_package(OpenGL REQUIRED)
    # find_package(glfw3 3.2 REQUIRED)
    # target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Now you can build your app with
#     mkdir build && cd build && cmake .. && cmake --build .