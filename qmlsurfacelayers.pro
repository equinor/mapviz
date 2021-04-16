!include( ./examples.pri ) {
    error( "Couldn't find the examples.pri file!" )
}

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \


RESOURCES += qmlsurfacelayers.qrc

OTHER_FILES += doc/src/* \
               doc/images/* \
               qml/qmlsurfacelayers/*

DISTFILES += \
    data/2.pmd \
    data/3.pmd \
    data/index.json \
    qml/qmlsurfacelayers/ColourBar.qml \
    qml/qmlsurfacelayers/SurfaceData.qml \
    qml/qmlsurfacelayers/Testsurf.qml

HEADERS += \
    headers/xtgeo/libxtg_.h \
    headers/xtgeo/pmread.h \
    headers/xtgeo/surf_import_petromod_bin.h \
    headers/xtgeo/x_swap_check.h \
    headers/xtgeo/x_swap_endian.h
