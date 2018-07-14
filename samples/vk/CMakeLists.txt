###############################################################################
# samples/vk/CMakeLists.txt
add_executable(MagmaVKCreateInstance create_instance.c++)
target_link_libraries(MagmaVKCreateInstance
                      PRIVATE MagmaVK MagmaWSI MagmaWSIMain)

