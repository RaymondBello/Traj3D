
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
