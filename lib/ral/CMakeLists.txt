###############################################################################
# lib/ral/CMakeLists.txt
set(SOURCES device.c++
            instance.c++
            physical_device.c++
	    )
add_library(MagmaRAL ${SOURCES})
install(TARGETS MagmaRAL
	ARCHIVE DESTINATION lib)

