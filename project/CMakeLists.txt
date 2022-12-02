cmake_minimum_required(VERSION 3.14)

if (WIN32)
    project(MY_PROJECT LANGUAGES CXX)
elseif(UNIX)
    project(MY_PROJECT)
endif()

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

#Прописать пути к соурсам qt и opencv
set(Qt6_DIR "/home/murph/qt/gcc_64")
set(OpenCV_DIR "/opt/opencv-4.x/build")

find_package(Qt6 6.2 COMPONENTS Core Widgets Gui Qml Quick REQUIRED)
find_package(OpenCV REQUIRED)


set(FORMS_DIR "${CMAKE_SOURCE_DIR}/ui")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")


include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})
link_directories(${LIB_DIR})

file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.qml"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*"
    "${SOURCE_DIR}/*"
    main.cpp
)

file(GLOB_RECURSE LIBRARY
    "${LIB_DIR}/*"
    )


set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
if (WIN32)
    add_executable(MY_PROJECT WIN32 ${SOURCES})
elseif(UNIX)
    add_executable(MY_PROJECT ${SOURCES} ./ui/main.qml)
endif()

# Add the target includes for MY_PROJECT
target_include_directories(MY_PROJECT PRIVATE ${FORMS_DIR})
target_include_directories(MY_PROJECT PRIVATE ${INCLUDE_DIR})
target_include_directories(MY_PROJECT PRIVATE ${SOURCE_DIR})
#===================== LINKING LIBRARIES =======================#
target_link_libraries(MY_PROJECT ${LIBRARY} ${OpenCV_LIBS})
target_link_libraries(MY_PROJECT Qt6::Widgets Qt6::Gui Qt6::Quick)
