cmake_minimum_required(VERSION 3.17)
project(workshop C)

message("Compiler id is: " ${CMAKE_C_COMPILER_ID})

add_executable(workshop main.c src/kv_pair.c src/word_counter.c include/word_counter.h)

foreach(exec workshop)
    message("Setting properties of ${exec}")
    set_target_properties(${exec}
            PROPERTIES
            LANGUAGE C
            C_STANDARD 11
            C_STANDARD_REQUIRED YES
            C_EXTENSIONS NO
            )
endforeach()

if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    message("Setting MSVC flags")
    list(APPEND COMPILE_FLAGS /W4 /RTC1 /Od /Zi)
else()
    message("Setting GCC/Clang flags")
    list(APPEND COMPILE_FLAGS -O1 -Wall -Wextra -pedantic -Werror)
endif()

target_compile_options(workshop PRIVATE ${COMPILE_FLAGS})

list(APPEND files alice0.txt)

foreach(file IN LISTS files)
    configure_file(${file} ${file} COPYONLY)
endforeach()

if ((CMAKE_C_COMPILER_ID STREQUAL "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "Clang"))
    message("Enabling ASAN")
    # enable ASAN - linux and mac only! disable this one if not available on your system
    message("ASAN: If you get an error compiling on your system, remove the line below.")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")
endif()



