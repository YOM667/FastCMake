# MapleTA 使用正则表达式匹配&{} 并进行替换

# CMake 最低兼容版本
cmake_minimum_required(VERSION &{cmake_version})
# 设置项目名称 
project(&{project_name})
# 设置C++ 版本
set(CMAKE_CXX_STANDARD &{cpp_version})
# 设置源码文件路径
file(GLOB SRC_FILES Source/main.cpp
        "${PROJECT_SOURCE_DIR}/Source/*.h"
        "${PROJECT_SOURCE_DIR}/Source/*.cpp"
        "${PROJECT_SOURCE_DIR}/Source/*.hpp"
        "${PROJECT_SOURCE_DIR}/Source/*.cc"
)

# 获取路径下所有的.cpp/.c/.cc文件，并赋值给变量中
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Sources SRC_FILES)
# 规定.h头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/Sources)

# 将.cpp/.c/.cc文件生成可执行文件
add_executable(${PROJECT_NAME} ${SRC_FILES})

# 对add_library或add_executable生成的文件进行链接操作
# target_link_libraries()

# 导出Assets 
add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Assets")