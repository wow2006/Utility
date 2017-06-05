
function(add_test_exp test_name)
    add_executable(${test_name} "${test_name}_test.cpp")
    target_link_libraries(${test_name} GTest::GTest GTest::Main)
    add_test(${test_name} ${test_name})
endfunction(add_test_exp)

include_directories(..)
find_package(GTest REQUIRED)

add_test_exp(stringUtility)
add_test_exp(arrayUtility)
add_test_exp(dynamicArray)
