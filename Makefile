EFFACE = clean
EXE = main
CCFLAGS = -g
g++Linux = -ansi -pedantic -Wall -std=c++11
RM = @rm
RMFLAGS = -f

.PHONY : $(EFFACE)

$(EXE) : $(EXE).o
	@echo 'EdL de <$(EXE)>'
	@g++ -o $(EXE) $(EXE).o

$(EXE).o: $(EXE).cpp
	@echo 'Compilation de <$(EXE).cpp>'
	@g++ -c $(g++Linux) $(EXE).cpp -g

AirCleaner.o : Materiel/AirCleaner.cpp Materiel/AirCleaner.h
	@echo "Compilation de <AirCleaner.cpp>"
	@g++ -c $(g++Linux) Materiel/AirCleaner.cpp $(CCFLAGS)

Capteur.o : Materiel/Capteur.cpp Materiel/Capteur.h
	@echo "Compilation de <Capteur.cpp>"
	@g++ -c $(g++Linux) Materiel/Capteur.cpp $(CCFLAGS)

Date.o : Materiel/Date.cpp Materiel/Date.h
	@echo "Compilation de <Date.cpp>"
	@g++ -c $(g++Linux) Materiel/Date.cpp $(CCFLAGS)

Mesure.o : Materiel/Mesure.cpp Materiel/Mesure.h Date.o
	@echo "Compilation de <Mesure.cpp>"
	@g++ -c $(g++Linux) Mesure.cpp Date.o $(CCFLAGS)

TypeMesure.o : Materiel/TypeMesure.cpp Materiel/TypeMesure.h
	@echo "Compilation de <TypeMesure.cpp>"
	@g++ -c $(g++Linux) Materiel/TypeMesure.cpp $(CCFLAGS)

GestionMateriel.o : Administration/GestionMateriel.cpp Administration/GestionMateriel.h Capteur.o
	@echo "Compilation de <GestionMateriel.cpp>"
	@g++ -c $(g++Linux) Administration/GestionMateriel.cpp Capteur.o $(CCFLAGS)

GestionMesure.o : Administration/GestionMesure.cpp Administration/GestionMesure.h Mesure.o
	@echo "Compilation de <GestionMesure.cpp>"
	@g++ -c $(g++Linux) Administration/GestionMesure.cpp Mesure.o $(CCFLAGS)

TraitementCapteur.o : Traitement/TraitementCapteur.cpp Traitement/TraitementCapteur.h AirCleaner.o Capteur.o Mesure.o GestionMesure.o GestionMateriel.o
	@echo "Compilation de <TraitementCapteur.cpp>"
	@g++ -c $(g++Linux) TraitementCapteur.cpp AirCleaner.o Capteur.o Mesure.o GestionMesure.o GestionMateriel.o $(CCFLAGS)

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) *.o