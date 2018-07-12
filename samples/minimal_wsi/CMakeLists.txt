###############################################################################
# samples/minimal_wsi/CMakeLists.txt
add_executable(MagmaMinimalWSI minimal_wsi.c++)
target_link_libraries(MagmaMinimalWSI PRIVATE MagmaWSI MagmaWSIMain)

