###############################################################################
# lib/ral/CMakeLists.txt
set(SOURCES instance.c++
	    )
add_library(MagmaRAL ${SOURCES})
install(TARGETS MagmaRAL
	ARCHIVE DESTINATION lib)

