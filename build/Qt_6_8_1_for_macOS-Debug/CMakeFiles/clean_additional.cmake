# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/drawingApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/drawingApp_autogen.dir/ParseCache.txt"
  "drawingApp_autogen"
  )
endif()
