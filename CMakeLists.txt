cmake_minimum_required(VERSION 3.16)

project(myMusicPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(myMusicPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        icon/back.png icon/danqu.png icon/foward.png icon/novoice.png icon/pause.png icon/play.png icon/shunxu.png icon/suiji.png icon/voice.png
        icon_resource.qrc
        song_info.h song_info.cpp
        song_list.h song_list.cpp
        file_tool.h file_tool.cpp
        icon/music_demopic.jpg
        song_tool.h
        song_tool.cpp
        songlistlabel.h
        songlistlabel.cpp
        icon/bg_1.jpg
        wid_songlist.h wid_songlist.cpp
        wid_ctrl.h wid_ctrl.cpp
        music_play.h music_play.cpp
        menu_of_song.h menu_of_song.cpp
        icon/addd.png icon/dele.png
        dialog_label.h dialog_label.cpp
        toast.h toast.cpp
        list_upmenu.h list_upmenu.cpp
        titlebar.h titlebar.cpp



    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET myMusicPlayer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(myMusicPlayer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(myMusicPlayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(myMusicPlayer PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.myMusicPlayer)
endif()
set_target_properties(myMusicPlayer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS myMusicPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(myMusicPlayer)
endif()
