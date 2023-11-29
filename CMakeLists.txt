cmake_minimum_required(VERSION 3.26)
project(LaneRoadDetection)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED opencv4)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(glfw)

add_executable(${PROJECT_NAME}
        main.cpp
        src/Regression.h
        src/RoadDetection.cpp
        src/Application.cpp
        src/VideoPlayer.cpp
        imgui/imgui_demo.cpp
        glad/src/glad.c
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${OPENCV_INCLUDE_DIRS}
        "glad/include" "imgui/"
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${OPENCV_LIBRARIES}
        glfw
)