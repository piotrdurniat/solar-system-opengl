cmake_minimum_required (VERSION 3.8)

project("gkikck-lab6")

if (WIN32)
    set(Boost_ADDITIONAL_VERSIONS 1.78.0)
    set(BOOST_ROOT "C:/Program Files/boost_1_78_0/")
    set(Boost_USE_STATIC_LIBS ON)  
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    include_directories(${BOOST_ROOT})
    link_directories(main ${BOOST_ROOT}/stage/lib)
endif()

include_directories("include")
add_executable(main "src/main.cpp" "src/Sphere.cpp" "src/Vertex.cpp" "src/Vector3f.cpp" "src/LightPoint.cpp" "src/Viewer.cpp" "src/Texture.cpp")

if(NOT MSVC)
    find_package(Boost REQUIRED COMPONENTS program_options)

    if (Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        target_link_libraries(main ${Boost_LIBRARIES})
    endif()
endif()

target_link_libraries(main -lGL -lglut -lGLU)
