cmake_minimum_required(VERSION 2.8.12)
project(LevelisedCostOfPowerAndHeat)

add_subdirectory(../GitHub/pybind11 ./cmake_build)
pybind11_add_module(LevelisedCostOfPowerAndHeat ./Source_Files/LevelisedCostOfPowerAndHeat.cpp)