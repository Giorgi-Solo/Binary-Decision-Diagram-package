project(VDSProject_test CXX C)
cmake_minimum_required(VERSION 3.10)



# Now simply link against gtest or gtest_main as needed. Eg

add_executable(VDSProject_test main_test.cpp)
target_link_libraries(VDSProject_test Manager)
target_link_libraries(VDSProject_test gtest gtest_main pthread)

add_test(NAME mytest
         COMMAND testDriver --config $<CONFIG>
                            --exe $<TARGET_FILE:VDSProject_test>)
