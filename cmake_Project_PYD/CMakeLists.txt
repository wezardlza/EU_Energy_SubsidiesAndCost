cmake_minimum_required(VERSION 2.8.12)
project(EUSAC)

add_subdirectory(../../GitHub/pybind11 ./cmake_build)
pybind11_add_module(EUSAC ../Source_Files/ZAMATH.cpp ../Source_Files/SRF.cpp ../Source_Files/EUSAC.cpp ../Source_Files/PYBIND_EUSAC.cpp)
