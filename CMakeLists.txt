cmake_minimum_required(VERSION 3.21)
project(ict1009_team22_2022_cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(ict1009_team22_2022_cpp
        main.cpp
        main.h
        movie_repo.h
        actions.cpp
        colors.h
        colors.cpp
        file.h
        hall.cpp
        hall.h
        menu.cpp
        menu.h
        menu_item.cpp
        menu_item.h
        movie.cpp
        movie.h
        show.cpp
        show.h)
