EFFACE = clean
CCFLAGS = -g
g++Linux = -ansi -pedantic -Wall -std=c++11
RM = @rm
RMFLAGS = -f

include ../Materiel/Makefile

.PHONY : $(EFFACE)

GestionMateriel.o : GestionMateriel.cpp GestionMateriel.h ../Materiel/Capteur.o
	@echo "Compilation de <GestionMateriel.cpp>"
	@g++ -c $(g++Linux) GestionMateriel.cpp ../Materiel/Capteur.o $(CCFLAGS)

GestionMesure.o : GestionMesure.cpp GestionMesure.h Mesure.o
	@echo "Compilation de <GestionMesure.cpp>"
	@g++ -c $(g++Linux) GestionMesure.cpp ../Materiel/Mesure.o $(CCFLAGS)

$(EFFACE) :
	$(RM) $(RMFLAGS) $(EXE) *.o