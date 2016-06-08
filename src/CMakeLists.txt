find_package(Boost REQUIRED COMPONENTS filesystem system)
find_package(ICU REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(log4cpp REQUIRED)

if(HAVE_DMCTK)
    find_package(DCMTK REQUIRED)
endif()

file(GLOB_RECURSE Header_Files "*.h")
file(GLOB_RECURSE Source_Files "*.cpp")
file(GLOB_RECURSE templates "*.txx")

list(APPEND Header_Files ${templates})

# Remove the DCMTK files
if(NOT HAVE_DCMTK)
    file(GLOB_RECURSE dcmtk_files "odil/dcmtk/*.*")
    foreach(dcmtk_file ${dcmtk_files})
        list(REMOVE_ITEM Header_Files ${dcmtk_file})
        list(REMOVE_ITEM Source_Files ${dcmtk_file})
    endforeach(dcmtk_file)
endif()

# Regroup files by folder
GroupFiles(Header_Files)
GroupFiles(Source_Files)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${ICU_INCLUDE_DIRS})

add_definitions(
    -D BOOST_ASIO_SEPARATE_COMPILATION
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
)
link_directories(${Boost_LIBRARY_DIRS})

add_library(libodil ${Source_Files} ${Header_Files})
set_target_properties(libodil PROPERTIES OUTPUT_NAME odil)

target_link_libraries(libodil PRIVATE
    ${Boost_LIBRARIES}
    ${ICU_LIBRARIES}
    jsoncpp_lib_static
    log4cpp)

if(HAVE_DCMTK)
    include_directories(${DCMTK_INCLUDE_DIRS})
    add_definitions(${DCMTK_DEFINITIONS})
    target_link_libraries(libodil PRIVATE dcmdata ofstd oflog)
endif()

if(WIN32)
    add_definitions(-D BUILDING_ODIL 
                    -D BOOST_ALL_NO_LIB)
    target_link_libraries(libodil PRIVATE netapi32)
endif()

set_target_properties(libodil PROPERTIES
    VERSION ${odil_VERSION}
    SOVERSION ${odil_MAJOR_VERSION})

target_include_directories(libodil INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>)

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
endif ()
