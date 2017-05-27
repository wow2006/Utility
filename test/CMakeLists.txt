enable_testing()

include_directories(..)
find_package(GTest REQUIRED)

add_executable(StringUtility stringUtility_test.cpp)

target_link_libraries(StringUtility GTest::GTest GTest::Main)

add_test(StringUtility_test StringUtility)
