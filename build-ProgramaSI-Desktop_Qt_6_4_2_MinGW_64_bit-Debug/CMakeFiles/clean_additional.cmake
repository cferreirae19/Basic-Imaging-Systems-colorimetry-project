# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ProgramaSI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ProgramaSI_autogen.dir\\ParseCache.txt"
  "ProgramaSI_autogen"
  )
endif()
