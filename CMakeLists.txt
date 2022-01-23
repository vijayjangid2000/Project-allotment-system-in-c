cmake_minimum_required(VERSION 3.21)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled aMain.c auserInterface.c addProject.c aUserLogin.c addEmployee.c aDbHelper.c allotment.c auserInterface.h addProject.h aDbHelper.h allotment.h addEmployee.h aUserLogin.h)
