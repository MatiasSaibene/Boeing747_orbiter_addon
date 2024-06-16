cmake_minimum_required(VERSION 3.16)
project(Boeing747_for_Windows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    # Deshabilitar advertencias específicas
    add_compile_options(/wd4996)  # Advertencia sobre 'strnicmp' deprecado
    add_compile_options(/wd2664)  # Advertencia sobre la conversión de tipos
    add_compile_options(/WX-)     # No tratar advertencias como errores
    add_compile_options(/we4311 /DNOMINMAX)
    add_compile_options(/permissive)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/BIN)

foreach(output_config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${output_config} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endforeach()

add_subdirectory(src_B985_121)
add_subdirectory(src_B747SP)
add_subdirectory(src_B747SOFIA)
add_subdirectory(src_B747_YAL1)
add_subdirectory(src_B747_Supertanker)
add_subdirectory(src_B747_SCA)
add_subdirectory(src_B747_LCF)
add_subdirectory(src_B747_AAC)
add_subdirectory(src_B747_400)
add_subdirectory(src_B747_100)
add_subdirectory(src_B747_8)
