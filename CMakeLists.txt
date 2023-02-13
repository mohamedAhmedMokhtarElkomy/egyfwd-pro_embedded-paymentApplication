cmake_minimum_required(VERSION 3.22)

project(PaymentApp)

add_executable(main.exe main.c Card/card.c Terminal/terminal.c Server/server.c Application/app.c)

target_include_directories(main.exe PUBLIC Application/ Terminal/ Server/ Card/)