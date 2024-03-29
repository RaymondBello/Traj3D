cmake_minimum_required(VERSION 3.12)
project(Traj3D)
set(CMAKE_CXX_STANDARD 17)



# Pthread flasg
option(COMPILE_WITH_PTHREAD " Compiles with PTHEAD" OFF)

if (COMPILE_WITH_PTHREAD)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Set Assimp build flags
option(ASSIMP_BUILD_ZLIB  "Build ZLIB support in Assimp" ON)
option(ASSIMP_BUILD_TESTS "Build test suite for Assimp"  OFF)

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
    FetchContent_Declare(imgui_bundle GIT_REPOSITORY https://github.com/RaymondBello/imgui_bundle.git GIT_TAG main)
    FetchContent_MakeAvailable(imgui_bundle)
endif()


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

file(GLOB_RECURSE UILAYER_SRC "include/UILayer/*.cpp")
file(GLOB_RECURSE RENDERER_SRC "include/Renderer/*.cpp")
file(GLOB_RECURSE OPENGL_API_SRC "include/OpenGL/*.cpp")
file(GLOB_RECURSE SCENE_SRC "include/Scene/*.cpp")


imgui_bundle_add_app(${PROJECT_NAME}    ${APP_SOURCES} 
                                        ${SCENE_SRC}
                                        ${UILAYER_SRC}
                                        ${RENDERER_SRC}
                                        ${OPENGL_API_SRC}
)

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
#     emrun --browser chrome Traj3D.html


