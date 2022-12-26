CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla -Wno-reorder -ggdb3
OBJECTS = Asset.o Board.o building.o Cash.o chance.o coopfeeaction.o dctimslineaction.o die.o Game.o goosenestingaction.o gototimsaction.o ImprovementData.o main.o needleshall.o needleshallaction.o needleshallactionsfactory.o nonproperties.o nonpropertiesactionsfactory.o nonpropertiesfactory.o Observer.o osapaction.o ownable.o ownablefactory.o Player.o rollupthetims.o rollupthetimsaction.o slc.o slcaction.o slcactionsfactory.o Subject.o TextDisplay.o tuitionaction.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = watopoly

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies