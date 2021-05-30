EFFACE = clean
EXE = main
CCFLAGS = -g
g++Linux = -ansi -pedantic -Wall -std=c++11
RM = @rm
RMFLAGS = -f

.PHONY : $(EFFACE)

$(EXE) : $(EXE).o 
	@echo 'EdL de <$(EXE)>'
	@g++ -o $(EXE) $(EXE).o AirCleaner.o TraitementCapteur.o TraitementMesure.o Date.o TypeMesure.o Capteur.o GestionMesure.o GestionMateriel.o Mesure.o

$(EXE).o: $(EXE).cpp TraitementCapteur.o TraitementMesure.o TypeMesure.o Date.o Capteur.o AirCleaner.o GestionMesure.o GestionMateriel.o Mesure.o
	@echo 'Compilation de <$(EXE).cpp>'
	@g++ -c $(g++Linux) $(EXE).cpp -g

AirCleaner.o : Materiel/AirCleaner.cpp
	@echo "Compilation de <AirCleaner.cpp>"
	@g++ -c $(g++Linux) Materiel/AirCleaner.cpp $(CCFLAGS)

Capteur.o : ./Materiel/Capteur.cpp
	@echo "Compilation de <Capteur.cpp>"
	@g++ -c $(g++Linux) ./Materiel/Capteur.cpp $(CCFLAGS)

Date.o : ./Materiel/Date.cpp
	@echo "Compilation de <Date.cpp>"
	@g++ -c $(g++Linux) ./Materiel/Date.cpp $(CCFLAGS)

TypeMesure.o : ./Materiel/TypeMesure.cpp
	@echo "Compilation de <TypeMesure.cpp>"
	@g++ -c $(g++Linux) ./Materiel/TypeMesure.cpp $(CCFLAGS)

Mesure.o : ./Materiel/Mesure.cpp
	@echo "Compilation de <Mesure.cpp>"
	@g++ -c $(g++Linux) ./Materiel/Mesure.cpp $(CCFLAGS)

GestionMateriel.o : ./Administration/GestionMateriel.cpp
	@echo "Compilation de <GestionMateriel.cpp>"
	@g++ -c $(g++Linux) ./Administration/GestionMateriel.cpp $(CCFLAGS)

GestionMesure.o : ./Administration/GestionMesure.cpp
	@echo "Compilation de <GestionMesure.cpp>"
	@g++ -c $(g++Linux) ./Administration/GestionMesure.cpp $(CCFLAGS)

TraitementCapteur.o : ./Traitement/TraitementCapteur.cpp
	@echo "Compilation de <TraitementCapteur.cpp>"
	@g++ -c $(g++Linux) ./Traitement/TraitementCapteur.cpp $(CCFLAGS)

TraitementMesure.o : ./Traitement/TraitementMesure.cpp
	@echo "Compilation de <TraitementMesure.cpp>"
	@g++ -c $(g++Linux) ./Traitement/TraitementMesure.cpp $(CCFLAGS)

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) *.o