# CMakeLists.txt

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.12)
project(Boeing747SCA)

# Directorio que contiene las bibliotecas
set(LIBRARY_DIRECTORY "/home/matias/orbiter_test/Orbiter/Orbitersdk/lib")

# Crear la biblioteca objetivo
add_library(Boeing747SCA SHARED Boeing747_SCA.cpp)

# Incluye directorios de encabezados necesarios
target_include_directories(Boeing747SCA PUBLIC "/home/matias/orbiter_test/Orbiter/Orbitersdk/include")

# Obtener la lista de archivos en el directorio
file(GLOB LIBRARIES "${LIBRARY_DIRECTORY}/*.lib")

# Enlazar con todas las bibliotecas encontradas en el directorio
target_link_libraries(Boeing747SCA ${LIBRARIES})
