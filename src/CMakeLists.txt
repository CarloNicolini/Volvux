add_definitions(${QT_DEFINITIONS})
include_directories("${CMAKE_SOURCE_DIR}/libs/eigen/unsupported")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(VOLVUX_HDRS VolvuxExpWidget.h  VolvuxMainWindow.h  VolvuxWidget.h)
set(VOLVUX_SRCS volvux.cpp  VolvuxExpWidget.cpp  VolvuxMainWindow.cpp  VolvuxWidget.cpp)
set(VOLVUX_FORMS VolvuxMainWindow.ui)
# link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} Core Experiment GLViz)
QT4_WRAP_UI(VOLVUX_FORMS_HDRS ${VOLVUX_FORMS})
QT4_WRAP_CPP(VOLVUX_HDRS_MOC ${VOLVUX_HDRS})

add_executable(volvux ${VOLVUX_SRSC} ${VOLVUX_HDRS} ${VOLVUX_HDRS_MOC} ${VOLVUX_FORMS_HDRS})

target_link_libraries(volvux ${QT_LIBRARIES})

if (WIN32)
set_target_properties(VolumetricHelicoidSimulatorALP PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
set_target_properties(VolumetricHelicoidSimulatorALP PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
set_target_properties(VolumetricHelicoidSimulatorALP PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
target_link_libraries(VolumetricHelicoidSimulatorALPExperiment ${QT_LIBRARIES} Core Experiment GLViz ${GL_LIBS} ALPProjector ${ALP_LIBRARY})
if (SMI_SUPPORT)
target_link_libraries(VolumetricHelicoidSimulatorALPExperiment SMI)
endif(SMI_SUPPORT)
endif(WIN32)

# if (NOT WIN32)
# target_link_libraries(VolumetricHelicoidSimulatorALPExperiment ${QT_LIBRARIES} Core Experiment GLViz ${GL_LIBS} )
# endif(NOT WIN32)
