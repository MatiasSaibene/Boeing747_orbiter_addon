cmake_minimum_required(VERSION 3.16)
project(Boeing747SP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

if (MSVC)
    # Deshabilitar advertencias específicas
    add_compile_options(/wd4996)  # Advertencia sobre 'strnicmp' deprecado
    add_compile_options(/wd2664)  # Advertencia sobre la conversión de tipos
    add_compile_options(/WX-)     # No tratar advertencias como errores
    add_compile_options(/we4311 /DNOMINMAX)
    add_compile_options(/permissive)
endif()

set(LIBRARY_DIRECTORY "C:\\Users\\Matías Saibene\\Saved Games\\OpenOrbiter\\Orbitersdk\\lib")
set(INCLUDE_DIRECTORY "C:\\Users\\Matías Saibene\\Saved Games\\OpenOrbiter\\Orbitersdk\\include")
set(XRSOUND_DIRECTORY "C:\\Users\\Matías Saibene\\Saved Games\\OpenOrbiter\\Orbitersdk\\XRSound")

file(GLOB LIBRARIES "${LIBRARY_DIRECTORY}/*.lib")
file(GLOB XRSOUNDLIBRARIES "${XRSOUND_DIRECTORY}/*.lib")

# Definiciones de los archivos de código fuente
set(SOURCE_FILES
    Boeing747SP.cpp
)

# Definiciones de los archivos de encabezado
set(HEADER_FILES
    Boeing747SP.h
    747cockpitdefinitions.h
    747FCdefinitions.h
    747SPdefinitions.h
    XRSound.h
)

# Agregar los archivos de código fuente y encabezado al proyecto
add_library(${PROJECT_NAME} SHARED
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

# Agregar directorios de inclusión
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIRECTORY}
    ${XRSOUND_DIRECTORY}
)

# Enlazar con todas las bibliotecas encontradas en el directorio
target_link_libraries(${PROJECT_NAME} ${LIBRARIES} ${XRSOUNDLIBRARIES})

# Configuraciones específicas de Windows y Orbiter
if(WIN32)
    add_compile_definitions(NOMINMAX _CRT_SECURE_NO_WARNINGS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Opciones de compilador para MSVC
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /MD)

    # Librerías de tiempo de ejecución multi-threaded
    target_compile_options(${PROJECT_NAME} PRIVATE /MD)

    # Opciones de optimización y depuración
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${PROJECT_NAME} PRIVATE /O2)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE /Zi /Od)
        target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
    endif()
endif()
