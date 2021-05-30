EFFACE = clean
EXE = main
CCFLAGS = -g
g++Linux = -ansi -pedantic -Wall -std=c++11
RM = @rm
RMFLAGS = -f

.PHONY : $(EFFACE)

$(EXE) : $(EXE).o AirCleaner.o Capteur.o Date.o Mesure.o TypeMesure.o GestionMateriel.o GestionMesure.o TraitementMesure.o TraitementCapteur.o
	@echo 'EdL de <$(EXE)>'
	@g++ -o $(EXE) $(EXE).o

$(EXE).o: $(EXE).cpp
	@echo 'Compilation de <$(EXE).cpp>'
	@g++ -c $(g++Linux) $(EXE).cpp -g

AirCleaner.o : Materiel/AirCleaner.cpp
	@echo "Compilation de <AirCleaner.cpp>"
	@g++ -c $(g++Linux) Materiel/AirCleaner.cpp $(CCFLAGS)

Capteur.o : Materiel/Capteur.cpp
	@echo "Compilation de <Capteur.cpp>"
	@g++ -c $(g++Linux) Materiel/Capteur.cpp $(CCFLAGS)

Date.o : Materiel/Date.cpp
	@echo "Compilation de <Date.cpp>"
	@g++ -c $(g++Linux) Materiel/Date.cpp $(CCFLAGS)

Mesure.o : Materiel/Mesure.cpp Materiel/Date.o
	@echo "Compilation de <Mesure.cpp>"
	@g++ -c $(g++Linux) Materiel/Mesure.cpp Materiel/Date.o $(CCFLAGS)

TypeMesure.o : Materiel/TypeMesure.cpp
	@echo "Compilation de <TypeMesure.cpp>"
	@g++ -c $(g++Linux) Materiel/TypeMesure.cpp $(CCFLAGS)

GestionMateriel.o : Administration/GestionMateriel.cpp Materiel/Capteur.o
	@echo "Compilation de <GestionMateriel.cpp>"
	@g++ -c $(g++Linux) Administration/GestionMateriel.cpp Materiel/Capteur.o $(CCFLAGS)

GestionMesure.o : Administration/GestionMesure.cpp Materiel/Mesure.o
	@echo "Compilation de <GestionMesure.cpp>"
	@g++ -c $(g++Linux) Administration/GestionMesure.cpp Materiel/Mesure.o $(CCFLAGS)

TraitementMesure.o : Traitement/TraitementMesure.cpp Materiel/Date.o Materiel/Mesure.o Administration/GestionMesure.o Administration/GestionMateriel.o
	@echo "Compilation de <TraitementMesure.cpp>"
	@g++ -c $(g++Linux) Traitement/TraitementCapteur.cpp Materiel/AirCleaner.o Materiel/Capteur.o Materiel/Mesure.o Administration/GestionMesure.o Administration/GestionMateriel.o $(CCFLAGS)

TraitementCapteur.o : Traitement/TraitementCapteur.cpp Materiel/AirCleaner.o Materiel/Capteur.o Materiel/Mesure.o Administration/GestionMesure.o Administration/GestionMateriel.o
	@echo "Compilation de <TraitementCapteur.cpp>"
	@g++ -c $(g++Linux) Traitement/TraitementCapteur.cpp Materiel/AirCleaner.o Materiel/Capteur.o Materiel/Mesure.o Administration/GestionMesure.o Administration/GestionMateriel.o $(CCFLAGS)

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) *.o