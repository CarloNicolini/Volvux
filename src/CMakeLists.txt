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
add_library(VOLVUXHELPER
Arcball.cpp
BinVoxReader.cpp
Camera.cpp
GL2DPainter.cpp
GLee.cpp
GLInfo.cpp
GLMaterial.cpp
GLSL.cpp
GLText.cpp
GLTexture.cpp
GLUtils.cpp
Grid.cpp
Homography.cpp
Icosphere.cpp
Imageloader.cpp
Mathcommon.cpp
ObjLoader2.cpp
ObjLoader.cpp
ParametersLoader.cpp
Screen.cpp
Timer.cpp
TinyObjLoader.cpp
Util.cpp
VolumetricMeshIntersection.cpp
VolumetricSurfaceIntersection.cpp
VRCamera.cpp
)
#ALPProjector.cpp
#SmartMotor.cpp

#link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} VOLVUXHELPER)
target_link_libraries(VOLVUXHELPER ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} freeglut)

# Volvux Main files
set(VOLVUX_HDRS VolvuxMainWindow.h VolvuxExpWidget.h VolvuxWidget.h)
set(VOLVUX_SRCS VolvuxMainWindow.cpp VolvuxExpWidget.cpp VolvuxWidget.cpp)
set(VOLVUX_FORMS VolvuxMainWindow.ui)

QT4_WRAP_UI(VOLVUX_FORMS_HDRS ${VOLVUX_FORMS})
QT4_WRAP_CPP(VOLVUX_HDRS_MOC ${VOLVUX_HDRS})

add_executable(volvux volvux.cpp ${VOLVUX_SRCS} ${VOLVUX_HDRS} ${VOLVUX_HDRS_MOC} ${VOLVUX_FORMS_HDRS})
target_link_libraries(volvux ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} VOLVUXHELPER)

if (WIN32)
    set_target_properties(volvux PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
    set_target_properties(volvux PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
    set_target_properties(volvux PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    if (SMI_SUPPORT)
    target_link_libraries(volvux SMI) #volvux SMI
    endif(SMI_SUPPORT)
endif(WIN32)
