add_definitions(${QT_DEFINITIONS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/libs/eigen/unsupported"
    ${QT_INCLUDE_PATH}
    ${QT_QTGUI_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
)
# https://cmake.org/cmake/help/v3.0/module/FindQt4.html
#set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Building VOLVUXHELPER library that consists

set(VOLVUXHELPER_SRCS
GLUtils.cpp
Grid.cpp
Homography.cpp
Mathcommon.cpp
ObjLoader.cpp
ParametersLoader.cpp
Timer.cpp
VolumetricSurfaceIntersection.cpp
VRCamera.cpp)

set(VOLVUXHELPER_SRCS ${VOLVUXHELPER_SRCS} ALPProjector.cpp)

if(SMI_SUPPORT)
    set(VOLVUXHELPER_SRCS ${VOLVUXHELPER_SRCS} SmartMotor.cpp StdAfx.cpp)
endif(SMI_SUPPORT)

add_library(VOLVUXHELPER ${VOLVUXHELPER_SRCS})

link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} Qt5::OpenGL VOLVUXHELPER)
target_link_libraries(VOLVUXHELPER ${OPENGL_LIBRARIES} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${ALP_LIBRARY})
if(ALP_SUPPORT)
target_link_libraries(VOLVUXHELPER ${ALP_LIBRARY})
endif(ALP_SUPPORT)

#if(SMI_SUPPORT)
#   target_link_libraries(VOLVUXHELPER ${SMI_LIBRARY})
#endif(SMI_SUPPORT)

# Volvux Main files
set(VOLVUX_HDRS VolvuxCalibrationWidget.h StackedWidget.h ProjectorWidgetPage.h CalibrationWidgetPage.h VolvuxWidgetPage.h VolvuxExpWidget.h VolvuxWidget.h testSMI.h)
set(VOLVUX_SRCS VolvuxCalibrationWidget.cpp StackedWidget.cpp ProjectorWidgetPage.cpp CalibrationWidgetPage.cpp VolvuxWidgetPage.cpp VolvuxExpWidget.cpp VolvuxWidget.cpp testSMI.cpp)
set(VOLVUX_FORMS StackedWidget.ui ProjectorWidgetPage.ui CalibrationWidgetPage.ui VolvuxWidgetPage.ui testSMI.ui)

if(QT5_SUPPORT)
    # Tell CMake to run moc when necessary:
    set(CMAKE_AUTOMOC ON)
    # As moc files are generated in the binary dir, tell CMake
    # to always look for includes there:
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    QT5_WRAP_UI(VOLVUX_FORMS_HDRS ${VOLVUX_FORMS})
    QT5_WRAP_CPP(VOLVUX_HDRS_MOC ${VOLVUX_HDRS})

    # Tell CMake to create the volvux executable
    add_executable(volvux volvux.cpp ${VOLVUX_SRCS} ${VOLVUX_HDRS} ${VOLVUX_FORMS_HDRS} ${VOLVUX_HELPERS})

    #Link the helloworld executable to the Qt 5 widgets library.
    target_link_libraries(volvux Qt5::Gui Qt5::Widgets Qt5::OpenGL VOLVUXHELPER ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} )
    if (WIN32)
        # http://stackoverflow.com/questions/16773789/qt5-static-build-yields-failed-to-load-platform-plugin-windows/17271172#17271172
        target_link_libraries(volvux Qt5::WinMain)
    endif(WIN32)
    qt5_use_modules(volvux Gui Widgets OpenGL)
endif(QT5_SUPPORT)


add_executable(testhomonogl testhomonogl.cpp Homography.cpp)

if (ALP_SUPPORT)
add_executable(testALPProjector tests/testALPProjector.cpp ALPProjector.cpp)
target_link_libraries(testALPProjector ${ALP_LIBRARY})
endif(ALP_SUPPORT)
