add_definitions(${QT_DEFINITIONS})
include_directories("${CMAKE_SOURCE_DIR}/libs/eigen/unsupported")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(VOLUMETRIC_HELICOID_ALP_HDR MainWindow.h VolumetricHelicoidWidgetALP.h ExperimentGLWidget.h)
set(VOLUMETRIC_HELICOID_ALP_SRC volumetricHelicoidSimulatorALP.cpp MainWindow.cpp  VolumetricHelicoidWidgetALP.cpp ExperimentGLWidget.cpp)
set(VOLUMETRIC_HELICOID_ALP_FORMS MainWindow.ui)
# link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES} Core Experiment GLViz)
QT4_WRAP_UI(VOLUMETRIC_HELICOID_ALP_FORMS_HEADERS ${VOLUMETRIC_HELICOID_ALP_FORMS})
QT4_WRAP_CPP(VOLUMETRIC_HELICOID_ALP_HEADERS_MOC ${VOLUMETRIC_HELICOID_ALP_HDR})

add_executable(VolumetricHelicoidSimulatorALPExperiment ${VOLUMETRIC_HELICOID_ALP_SRC} ${VOLUMETRIC_HELICOID_ALP_HDR} ${VOLUMETRIC_HELICOID_ALP_HEADERS_MOC} ${VOLUMETRIC_HELICOID_ALP_RESOURCES_SOURCES} ${VOLUMETRIC_HELICOID_ALP_FORMS_HEADERS} ${VOLUMETRIC_ALP_HELICOID_RCS} )

target_link_libraries(VolumetricHelicoidSimulatorALPExperiment ${QT_LIBRARIES} Core Experiment GLViz ${GL_LIBS} ALPProjector ${ALP_LIBRARY})

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
