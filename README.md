
# TrajectorySim


## Build for Linux and macOS

### 1. Create the build directory, run cmake and make

```bash
mkdir -p build && cd build
cmake ..
make -j 4
```

## Build for Windows

### 1. Optional: clone imgui_bundle
Follow step 1 from the Linux/macOS section above.

### 2. Create the build directory, run cmake

```bash
mkdir build && cd build
cmake ..
```

### 3. Open the Visual Studio solution
It should be located in `build/imgui_bundle_example_integration.sln`

## Build for emscripten

### Install emscripten
You can either install emsdk following [the instruction on the emscripten website](https://emscripten.org/docs/getting_started/downloads.html).

### Compile with emscripten

```bash
# Add emscripten tools to your path
# (assuming you installed emscripten in ~/emsdk)
source ~/emsdk/emsdk_env.sh

# cmake and build
mkdir build_emscripten
cd build_emscripten
emcmake cmake ..
make -j 4

# launch a webserver
python3 -m http.server
```

Open a browser, and navigate to [http://localhost:8000](http://localhost:8000).

## Build for Android

Add this line at the top of your CMakeLists.txt

```cmake
add_subdirectory(external/imgui_bundle)
```

### 2. Create the Android Studio project

```bash
# Set the ANDROID_HOME and ANDROID_NDK_HOME environment variables
# For example:
export ANDROID_HOME=/Users/YourName/Library/Android/sdk
export ANDROID_NDK_HOME=/Users/YourName/Library/Android/sdk/ndk/26.1.10909125

mkdir build_android && cd build_android
../external/imgui_bundle/external/hello_imgui/hello_imgui/tools/android/cmake_arm-android.sh ..
```

### 3. Open the project in Android Studio
It should be located in `build_android/imgui_bundle_example_integration_AndroidStudio`

## Build for iOS

### 2. Create the Xcode project

```bash
mkdir build_ios && cd build_ios
```

Run CMake with the following command, where you replace `XXXXXXXXX` with your Apple Developer Team ID,
and `com.your_website` with your website (e.g. `com.mycompany`).

```bash
cmake .. \
-GXcode \
-DCMAKE_TOOLCHAIN_FILE=../external/imgui_bundle/external/hello_imgui/hello_imgui/hello_imgui_cmake/ios-cmake/ios.toolchain.cmake \
-DPLATFORM=OS64COMBINED \
-DCMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM=XXXXXXXXX \
-DHELLO_IMGUI_BUNDLE_IDENTIFIER_URL_PART=com.your_website \
-DHELLOIMGUI_USE_SDL_OPENGL3=ON
```

Then, open the XCode project in `build_ios/imgui_bundle_example_integration.xcodeproj`