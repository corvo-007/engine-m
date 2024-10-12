add_executable(test_vector2d test_vector2d.cpp)
add_executable(test_vector3d test_vector3d.cpp)
add_executable(test_matrix test_matrix.cpp)

target_link_libraries(test_vector2d gtest gtest_main MathEngine)
target_link_libraries(test_vector3d gtest gtest_main MathEngine)
target_link_libraries(test_matrix gtest gtest_main MathEngine)

add_test(NAME test_vector2d COMMAND test_vector2d)
add_test(NAME test_vector3d COMMAND test_vector3d)
add_test(NAME test_matrix COMMAND test_matrix)

foreach (test_exec IN ITEMS test_vector2d test_vector3d test_matrix)
    add_custom_command(TARGET ${test_exec} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:MathEngine> $<TARGET_FILE_DIR:${test_exec}>
    )
endforeach ()
