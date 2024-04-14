# CMakeLists.txt

set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.12)
project(Boeing747SOFIA)

# Directorio que contiene las bibliotecas
set(LIBRARY_DIRECTORY "$HOME/orbiter_test/Orbiter/Orbitersdk/lib")

# Crear la biblioteca objetivo
add_library(Boeing747SOFIA SHARED Boeing747SOFIA.cpp)

# Incluye directorios de encabezados necesarios
target_include_directories(Boeing747SOFIA PUBLIC "$HOME/orbiter_test/Orbiter/Orbitersdk/include")

# Obtener la lista de archivos en el directorio
file(GLOB LIBRARIES "${LIBRARY_DIRECTORY}/*.lib")

# Enlazar con todas las bibliotecas encontradas en el directorio
target_link_libraries(Boeing747SOFIA ${LIBRARIES})
