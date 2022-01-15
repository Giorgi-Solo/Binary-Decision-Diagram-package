add_subdirectory(test)
add_subdirectory(verify)
add_subdirectory(bench)

add_library(Manager Manager.cpp)

enable_testing()
