cmake_minimum_required(VERSION 3.28)
project(AlgoritmosGulosos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(seminario main.cpp)

target_sources(seminario
    PUBLIC
        FILE_SET CXX_MODULES FILES
            1_selecao_atividades.cppm
            2_mochila_fracionaria.cppm
            3_huffman.cppm
            4_kruskal_mst.cppm
            5_prim_mst.cppm
)
