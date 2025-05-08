cmake_minimum_required(VERSION 3.16)

project(PowerPSI VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17) # 设置C++标准为C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 设置C++标准为必须
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 生成编译命令文件

set(CMAKE_INCLUDE_CURRENT_DIR ON) # 设置包含当前目录
# target_include_directories(PowerPSI PRIVATE ${CMAKE_SOURCE_DIR})
file(GLOB_RECURSE SRC_FILES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.h")
file(GLOB_RECURSE QML_FILES RELATIVE ${CMAKE_SOURCE_DIR} "qml/*.qml" "qml/*.qrc")
# file(GLOB_RECURSE RESOURCE_FILES RELATIVE ${CMAKE_SOURCE_DIR} "res/*.png" "res/*.gif")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(TARGET_NAME "${PROJECT_NAME}_d")
else()
    set(TARGET_NAME "${PROJECT_NAME}")
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick AxContainer) # 为下面的cmake语句提供依赖

qt_standard_project_setup(REQUIRES 6.5)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin) # 设置生成exe的输出目录
# file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/android")
# file(WRITE "${PROJECT_SOURCE_DIR}/android/EXECUTABLE_OUTPUT_PATH.txt" ${EXECUTABLE_OUTPUT_PATH})
# set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin) # 设置生成apk的输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin) # 设置生成apk的输出目录
# set(ANDROID_APK_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin) # 设置生成apk的输出目录
# set(CMAKE_ANDROID_APK_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin) # 设置生成apk的输出目录

qt_add_executable(${TARGET_NAME}
    # 指定生成可执行文件名和源文件
    main.cpp
    main.h
    ${SRC_FILES}
)

set_property(TARGET ${TARGET_NAME}
    # 指定AndroidManifest.xml的路径
    APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/android
)

set_target_properties(${TARGET_NAME}
    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION} # 设置macOS应用程序包的版本号，使用项目的版本号
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} # 设置macOS应用程序包的短版本号，使用项目的主版本号和次版本号
        MACOSX_BUNDLE TRUE # 将目标标记为macOS应用程序包
        WIN32_EXECUTABLE TRUE # 将目标标记为Windows可执行文件
)

qt_add_resources(${TARGET_NAME} "all_resources"
    # 指定生成物链接的资源文件及它们的qrc路径
    PREFIX "/"
    FILES ${RESOURCE_FILES} ${QML_FILES}
    # OPTIONS
    #     -no-compress # 不压缩资源文件
    #     -verbose # 显示详细的打包过程信息
    #     -binary # 将资源文件打包成二进制数据
    #     -compress # 压缩资源文件
    #     -prefix / # 指定资源文件的前缀路径
    #     -root /path/to/resources # 指定资源文件的根目录路径
)

target_link_libraries(${TARGET_NAME}
    # 指定生成物需要链接的Qt模块
    PRIVATE Qt6::Quick Qt6::AxContainer
)

target_compile_definitions(${TARGET_NAME}
    # 在编译配置为Debug或RelWithDebInfo时启用QML调试
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 打印
message(STATUS "TARGET_NAME:                ${TARGET_NAME}")
message(STATUS "CMake Build Type:           ${CMAKE_BUILD_TYPE}")
message(STATUS "Output Path:                ${EXECUTABLE_OUTPUT_PATH}")