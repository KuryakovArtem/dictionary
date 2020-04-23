cmake_minimum_required(version 3.2)
project(dictionary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# используем Boost.Program_options
# дабы не переусложнять, в качестве статической библиотеки
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

# исполняемый файл нашего приложения
add_executable(dictionary_app dictionary.cpp)
target_link_libraries(dictionary_app ${Boost_LIBRARIES})

enable_testing()

# в качестве фреймворка для тестирования используем GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# исполняемый файл тестов
add_executable(Test_for_dict test.cpp)
target_link_libraries(Test_for_dict ${GTEST_LIBRARIES} pthread)
# добавим этот файл в тестовый набор CTest
add_test(NAME Test COMMAND Test_for_dict)