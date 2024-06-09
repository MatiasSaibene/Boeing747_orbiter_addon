cmake_minimum_required(VERSION 3.16)
project(Boeing747_for_Linux)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Directorio de salida de la biblioteca
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/BIN)

# Asegúrate de que todas las bibliotecas se creen en el directorio BIN
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
