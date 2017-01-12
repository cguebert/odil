find_package(Boost REQUIRED COMPONENTS filesystem system date_time)

if(WITH_DMCTK)
    find_package(DCMTK REQUIRED)
endif()

if(WITH_JSON)
    find_package(ICU REQUIRED)
    find_package(jsoncpp REQUIRED)
endif()

if(WITH_LOGGING)
    find_package(log4cpp REQUIRED)
endif()

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")
file(GLOB_RECURSE templates "*.txx")
list(SORT Header_Files)
list(SORT Source_Files)
list(SORT templates)

list(APPEND Header_Files ${templates})

if(NOT WITH_DCMTK)
    set(pattern "${CMAKE_CURRENT_SOURCE_DIR}/odil/dcmtk/[^;]+[;$]")
    string(REGEX REPLACE ${pattern} "" Header_Files "${Header_Files}")
    string(REGEX REPLACE ${pattern} "" Source_Files "${Source_Files}")
endif()

if(NOT WITH_JSON)
    set(pattern "${CMAKE_CURRENT_SOURCE_DIR}/odil/(json_converter|unicode)[^;]+[;$]")
    string(REGEX REPLACE ${pattern} "" Header_Files "${Header_Files}")
    string(REGEX REPLACE ${pattern} "" Source_Files "${Source_Files}")
endif()

# Regroup files by folder
GroupFiles(Header_Files)
GroupFiles(Source_Files)

add_library(libodil ${Source_Files} ${Header_Files})
set_target_properties(libodil PROPERTIES OUTPUT_NAME odil)

target_include_directories(libodil 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_compile_definitions(libodil
    PUBLIC
    BOOST_ASIO_SEPARATE_COMPILATION
    PRIVATE
	BOOST_ASIO_DYN_LINK
    ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
)

target_link_libraries(libodil PRIVATE
    Boost::filesystem
    Boost::date_time)

if(WITH_JSON)
    target_include_directories(libodil PRIVATE ${ICU_INCLUDE_DIRS})
    target_link_libraries(libodil PRIVATE
        ${ICU_LIBRARIES}
        jsoncpp_lib_static)
endif()

if(WITH_LOGGING)
    target_compile_definitions(libodil PRIVATE WITH_LOGGING)
    target_link_libraries(libodil PRIVATE log4cpp)
endif()

if(HAVE_DCMTK)
    target_include_directories(libodil PUBLIC ${DCMTK_INCLUDE_DIRS})
    add_definitions(${DCMTK_DEFINITIONS})
    target_link_libraries(libodil PRIVATE dcmdata ofstd oflog)
endif()

if(WIN32)
    target_compile_definitions(libodil
    PRIVATE
        BUILDING_ODIL
        BOOST_ALL_NO_LIB)
    target_link_libraries(libodil PRIVATE netapi32)
endif()

set_target_properties(libodil PROPERTIES
    VERSION ${odil_VERSION}
    SOVERSION ${odil_MAJOR_VERSION})

set(DEFAULT_COMPILE_OPTIONS)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(DEFAULT_COMPILE_OPTIONS ${DEFAULT_COMPILE_OPTIONS}
        /MP     # -> build with multiple processes
        /wd4251 # -> disable warning: 'identifier': class 'type' needs to have dll-interface to be used by clients of class 'type2'
        /wd4275 # -> disable warning: non - DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
    )

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

target_compile_options(libodil PRIVATE ${DEFAULT_COMPILE_OPTIONS})

if (BUILD_INSTALL)
    set(odil_cmake_dir lib/cmake/odil)
    set(version_config ${PROJECT_BINARY_DIR}/odil-config-version.cmake)
    set(project_config ${PROJECT_BINARY_DIR}/odil-config.cmake)
    set(targets_export_name odil-targets)

    install(
        DIRECTORY odil/ DESTINATION include/odil
        FILES_MATCHING PATTERN "*.h" PATTERN "*.txx")
    install(
        TARGETS libodil
        EXPORT ${targets_export_name}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
    
    # Generate the version, config and target files into the build directory.
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${version_config}
        VERSION ${odil_VERSION}
        COMPATIBILITY AnyNewerVersion)
    configure_package_config_file(
        ${PROJECT_SOURCE_DIR}/cmake/odil-config.cmake.in 
        ${project_config}
        INSTALL_DESTINATION ${odil_cmake_dir})
    export(
        TARGETS libodil 
        FILE "${PROJECT_BINARY_DIR}/${targets_export_name}.cmake")

    # Install version, config and target files.
    install(
        FILES ${project_config} ${version_config}
        DESTINATION ${odil_cmake_dir})
    install(EXPORT ${targets_export_name} DESTINATION ${odil_cmake_dir})
    
    if (BUILD_TESTING AND WIN32) # Need to copy the necessary dlls to the test folder
        install(TARGETS libodil RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/tests/Release CONFIGURATIONS Release)
        install(TARGETS libodil RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/tests/Debug CONFIGURATIONS Debug)
    endif()
endif ()
