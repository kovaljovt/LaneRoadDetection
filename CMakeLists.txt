cmake_minimum_required(VERSION 3.26)
project(LaneRoadDetection)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV 4.5 REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(LaneRoadDetection
        main.cpp
        UI.cpp
        VideoPlayer.cpp
        test.cpp
)

target_include_directories(LaneRoadDetection PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(LaneRoadDetection PRIVATE ${OpenCV_LIBS} Qt5::Widgets)
