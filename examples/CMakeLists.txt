set(ALL_SOURCES
	basic_usage.cpp
)

if(WIN32)
    add_executable(examples ${ALL_SOURCES})
    # 不带命令行
	# add_executable(examples WIN32 ${ALL_SOURCES})
else()
    add_executable(examples ${ALL_SOURCES})
endif()

# 链接依赖库
target_link_libraries(examples
    PRIVATE
    xxWeakPtr
)

# 确保输出目录正确
set_target_properties(examples
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# 设置包含目录
target_include_directories(examples PRIVATE 
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
)