# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitclone-lastrun.txt" AND EXISTS "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitinfo.txt" AND
  "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --progress --config "advice.detachedHead=false" "https://github.com/sammycage/lunasvg" "lunasvg-src"
    WORKING_DIRECTORY "/Users/raybello/Github/TrajectorySim/build/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/sammycage/lunasvg'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "v2.3.9" --
  WORKING_DIRECTORY "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v2.3.9'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitinfo.txt" "/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/raybello/Github/TrajectorySim/build/_deps/lunasvg-subbuild/lunasvg-populate-prefix/src/lunasvg-populate-stamp/lunasvg-populate-gitclone-lastrun.txt'")
endif()
