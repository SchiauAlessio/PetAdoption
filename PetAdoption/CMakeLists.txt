cmake_minimum_required(VERSION 3.19)
project(PetAdoption)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.1.3\\mingw81_64")
set(CMAKE_AUTOUIC_SEARCH_PATHS gui)
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Quick REQUIRED)

include_directories(app_start)
include_directories(domain)
include_directories(dynamic_vector)
include_directories(gui)
include_directories(repository)
include_directories(repository/file_repo)
include_directories(repository/file_repo/csv)
include_directories(repository/file_repo/html)
include_directories(sensor)
include_directories(service)
include_directories(tests)
include_directories(ui)
include_directories(validators)

add_executable(PetAdoption
        app_start/AppStart.cpp
        app_start/AppStart.h
        domain/domain.cpp
        domain/domain.h
        dynamic_vector/dynamic_vector.h
        gui/admin_gui.cpp
        gui/admin_gui.h
        gui/initial_state.cpp
        gui/initial_state.h
        gui/user_gui.cpp
        gui/user_gui.h
        repository/file_repo/csv/csv_repo.cpp
        repository/file_repo/csv/csv_repo.h
        repository/file_repo/html/html_repo.cpp
        repository/file_repo/html/html_repo.h
        repository/file_repo/file_repo.cpp
        repository/file_repo/file_repo.h
        repository/file_repo/file_repo_adoption.cpp
        repository/file_repo/file_repo_adoption.h
        repository/adoption_repo.cpp
        repository/adoption_repo.h
        repository/repo.cpp
        repository/repo.h
        sensor/sensor.cpp
        sensor/sensor.h
        service/adoption_service.cpp
        service/adoption_service.h
        service/service.cpp
        service/service.h
        tests/program_tests.cpp
        tests/program_tests.h
        ui/admin_interface.cpp
        ui/admin_interface.h
        ui/user_interface.cpp
        ui/user_interface.h
        validators/exceptions.h
        validators/validating.cpp
        validators/validating.h
        main.cpp undo_redo/undo_redo.cpp undo_redo/undo_redo.h undo_redo/operation.cpp undo_redo/operation.h gui/AdoptionList_TableModel.cpp gui/AdoptionList_TableModel.h)

target_link_libraries(PetAdoption Qt6::Core)
target_link_libraries(PetAdoption Qt6::Widgets)
target_link_libraries(PetAdoption Qt6::Quick)