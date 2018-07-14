###############################################################################
# test/core/CMakeLists.txt
set(SOURCES iterator_tests.c++
            thread_pool_tests.c++)
add_executable(TestMagmaCore ${SOURCES})
target_link_libraries(TestMagmaCore PRIVATE MagmaCore ${GMOCK_MAIN_LIBRARY})
add_test(NAME Core COMMAND TestMagmaCore)

