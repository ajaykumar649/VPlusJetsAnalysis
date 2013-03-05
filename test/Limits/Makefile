CXXFLAGS := `root-config --cflags` -O2 -g -Wall -DMAIN -I${ROOFITSYS}/include

LDFLAGS := `root-config --libs` -L${ROOFITSYS}/lib -L${CMSSW_BASE}/lib/${SCRAM_ARCH} -lRooFitCore -lHiggsAnalysisCombinedLimit

%.o: %.cc
	${CXX} -c $*.cc -o $@ ${CXXFLAGS} 

%.o: %.C
	${CXX} -c $*.C -o $@ ${CXXFLAGS} 

all : exe

#exe: makeDataCardShapes.exe makeDataCardShapes4tgc.exe makeDataCardFromTable.exe makeDataCardFromRooWorkspace.exe
exe: makeDataCardShapes4tgc.exe \
	makeDataCardShapes4wwgamaqgc.exe \
	makeDataCardFromTable.exe \
	makeDataCardFromRooWorkspace.exe

makeDataCardShapes.exe: makeDataCardShapes.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardFromTable.exe: makeDataCardFromTable.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardFromRooWorkspace.exe: makeDataCardFromRooWorkspace.o card.o hwwutils.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardShapes4tgc.exe: makeDataCardShapes4tgc.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardShapes4wwgamaqgc.exe: makeDataCardShapes4wwgamaqgc.o card.o
	${CXX} -g -o $@ $^  ${LDFLAGS}

makeDataCardShapes.o: makeDataCardShapes.cc hwwshapes.C dcutils.C hwwinputs.h mjjinputs.h hwwutils.C

makeDataCardFromTable.o: makeDataCardFromTable.cc dcutils.C hwwinputs.h hwwutils.C

makeDataCardFromRooWorkspace.o: makeDataCardFromRooWorkspace.cc card.cc card.h hwwinputs.h hwwutils.h

makeDataCardShapes4tgc.o: makeDataCardShapes4tgc.cc dcutils.C atgcinputs.h

makeDataCardShapes4twwgamaqgc.o: makeDataCardShapes4twwgamaqgc.cc wwgamaqgcinputs.h card.h

card.o: card.cc card.h
