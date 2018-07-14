###############################################################################
# test/vk/CMakeLists.txt
add_executable(TestMagmaVK instance_tests.c++)
target_link_libraries(TestMagmaVK PRIVATE MagmaVK ${GMOCK_MAIN_LIBRARY})
add_test(NAME VK COMMAND TestMagmaVK)

