###############################################################################
# lib/vk/CMakeLists.txt
set(SOURCES error.c++
            instance.c++
            loader.c++
            physical_device.c++
            )
add_library(MagmaVK ${SOURCES})
target_link_libraries(MagmaVK PUBLIC MagmaRAL vulkan dl)
install(TARGETS MagmaVK
	ARCHIVE DESTINATION lib)

