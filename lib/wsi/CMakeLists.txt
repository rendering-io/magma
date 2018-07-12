###############################################################################
# lib/wsi/CMakeLists.txt
if("${CMAKE_SYSTEM}" MATCHES "Linux")
  list(APPEND WSI_SOURCES xcb.c++)
  list(APPEND WSI_MAIN_SOURCES linux_main.c++)
endif()

add_library(MagmaWSI ${WSI_SOURCES})
add_library(MagmaWSIMain ${WSI_MAIN_SOURCES})
install(TARGETS MagmaWSI MagmaWSIMain
	ARCHIVE DESTINATION lib)

if("${CMAKE_SYSTEM}" MATCHES "Linux")
  target_link_libraries(MagmaWSI PUBLIC xcb)
endif()

