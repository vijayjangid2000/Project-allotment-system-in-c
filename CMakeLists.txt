cmake_minimum_required(VERSION 3.21)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c userInterface.c inputProject.c loginTask.c inputEmployee.c databaseHelper.c Allotment.c userInterface.h inputProject.h databaseHelper.h Allotment.h inputEmployee.h loginTask.h)
