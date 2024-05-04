

project (sxw_hw1)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (src SRC_LIST)

include_directories (inc)

add_executable (sxw_hw1 ${SRC_LIST})   #设置可执行文件的名称，sxw_hw1之后build目录下出现sxw_hw1.exe
