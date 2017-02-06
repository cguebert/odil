find_package(Boost COMPONENTS unit_test_framework filesystem date_time REQUIRED)
find_package(DCMTK REQUIRED)
find_package(jsoncpp REQUIRED)

add_subdirectory(tools)

file(GLOB headers *.h)
file(GLOB_RECURSE tests code/*.cpp)
if(NOT WITH_DCMTK)
    list(
        REMOVE_ITEM tests
        ${CMAKE_CURRENT_SOURCE_DIR}/code/conversion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code/DcmtkException.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code/ElementAccessor.cpp)
    set(
        extra_files
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/conversion.cpp
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/ElementAccessor.cpp
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/ElementTraits.cpp
        ${CMAKE_SOURCE_DIR}/src/odil/dcmtk/Exception.cpp)
endif()

if(NOT WITH_WITH_JSON)
    list(
        REMOVE_ITEM tests
        ${CMAKE_CURRENT_SOURCE_DIR}/code/json_converter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/code/unicode.cpp)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS})

add_definitions(
    ${DCMTK_DEFINITIONS}
    -D ODIL_MAJOR_VERSION=${odil_MAJOR_VERSION}
)
link_directories(${Boost_LIBRARY_DIRS})


foreach(test_file ${tests})
    get_filename_component(test ${test_file} NAME_WE)

    add_executable(test_${test} ${test_file} ${headers} ${extra_files})
    target_link_libraries(test_${test} libodil ${Boost_LIBRARIES} jsoncpp_lib_static dcmdata ofstd oflog)
    set_target_properties(test_${test} PROPERTIES OUTPUT_NAME ${test} FOLDER "Tests")

    file(READ ${test_file} content)

    set(pattern "BOOST_(AUTO|FIXTURE)_TEST_CASE\\(([^),]+)")

    string(REGEX MATCHALL ${pattern} cases ${content})

    foreach(case ${cases})
        string(REGEX REPLACE ${pattern} "\\2" case ${case})
        if(NOT ${case} MATCHES "##")
            add_test("${test}_${case}" "${test}" "--run_test=${case}")
        endif()
    endforeach()

    set(pattern "ElementTest\\([\n ]+([A-Z]+)")

    string(REGEX MATCHALL ${pattern} matches ${content})

    foreach(match ${matches})
        string(REGEX REPLACE ${pattern} "\\1" vr ${match})

        set(case "${vr}FromOdil")
        add_test("${test}_${case}" "${test}" "--run_test=${case}")

        set(case "${vr}ToOdil")
        add_test("${test}_${case}" "${test}" "--run_test=${case}")
    endforeach()

    if(BUILD_SHARED_LIBS)
        target_compile_definitions(test_${test} PRIVATE BOOST_ALL_NO_LIB)
    endif()

endforeach()

# Copy the necessary dlls in the tests folder
if(WIN32)
	foreach(export_lib Boost::filesystem Boost::system Boost::date_time Boost::unit_test_framework)
		InstallDependency(${export_lib} ${CMAKE_BINARY_DIR}/tests)
	endforeach()
endif()

file(GLOB_RECURSE python_tests *.py)

add_custom_target(Runner ${CMAKE_COMMAND} -E echo "Test runner" SOURCES run)
add_custom_target(
    PythonTests ${CMAKE_COMMAND} -E echo "Python tests" SOURCES ${python_tests})
