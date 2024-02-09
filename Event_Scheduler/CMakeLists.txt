cmake_minimum_required(VERSION 3.14)
project(Homework)

# Using -Wall is required:
add_compile_options(-Wall)

# These compile flags are highly recommended, but not required:
add_compile_options(-Wextra -Wpedantic)

# Optional super-strict mode:
add_compile_options(-fmessage-length=80 -fno-diagnostics-show-option)
add_compile_options(-fstack-protector-all -g -O3 -std=c++14 -Walloc-zero)
add_compile_options(-Walloca -Wctor-dtor-privacy -Wduplicated-cond)
add_compile_options(-Wduplicated-branches -Werror -Wfatal-errors -Winit-self)
add_compile_options(-Wlogical-op -Wold-style-cast -Wshadow)
add_compile_options(-Wunused-const-variable=1 -Wzero-as-null-pointer-constant)

# add_compile_options must be BEFORE add_executable or add_library.

add_library(hw7 Event.cc Schedule.cc validate.cc)
add_executable(test test.cc)
target_link_libraries(test hw7)

# Create a tar file every time:
add_custom_target(hw7.tar ALL COMMAND tar cf hw7.tar Event.cc Event.h Schedule.cc Schedule.h validate.cc validate.h test.cc CMakeLists.txt)