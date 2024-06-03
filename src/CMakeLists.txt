# Add current dir as src dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/instrumentation)

add_library(instrumentation instrumentation/instrumentation.cpp)

function(mktarget TARGET_NAME)
  add_executable(${TARGET_NAME} "${TARGET_NAME}.c")
  target_compile_options(${TARGET_NAME} PRIVATE -O0)
  set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "${TARGET_NAME}")
  target_link_libraries(${TARGET_NAME} PRIVATE instrumentation)
endfunction()

function(mktarget_opt TARGET_NAME)
  add_executable(${TARGET_NAME}_opt "${TARGET_NAME}.c")
  target_compile_options(${TARGET_NAME}_opt PRIVATE -O2 -fno-tree-coalesce-vars)
  set_target_properties(${TARGET_NAME}_opt PROPERTIES OUTPUT_NAME "${TARGET_NAME}_opt")
  target_link_libraries(${TARGET_NAME}_opt PRIVATE instrumentation)
endfunction()

# Define executables
mktarget(mystery0)
mktarget_opt(mystery0)
mktarget(mystery0_unroll)
mktarget(mystery0_unroll2)
mktarget(mystery0_unroll2_sums)
mktarget(mystery1)
mktarget_opt(mystery1)
