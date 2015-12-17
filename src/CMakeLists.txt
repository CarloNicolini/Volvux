add_definitions(${QT_DEFINITIONS})
add_definitions("/DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED")
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
Arcball.cpp
BinVoxReader.cpp
GLSL.cpp
GLUtils.cpp
Grid.cpp
Homography.cpp
Icosphere.cpp
Imageloader.cpp
Mathcommon.cpp
ObjLoader2.cpp
ParametersLoader.cpp
Screen.cpp
Timer.cpp
TinyObjLoader.cpp
VolumetricMeshIntersection.cpp
VolumetricSurfaceIntersection.cpp
VRCamera.cpp)

set(VOLVUXHELPER_SRCS ${VOLVUXHELPER_SRCS} ALPProjector.cpp)


if(SMI_SUPPORT)
    set(VOLVUXHELPER_SRCS ${VOLVUXHELPER_SRCS} SmartMotor.cpp StdAfx.cpp)
endif(SMI_SUPPORT)

add_library(VOLVUXHELPER ${VOLVUXHELPER_SRCS})

#link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} VOLVUXHELPER)
target_link_libraries(VOLVUXHELPER ${OPENGL_LIBRARIES} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${ALP_LIBRARY})
if(ALP_SUPPORT)
target_link_libraries(VOLVUXHELPER ${ALP_LIBRARY})
endif(ALP_SUPPORT)

#if(SMI_SUPPORT)
#   target_link_libraries(VOLVUXHELPER ${SMI_LIBRARY})
#endif(SMI_SUPPORT)

# Volvux Main files
set(VOLVUX_HDRS VolvuxCalibrationWidget.h StackedWidget.h ProjectorWidgetPage.h CalibrationWidgetPage.h VolvuxWidgetPage.h VolvuxExpWidget.h VolvuxWidget.h) #VolvuxExpWidget.h  VolvuxMainWindow.h VolvuxWidget.h 
set(VOLVUX_SRCS VolvuxCalibrationWidget.cpp StackedWidget.cpp ProjectorWidgetPage.cpp CalibrationWidgetPage.cpp VolvuxWidgetPage.cpp VolvuxExpWidget.cpp VolvuxWidget.cpp ) #VolvuxExpWidget.cpp  VolvuxMainWindow.cpp VolvuxWidget.cpp 
set(VOLVUX_FORMS StackedWidget.ui ProjectorWidgetPage.ui CalibrationWidgetPage.ui VolvuxWidgetPage.ui) #VolvuxMainWindow.ui
#set(VOLVUX_HELPERS StackedWidgetHelper.cpp StackedWidgetHelper.h CalibrationHelper.cpp CalibrationHelper.h)

if(QT5_SUPPORT)
    # Tell CMake to run moc when necessary:
    set(CMAKE_AUTOMOC ON)
    # As moc files are generated in the binary dir, tell CMake
    # to always look for includes there:
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    QT5_WRAP_UI(VOLVUX_FORMS_HDRS ${VOLVUX_FORMS})
    QT5_WRAP_CPP(VOLVUX_HDRS_MOC ${VOLVUX_HDRS})

    #add_executable(volvux volvux.cpp ${VOLVUX_SRCS} ${VOLVUX_FORMS_HDRS})
    #target_link_libraries(volvux Qt5::Widgets Qt5::OpenGL VOLVUXHELPER)
    # Tell CMake to create the helloworld executable
    add_executable(volvux volvux.cpp ${VOLVUX_SRCS} ${VOLVUX_HDRS} ${VOLVUX_FORMS_HDRS} ${VOLVUX_HELPERS})

    #Link the helloworld executable to the Qt 5 widgets library.
    target_link_libraries(volvux Qt5::Gui Qt5::Widgets Qt5::OpenGL VOLVUXHELPER ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES})
    if (WIN32)
    # http://stackoverflow.com/questions/16773789/qt5-static-build-yields-failed-to-load-platform-plugin-windows/17271172#17271172
    target_link_libraries(volvux Qt5::WinMain)
    endif(WIN32)
    qt5_use_modules(volvux Gui Widgets OpenGL)

    #add_executable(welcomevolvux welcomevolvux.cpp ${VOLVUX_SRCS} ${VOLVUX_HDRS} ${VOLVUX_FORMS_HDRS})
    #Link the helloworld executable to the Qt 5 widgets library.
    #target_link_libraries(welcomevolvux Qt5::Gui Qt5::Widgets Qt5::OpenGL VOLVUXHELPER)
    #if (WIN32)
    # http://stackoverflow.com/questions/16773789/qt5-static-build-yields-failed-to-load-platform-plugin-windows/17271172#17271172
    #target_link_libraries(welcomevolvux Qt5::WinMain)
    #endif(WIN32)
    #qt5_use_modules(welcomevolvux Gui Widgets OpenGL)

endif(QT5_SUPPORT)


#if(QT4_SUPPORT)
#QT4_WRAP_UI(VOLVUX_FORMS_HDRS ${VOLVUX_FORMS})
#QT4_WRAP_CPP(VOLVUX_HDRS_MOC ${VOLVUX_HDRS})

#add_executable(volvux volvux.cpp ${VOLVUX_SRCS} ${VOLVUX_HDRS} ${VOLVUX_HDRS_MOC} ${VOLVUX_FORMS_HDRS})
#target_link_libraries(volvux ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${FREEGLUT_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} VOLVUXHELPER)

#if (WIN32)
#    set_target_properties(volvux PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
#    set_target_properties(volvux PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
#    set_target_properties(volvux PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
#endif(WIN32)
#endif(QT4_SUPPORT)

add_executable(testhomography testhomography.cpp)
target_link_libraries(testhomography VOLVUXHELPER dl)

add_executable(testhomonogl testhomonogl.cpp Homography.cpp)
