# CMakeList.txt: KouSuan 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
    @ONLY
)

# 将源代码添加到此项目的可执行文件。
add_executable (MentalArithmeticTrainer "MentalArithmeticTrainer.cpp" )

target_include_directories(MentalArithmeticTrainer PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

# if (CMAKE_VERSION VERSION_GREATER 3.12)
set_property(TARGET MentalArithmeticTrainer PROPERTY CXX_STANDARD 20)
# endif()

# TODO: 如有需要，请添加测试并安装目标。
