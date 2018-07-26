###############################################################################
# test/ral/CMakeLists.txt
add_executable(TestMagmaRAL instance_tests.c++)
target_link_libraries(TestMagmaRAL PRIVATE MagmaRAL MagmaVK ${GMOCK_MAIN_LIBRARY})
add_test(NAME RAL COMMAND TestMagmaRAL)

