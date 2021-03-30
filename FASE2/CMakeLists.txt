
cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(trabalho)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(include)

add_executable(engine src/engine.c++ include/Translacao.cpp include/Translacao.h include/Rotacao.cpp include/Rotacao.h include/Escala.cpp include/Escala.h include/Cor.cpp include/Cor.h include/Ponto.cpp include/Ponto.h include/Operacao.h include/Push.h include/Push.cpp include/Pop.cpp include/Pop.h include/Desenhar.cpp include/Desenhar.h)
add_executable(generator src/generator.c++)

add_dependencies(engine generator)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if (WIN32)

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT class1)
    message(STATUS "GLUT_DIR set to: " ${GLUT_DIR})
    set(GLUT_DIR "" CACHE PATH "Path to GLUT folder")
    if (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")
        message(ERROR ": GLUT not found")
    endif (NOT EXISTS "${GLUT_DIR}/GL/glut.h" OR NOT EXISTS "${GLUT_DIR}/glut32.lib")    
    include_directories(${GLUT_DIR})
    link_directories(${GLUT_DIR})
    target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_DIR}/glut32.lib )
    if (EXISTS "${GLUT_DIR}/glut32.dll")
        file(COPY ${GLUT_DIR}/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif()
    
else (WIN32) #Linux and Mac

    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
    if(NOT GLUT_FOUND)
       message(ERROR ": GLUT not found!")
    endif(NOT GLUT_FOUND)
    
endif(WIN32)
