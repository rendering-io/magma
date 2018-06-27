###############################################################################
# lib/core/CMakeLists.txt
add_library(MagmaCore thread_pool.c++)
install(TARGETS MagmaCore
	ARCHIVE DESTINATION lib)

