CXX = c++

OBJS += Main.o
OBJS += GameManager.o
OBJS += Body.o
OBJS += Character.o
OBJS += MMath.o
OBJS += PlayerBody.o
OBJS += Scene1.o
OBJS += Timer.o
OBJS += VMath.o
OBJS += Window.o
OBJS += Steering/KinematicBody.o
OBJS += Steering/SteeringOutput.o

#OBJS += Graph.o
#OBJS += Scene2.o
#OBJS += Tile.o
#OBJS += KinematicSteeringOutput.o
#OBJS += SteeringBehaviour.o
#OBJS += StaticBody.o
#OBJS += Seek.o

SDLCFG := sdl2-config

CPPFLAGS = $(shell $(SDLCFG) --cflags)

LIBSDL = $(shell $(SDLCFG) --libs)
LIBSDL += -lSDL2_image

CPPFLAGS += -std=c++17
CPPFLAGS += -I. -ISteering/ -IStateMachine/ -IScenes
CPPFLAGS += -IPathfinding/ -IPathFinding/
#CPPFLAGS += -I/Library/Frameworks/SDL2_image.framework/Headers
#CPPFLAGS += -I/Library/Frameworks/SDL2.framework/Headers
# TODO Add more if needed


main: $(OBJS)
	$(CXX) -o main $(OBJS) $(LIBSDL)

Main.o: Main.cpp GameManager.h
	$(CXX) -c $(CPPFLAGS) Main.cpp


%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $< -o $@

%.cpp: %.h
	touch $@

%.cpp: %.hpp
	touch $@


.PHONY:	clean

clean:
	-rm -f $(OBJS) main



########

#Main.o:	Main.cpp
#	gcc -std=c++17 -c \
#	-I./Steering \
#	-I/Library/Frameworks \
#	-I/Library/Frameworks/SDL2.framework/Headers  \
#	-I/Library/Frameworks/SDL2_image.framework/Headers \
#	Main.cpp

