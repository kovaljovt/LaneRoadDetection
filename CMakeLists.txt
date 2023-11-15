cmake_minimum_required(VERSION 3.26)
project(LaneRoadDetection)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCV REQUIRED)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
        main.cpp
        UI.cpp
        VideoPlayer.cpp
        VideoPLayerTest.cpp
)

add_executable(LaneRoadDetection ${SOURCE_FILES})
target_link_libraries(LaneRoadDetection PRIVATE ${OpenCV_LIBS} Qt5::Widgets)
