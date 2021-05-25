EFFACE = clean
CCFLAGS = -g
g++Linux = -ansi -pedantic -Wall -std=c++11
RM = @rm
RMFLAGS = -f

.PHONY : $(EFFACE)

AirCleaner.o : AirCleaner.cpp AirCleaner.h
	@echo "Compilation de <AirCleaner.cpp>"
	@g++ -c $(g++Linux) AirCleaner.cpp $(CCFLAGS)

Capteur.o : Capteur.cpp Capteur.h
	@echo "Compilation de <Capteur.cpp>"
	@g++ -c $(g++Linux) Capteur.cpp $(CCFLAGS)

Mesure.o : Mesure.cpp Mesure.h Date.o
	@echo "Compilation de <Mesure.cpp>"
	@g++ -c $(g++Linux) Mesure.cpp Date.o $(CCFLAGS)

Date.o : Date.cpp Date.h Date.o
	@echo "Compilation de <Date.cpp>"
	@g++ -c $(g++Linux) Date.cpp$(CCFLAGS)

TypeMesure.o : TypeMesure.cpp TypeMesure.h
	@echo "Compilation de <TypeMesure.cpp>"
	@g++ -c $(g++Linux) TypeMesure.cpp $(CCFLAGS)

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) *.o