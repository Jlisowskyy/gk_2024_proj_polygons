cmake_minimum_required(VERSION 3.16)

project(app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_RESOURCES
        images.qrc
)

set(PROJECT_SOURCES
        include/main.cpp
        include/mainwindow.cpp
        include/mainwindow.h
        include/mainwindow.ui
        src/ToolBar.cpp
        include/ManagingObjects/ToolBar.h
        src/DrawingWidget.cpp
        include/GraphicObjects/DrawingWidget.h
        src/Point.cpp
        include/GraphicObjects/Point.h
        src/Edge.cpp
        include/GraphicObjects/Edge.h
        src/Polygon.cpp
        include/ManagingObjects/Polygon.h
        include/Constants.h
        include/Interfaces/IConnectableElement.h
        include/Interfaces/IPolygonObject.h
        src/IEdgePolygonObject.cpp
        include/Interfaces/IEdgePolygonObject.h
        src/IPointPolygonObject.cpp
        include/Interfaces/IPointPolygonObject.h
        src/IPolygonObject.cpp
        include/Restrictions/ObjectRestriction.h
        src/EdgeHorizontalRestriction.cpp
        include/Restrictions/EdgeHorizontalRestriction.h
        src/EdgeRestriction.cpp
        include/Restrictions/EdgeRestriction.h
        src/PointRestriction.cpp
        include/Restrictions/PointRestriction.h
        include/Restrictions/Restrictions.h
        src/Restrictions.cpp
        src/RestrictionIcon.cpp
        include/Restrictions/RestrictionIcon.h
        src/ObjectRestriction.cpp
        src/EdgeVerticalRestriction.cpp
        include/Restrictions/EdgeVerticalRestriction.h
        src/EdgeConstLengthRestriction.cpp
        include/Restrictions/EdgeConstLengthRestriction.h
        src/PointContinuousRestriction.cpp
        include/Restrictions/PointContinuousRestriction.h
        src/EdgeBezierRestriction.cpp
        include/Restrictions/EdgeBezierRestriction.h
        include/GraphicObjects/BezierPoint.h
        src/BezierPoint.cpp
        src/Constants.cpp
        src/LengthDialog.cpp
        include/GraphicObjects/LengthDialog.h
        src/DebugDialog.cpp
        include/GraphicObjects/DebugDialog.h
        src/PointGContinuousRestriction.cpp
        include/Restrictions/PointGContinuousRestriction.h
        include/Restrictions/PointC1ContinuousRestriction.h
        include/Restrictions/PointG1ContinuousRestriction.h
        include/GraphicObjects/HelpWindow.h
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${PROJECT_RESOURCES}
    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(app SHARED
                ${PROJECT_SOURCES}
                ${PROJECT_RESOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(app
                ${PROJECT_SOURCES}
                ${PROJECT_RESOURCES}
        )
    endif ()
endif ()

target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app)
endif ()
set_target_properties(app PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS app
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(app)
endif ()
