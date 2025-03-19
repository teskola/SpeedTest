cmake_minimum_required(VERSION 3.16)

project(sairaan_nopee VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS LinguistTools)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(QT_NO_GLOBAL_APK_TARGET_PART_OF_ALL OFF)

qt_standard_project_setup(
    REQUIRES 6.8
    I18N_TRANSLATED_LANGUAGES fi)

qt_add_executable(appsairaan_nopee
    main.cpp
)

qt_add_qml_module(appsairaan_nopee
    URI sairaan_nopee
    VERSION 1.0
    QML_FILES
    QML_FILES SpeedTestButton.qml Main.qml
    SOURCES main.cpp speedtest.cpp
    SOURCES speedtest.h
    SOURCES i18n/qml_fi_FI.ts
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appsairaan_nopee PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appsairaan_nopee
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
    QT_ANDROID_PACKAGE_NAME "com.teskola.speedtest"
    QT_ANDROID_VERSION_NAME "1.2"
    QT_ANDROID_VERSION_CODE 105
    QT_ANDROID_BUILD_ALL_ABIS TRUE
)

target_link_libraries(appsairaan_nopee
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appsairaan_nopee
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
