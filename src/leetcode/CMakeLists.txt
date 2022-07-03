########################################
# Unit tests
########################################
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/src/leetcode/*.cc)

foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    target_link_libraries(${_test_name}
        glog
        gtest
        gtest_main
    )
    set_target_properties(${_test_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/test
    )
    add_test(${_test_name} ${_test_name})
endforeach()