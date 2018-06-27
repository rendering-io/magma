###############################################################################
# test/core/CMakeLists.txt
add_executable(core-tests thread_pool_tests.c++)
target_link_libraries(core-tests PRIVATE MagmaCore ${GMOCK_MAIN_LIBRARY})
add_test(NAME core COMMAND core-tests)

