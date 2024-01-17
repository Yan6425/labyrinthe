exe: menu.o plateau.o joueur.o affichage.o main.o
	@echo "Compilation de l'exécutable."
	gcc menu.o affichage.o plateau.o joueur.o main.o -o labyrinthe.exe

affichage.o: affichage.c structure.h fonctions.h 
	@echo "Compilation de affichage."
	gcc -c -Wall affichage.c -o affichage.o

joueur.o: joueur.c structure.h fonctions.h
	@echo "Compilation de joueur."
	gcc -c -Wall joueur.c -o joueur.o

plateau.o: plateau.c structure.h fonctions.h
	@echo "Compilation de plateau."
	gcc -c -Wall plateau.c -o plateau.o

menu.o: menu.c structure.h fonctions.h
	@echo "Compilation de menu."
	gcc -c -Wall menu.c -o menu.o

main.o: main.c structure.h fonctions.h
	@echo "Compilation du main."
	gcc -c -Wall main.c -o main.o

clean:
	@echo "J'ai tout effacé."
	rm -f *.o
