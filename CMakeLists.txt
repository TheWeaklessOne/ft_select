cmake_minimum_required(VERSION 3.14)
project(ft_select C)

set(CMAKE_C_STANDARD 11)

include_directories(Includes)

add_executable(ft_select
        Includes/data_structures.h
        Includes/list.h
        Sources/data_structures.c
        Sources/list.c
        Sources/list_2.c
        Sources/ft_select.c
        Sources/ft.c
        Sources/ft_2.c
        Includes/ft_select.h Sources/init.c Sources/input.c Sources/escape.c)

set_target_properties(ft_select PROPERTIES LINK_FLAGS "-ltermcap")