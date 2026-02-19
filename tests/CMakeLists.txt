include_directories(${EngineM_SOURCE_DIR}/include)

set(TESTS
    test_vector.cpp
    test_matrix.cpp
    test_quaternion.cpp
    test_bezier.cpp
    test_hermite.cpp
)

foreach(test_src IN LISTS TESTS)
    get_filename_component(test_target ${test_src} NAME_WE)
    add_executable(${test_target} ${test_src})
    target_link_libraries(${test_target} gtest gtest_main EngineM)
    add_test(NAME ${test_target} COMMAND ${test_target})
    add_custom_command(TARGET ${test_target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:EngineM> $<TARGET_FILE_DIR:${test_target}>
    )
endforeach()
