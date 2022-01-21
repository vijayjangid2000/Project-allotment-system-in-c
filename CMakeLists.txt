cmake_minimum_required(VERSION 3.21)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c userInterface.c inputProjectTask.c loginEmpTask.c inputEmpTask.c databaseHelper2.c allotmentTask.c userInterface.h inputProjectTask.h databaseHelper2.h allotmentTask.h inputEmpTask.h loginEmpTask.h)
