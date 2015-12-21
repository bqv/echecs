
CXX=g++
CXXFLAGS=-std=c++11 -O3 -pthread #-Wall -Wcast-qual -fno-exceptions -fno-rtti -pedantic -Wno-long-long -Wextra -Wshadow -mdynamic-no-pic
LDFLAGS=
LIBRARIES=
SOURCES= \
 chess.cpp \
 http.cpp \
 irc.cpp \
 main.cpp \
 network.cpp \
 plugins.cpp \
 plugins/aliasPlugin.cpp \
 stringUtils.cpp
OBJECTS=$(SOURCES: .cpp=.o)
ENGINE=engine/static.a
EXECUTABLE=echecs

all: $(EXECUTABLE)

$(ENGINE):
		$(MAKE) -C engine static ARCH=`uname -m | tr _ -`
		
$(EXECUTABLE): $(OBJECTS) $(ENGINE)
		$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(ENGINE) $(LDFLAGS) $(LIBRARIES)

.cpp.o:
		$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(RM) $(EXECUTABLE) *.o
		$(MAKE) -C engine clean

rmr:
		$(RM) $(EXECUTABLE) *.o
		$(MAKE) all
		./$(EXECUTABLE) irc.sublumin.al 6667
