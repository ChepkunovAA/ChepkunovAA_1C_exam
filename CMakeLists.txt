cmake_minimum_required(VERSION 3.0)
project(navi_predictor)

set (CMAKE_CXX_STANDARD 11)
set(HEADERS_DIR "${navi_predictor_SOURCE_DIR}/includes")
set(SRC_DIR "${navi_predictor_SOURCE_DIR}/src")

add_executable( run
  main.cpp
  ./sourse/Predictor.cpp
  ./sourse/Interface.cpp
  ./sourse/Abstract.cpp
)

target_include_directories(run PUBLIC ${navi_predictor_SOURCE_DIR}/includes)

