add_definitions(${QT_DEFINITIONS})
include_directories("${CMAKE_SOURCE_DIR}/libs/eigen/unsupported")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


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
TinyObjLoader.cpp
Util.cpp
)
#ALPProjector.cpp
#SmartMotor.cpp

set(VOLVUX_HDRS VolvuxMainWindow.h  VolvuxExpWidget.h  VolvuxWidget.h)
set(VOLVUX_SRCS VolvuxMainWindow.cpp  VolvuxExpWidget.cpp  VolvuxWidget.cpp)
set(VOLVUX_FORMS VolvuxMainWindow.ui)
#link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} VOLVUXHELPER)
QT4_WRAP_UI(VOLVUX_FORMS_HDRS ${VOLVUX_FORMS})
QT4_WRAP_CPP(VOLVUX_SRCS_MOC ${VOLVUX_SRCS})

include_directories(${QT_INCLUDE_PATH} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES})

add_executable(volvux volvux.cpp ${VOLVUX_SRSC} ${VOLVUX_SRCS_MOC} ${VOLVUX_FORMS_HDRS})
target_link_libraries(volvux VOLVUXHELPER ${QT_LIBRARIES})

# if (WIN32)
# set_target_properties(volvux PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
# set_target_properties(volvux PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
# set_target_properties(volvux PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
# target_link_libraries(volvux ${QT_LIBRARIES} Core Experiment GLViz ${GL_LIBS} ALPProjector ${ALP_LIBRARY})
# if (SMI_SUPPORT)
# target_link_libraries(volvux SMI)
# endif(SMI_SUPPORT)
# endif(WIN32)

# if (NOT WIN32)
# target_link_libraries(VolumetricHelicoidSimulatorALPExperiment ${QT_LIBRARIES} Core Experiment GLViz ${GL_LIBS} )
# endif(NOT WIN32)
