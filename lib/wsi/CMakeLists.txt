###############################################################################
# lib/wsi/CMakeLists.txt

if("${CMAKE_SYSTEM}" MATCHES "Linux")
  list(APPEND SOURCES linux_main.c++)
endif()

add_library(MagmaWSIMain ${SOURCES}) 
install(TARGETS MagmaWSIMain
	ARCHIVE DESTINATION lib)

