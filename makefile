exe: plateau.o joueur.o affichage.o main.o
	@echo "Compilation de l'exécutable."
	gcc affichage.o plateau.o joueur.o main.o -o labyrinthe.exe

affichage.o: affichage.c affichage.h
	@echo "Compilation de affichage."
	gcc -c -Wall affichage.c -o affichage.o

plateau.o: plateau.c plateau.h
	@echo "Compilation de plateau."
	gcc -c -Wall plateau.c -o plateau.o

joueur.o: joueur.c joueur.h
	@echo "Compilation de joueur."
	gcc -c -Wall joueur.c -o joueur.o

main.o: main.c plateau.h joueur.h affichage.h
	@echo "Compilation du main."
	gcc -c -Wall main.c -o main.o

clean:
	@echo "J'ai tout effacé."
	rm -f *.o
