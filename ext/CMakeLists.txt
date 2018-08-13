###############################################################################
# ext/CMakeLists.txt

# Optionally build googlemock.
if(${BUILD_TESTS})
  find_package(Threads REQUIRED)

  # Visual Studio chooses to build projects in build type subdirectories.
  message("gen ${CMAKE_GENERATOR}")
  if(${CMAKE_GENERATOR} STREQUAL "Visual Studio 15 2017")
    set(BUILD_SUB_DIR "${CMAKE_BUILD_TYPE}/")
	message("type ${CMAKE_BUILD_TYPE}")
  endif()
  
  set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
  set(GTEST_CRT_SUFFIX "")

  ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    UPDATE_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
	CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE};-Dgtest_force_shared_crt:BOOL=ON")

  ExternalProject_Get_Property(googletest source_dir)
  set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include)
  set(GMOCK_INCLUDE_DIRS ${source_dir}/googlemock/include)
  file(MAKE_DIRECTORY ${GTEST_INCLUDE_DIRS})
  file(MAKE_DIRECTORY ${GMOCK_INCLUDE_DIRS})

  ExternalProject_Get_Property(googletest binary_dir)
  set(GTEST_LIBRARY_PATH
      ${binary_dir}/googlemock/gtest/${BUILD_SUB_DIR}${CMAKE_FIND_LIBRARY_PREFIXES}gtest${GTEST_CRT_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GTEST_LIBRARY gtest)
  add_library(${GTEST_LIBRARY} STATIC IMPORTED GLOBAL)
  set_target_properties(${GTEST_LIBRARY} PROPERTIES
    IMPORTED_LOCATION ${GTEST_LIBRARY_PATH}
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
    INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
  add_dependencies(${GTEST_LIBRARY} googletest)

  set(GTEST_MAIN_LIBRARY_PATH
      ${binary_dir}/googlemock/gtest/${BUILD_SUB_DIR}${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${GTEST_CRT_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GTEST_MAIN_LIBRARY gtest_main)
  add_library(${GTEST_MAIN_LIBRARY} STATIC IMPORTED GLOBAL)
  set_target_properties(${GTEST_MAIN_LIBRARY} PROPERTIES
    IMPORTED_LOCATION ${GTEST_MAIN_LIBRARY_PATH}
    IMPORTED_LINK_INTERFACE_LIBRARIES
      "${CMAKE_THREAD_LIBS_INIT};${GTEST_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS})
  add_dependencies(${GTEST_MAIN_LIBRARY} googletest)

  set(GMOCK_LIBRARY_PATH
      ${binary_dir}/googlemock/${BUILD_SUB_DIR}${CMAKE_FIND_LIBRARY_PREFIXES}gmock${GTEST_CRT_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GMOCK_LIBRARY gmock)
  add_library(${GMOCK_LIBRARY} STATIC IMPORTED GLOBAL)
  set_target_properties(${GMOCK_LIBRARY} PROPERTIES
    IMPORTED_LOCATION ${GMOCK_LIBRARY_PATH}
    IMPORTED_LINK_INTERFACE_LIBRARIES
      "${CMAKE_THREAD_LIBS_INIT};${GTEST_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES ${GMOCK_INCLUDE_DIRS})
  add_dependencies(${GMOCK_LIBRARY} googletest)

  set(GMOCK_MAIN_LIBRARY_PATH
      ${binary_dir}/googlemock/${BUILD_SUB_DIR}${CMAKE_FIND_LIBRARY_PREFIXES}gmock_main${GTEST_CRT_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GMOCK_MAIN_LIBRARY gmock_main)
  add_library(${GMOCK_MAIN_LIBRARY} STATIC IMPORTED GLOBAL)
  set_target_properties(${GMOCK_MAIN_LIBRARY} PROPERTIES
    IMPORTED_LOCATION ${GMOCK_MAIN_LIBRARY_PATH}
    IMPORTED_LINK_INTERFACE_LIBRARIES
      "${CMAKE_THREAD_LIBS_INIT};${GMOCK_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES ${GMOCK_INCLUDE_DIRS})
  add_dependencies(${GMOCK_MAIN_LIBRARY} ${GMOCK_LIBRARY})

  set(GTEST_LIBRARY ${GTEST_LIBRARY} PARENT_SCOPE)
  set(GTEST_MAIN_LIBRARY ${GTEST_MAIN_LIBRARY} PARENT_SCOPE)
  set(GMOCK_LIBRARY ${GMOCK_LIBRARY} PARENT_SCOPE)
  set(GMOCK_MAIN_LIBRARY ${GMOCK_MAIN_LIBRARY} PARENT_SCOPE)
endif()
