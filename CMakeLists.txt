cmake_minimum_required(VERSION 3.10)

# Set the project name
project(HeatExchanger)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target
add_executable(heat_exchanger
    code/main.cpp
    code/calculator/calculator.cpp
    code/calculator/calculator.h
    code/heatExchanger/heatExchanger.cpp
    code/heatExchanger/heatExchanger.h
    code/heatExchanger/product/product.cpp
    code/heatExchanger/product/product.h
)

# Optionally include directories if needed
target_include_directories(heat_exchanger PRIVATE code/calculator code/heatExchanger code/heatExchanger/product)
