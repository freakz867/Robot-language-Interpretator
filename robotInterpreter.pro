QT       += core gui
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11

LIBS += -lfl -ly

FLEXSOURCES = robotLexer.l
BISONSOURCES = robotParser.y

OTHER_FILES += \
    $$FLEXSOURCES \
    $$BISONSOURCES



SOURCES += \
    codeproc.cpp \
    codecontext.cpp \
    field/qgameplace.cpp \
    field/qcell.cpp \
    field/qboardplace.cpp \
    field/qlabyrinth.cpp \
    field/qrobot.cpp

flexsource.input = FLEXSOURCES
flexsource.output = /home/z/robot/robotInterpreter/robotLexer.cpp
flexsource.commands = flex --header-file=/home/z/robot/robotInterpreter/robotLexer.h -o /home/z/robot/robotInterpreter/robotLexer.cpp ${QMAKE_FILE_IN}
flexsource.variable_out = SOURCES
flexsource.name = Flex Sources ${QMAKE_FILE_IN}
flexsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += flexsource

flexheader.input = FLEXSOURCES
flexheader.output = /home/z/robot/robotInterpreter/robotLexer.h
flexheader.commands = @true
flexheader.variable_out = HEADERS
flexheader.name = Flex Headers ${QMAKE_FILE_IN}
flexheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += flexheader

bisonsource.input = BISONSOURCES
bisonsource.output = /home/z/robot/robotInterpreter/robotParser.cpp
bisonsource.commands = bison -d --defines=/home/z/robot/robotInterpreter/robotParser.h -o /home/z/robot/robotInterpreter/robotParser.cpp ${QMAKE_FILE_IN}
bisonsource.variable_out = SOURCES
bisonsource.name = Bison Sources ${QMAKE_FILE_IN}
bisonsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += bisonsource

bisonheader.input = BISONSOURCES
bisonheader.output = /home/z/robot/robotInterpreter/robotParser.h
bisonheader.commands = @true
bisonheader.variable_out = HEADERS
bisonheader.name = Bison Headers ${QMAKE_FILE_IN}
bisonheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += bisonheader

HEADERS += \
    codeproc.h \
    codecontext.h \
    field/qgameplace.h \
    field/qcell.h \
    field/qboardplace.h \
    field/qlabyrinth.h \
    field/qrobot.h

FORMS += \
    field/qgameplace.ui

RESOURCES += \
    svg.qrc
