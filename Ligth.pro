QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS += \
    exportclass.h \
    fen.h \
    fenprincipale.h \
    filemanager.h

SOURCES += \
    exportclass.cpp \
    fen.cpp \
    fenprincipale.cpp \
    filemanager.cpp \
    main.cpp

QT += widgets
QT += gui
QT += core
INSTALLS += target

RC_FILE = light.rc

RESOURCES += \
    res.qrc

