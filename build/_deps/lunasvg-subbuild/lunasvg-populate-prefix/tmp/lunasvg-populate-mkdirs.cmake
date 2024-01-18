# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-src"
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-build"
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix"
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/tmp"
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp"
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src"
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
