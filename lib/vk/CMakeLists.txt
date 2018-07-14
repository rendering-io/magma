###############################################################################
# lib/vk/CMakeLists.txt
set(SOURCES error.c++
            instance.c++
            loader.c++)
add_library(MagmaVK ${SOURCES})
target_compile_definitions(MagmaVK
                           PUBLIC -DVK_NO_PROTOTYPES)
target_link_libraries(MagmaVK PUBLIC dl)
install(TARGETS MagmaVK
	ARCHIVE DESTINATION lib)

