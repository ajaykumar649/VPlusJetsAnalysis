CXXFLAGS := `root-config --cflags` -O2 -g -Wall -DMAIN -I${ROOFITSYS}/include

LDFLAGS := `root-config --libs` -L${ROOFITSYS}/lib -L${CMSSW_BASE}/lib/${SCRAM_ARCH} -lRooFitCore -lHiggsAnalysisCombinedLimit

#%.o: %.cc
#	${CXX} -c $*.cc -o $@ ${CXXFLAGS} 
#
#%.o: %.C
#	${CXX} -c $*.C -o $@ ${CXXFLAGS} 

all : exe

#exe: makeDataCardShapes.exe makeDataCardShapes4tgc.exe makeDataCardFromTable.exe makeDataCardFromRooWorkspace.exe
exe:  makeDataCardShapes.exe \
	makeDataCardShapes4tgc.exe \
	makeDataCardShapes4wwgamaqgc.exe \
	makeDataCardFromTable.exe \
	makeDataCardFromRooWorkspace.exe

makeDataCardShapes.exe: makeDataCardShapes.o card.o hwwutils.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardFromTable.exe: makeDataCardFromTable.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardFromRooWorkspace.exe: makeDataCardFromRooWorkspace.o card.o hwwutils.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardShapes4tgc.exe: makeDataCardShapes4tgc.o card.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardShapes4wwgamaqgc.exe: makeDataCardShapes4wwgamaqgc.o card.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardShapes.o: makeDataCardShapes.cc card.h hwwutils.h hwwinputs.h mjjinputs.h

makeDataCardFromTable.o: makeDataCardFromTable.cc dcutils.C hwwinputs.h hwwutils.C

makeDataCardFromRooWorkspace.o: makeDataCardFromRooWorkspace.cc card.h hwwinputs.h hwwutils.h

makeDataCardShapes4tgc.o: makeDataCardShapes4tgc.cc card.h atgcinputs.h

makeDataCardShapes4wwgamaqgc.o: makeDataCardShapes4wwgamaqgc.cc wwgamaqgcinputs.h card.h

card.o: card.cc card.h
