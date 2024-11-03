cmake_minimum_required(VERSION 3.10)

project(flight-data-plotter VERSION 0.1 LANGUAGES CXX)

find_package(implot REQUIRED)
find_package(imgui REQUIRED)
find_package(SDL2 REQUIRED)
find_package(sdbus-c++ REQUIRED)
find_package(asio REQUIRED)

set(SOURCES
    src/main.cpp
    src/app.cpp
    src/receiver.cpp
    src/graph.cpp
    src/control_panel.cpp
    src/client.cpp
    src/windows.cpp
    src/network_proxy.cpp
    src/data_storage.cpp
    src/madgwick.cpp
    bindings/imgui_impl_sdl2.cpp
    bindings/imgui_impl_opengl3.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE implot::implot imgui::imgui SDL2::SDL2main SDBusCpp::sdbus-c++ asio::asio)
target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
        ${PROJECT_SOURCE_DIR}/bindings
)
