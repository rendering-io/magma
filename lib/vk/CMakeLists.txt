###############################################################################
# lib/vk/CMakeLists.txt
set(SOURCES loader.c++)
add_library(MagmaVK ${SOURCES})
install(TARGETS MagmaVK
	ARCHIVE DESTINATION lib)

