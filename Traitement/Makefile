EFFACE = clean
EXE = main
CCFLAGS = -g
g++Linux = -ansi -pedantic -Wall -std=c++11
RM = @rm
RMFLAGS = -f

.PHONY : $(EFFACE)

include ../Materiel/Makefile 
include ../Administration/Makefile

$(EXE) : $(EXE).o
	@echo 'EdL de <$(EXE)>'
	@g++ -o $(EXE) $(EXE).o TraitementCapteur.o

$(EXE).o: $(EXE).cpp TraitementCapteur.o
	@echo 'Compilation de <$(EXE).cpp>'
	@g++ -c $(g++Linux) $(EXE).cpp TraitementCapteur.o -g

TraitementCapteur.o : TraitementCapteur.cpp TraitementCapteur.h ../Materiel/AirCleaner.o ../Materiel/Capteur.o ../Materiel/Mesure.o ../Administration/GestionMesure.o ../Administration/GestionMateriel.o
	@echo "Compilation de <TraitementCapteur.cpp>"
	@g++ -c $(g++Linux) TraitementCapteur.cpp ../Materiel/AirCleaner.o ../Materiel/Capteur.o ../Materiel/Mesure.o ../Administration/GestionMesure.o ../Administration/GestionMateriel.o $(CCFLAGS)

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) *.o