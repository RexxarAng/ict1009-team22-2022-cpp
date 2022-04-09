cmake_minimum_required(VERSION 3.21)
project(ict1009_team22_2022_cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(ict1009_team22_2022_cpp
        main.cpp
        main.h
        repository.h
        movie_repo.h
        colors.h
        colors.cpp
        hall.cpp
        hall.h
        menu.cpp
        menu.h
        menu_item.cpp
        menu_item.h
        movie.cpp
        movie.h
        show.cpp
        show.h
        repository_exception.h
        repository_template.h
        movie_controller.cpp
        movie_controller.h
        hall_controller.cpp
        hall_controller.h
        show_controller.cpp
        show_controller.h
        booking_controller.cpp
        booking_controller.h
        screen_utility.cpp
        screen_utility.h
        helper.cpp
        helper.h)
