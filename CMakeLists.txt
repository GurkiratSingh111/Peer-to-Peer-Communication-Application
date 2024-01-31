cmake_minimum_required(VERSION 3.21)
project(Assignment2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Assignment2 s-talk.c receiver.c screen.c keyboard.c sender.c list.o thread_canceller.c)
