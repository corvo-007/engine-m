add_executable(test_vector2d test_vector2d.cpp)
add_executable(test_vector3d test_vector3d.cpp)
add_executable(test_matrix test_matrix.cpp)
add_executable(test_quaternion test_quaternion.cpp)
add_executable(test_bezier_curve test_bezier.cpp)
add_executable(test_hermite_curve test_hermite.cpp)

target_link_libraries(test_vector2d gtest gtest_main EngineM)
target_link_libraries(test_vector3d gtest gtest_main EngineM)
target_link_libraries(test_matrix gtest gtest_main EngineM)
target_link_libraries(test_quaternion gtest gtest_main EngineM)
target_link_libraries(test_bezier_curve gtest gtest_main EngineM)
target_link_libraries(test_hermite_curve gtest gtest_main EngineM)

add_test(NAME test_vector2d COMMAND test_vector2d)
add_test(NAME test_vector3d COMMAND test_vector3d)
add_test(NAME test_matrix COMMAND test_matrix)
add_test(NAME test_quaternion COMMAND test_quaternion)
add_test(NAME test_bezier_curve COMMAND test_bezier_curve)
add_test(NAME test_hermite_curve COMMAND test_hermite_curve)

foreach (test_exec IN ITEMS test_vector2d test_vector3d test_matrix)
    add_custom_command(TARGET ${test_exec} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:EngineM> $<TARGET_FILE_DIR:${test_exec}>
    )
endforeach ()
