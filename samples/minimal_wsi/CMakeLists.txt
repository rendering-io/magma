###############################################################################
# samples/minimal_wsi/CMakeLists.txt
if(WIN32)
  set(EXECUTABLE_TYPE WIN32)
endif()

add_executable(MagmaMinimalWSI ${EXECUTABLE_TYPE} minimal_wsi.c++)
target_link_libraries(MagmaMinimalWSI PRIVATE MagmaWSI MagmaWSIMain)
