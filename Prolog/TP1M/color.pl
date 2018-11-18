couleur(vert).
couleur(jaune).
couleur(rouge).


coloriage(C1,C2,C3,C4):-
  couleur(C1),couleur(C2),couleur(C3),couleur(C4),
  C1 \== C2, C1 \== C3, C1 \== C4,
  C2 \== C3,
  C3 \== C4.

menu :-
    write('                          '),nl,
    write('   1. choisir une couleur à une position  '),nl,
    write('   2. coloriage automatique  '),nl,
    write('   Il ne faut pas oublier le point après'),nl
    write('                          '),nl,
    write('===>'),nl,
    read(X), choice(X).

    choice(1) :- menucolo(),nl.
    choice(2) :- coloriage(C1,C2,C3,C4), write(C1 ),write(" "), write(C2 ),write(" "), write(C3 ),write(" "), write(C4 ), nl.

menucolo :-
  write("                              "),nl,
  write("   Entrez le nom de la couleur    "),nl,
  write('                          '),nl,
  write('===>'),nl,
  read(X),menucolo2(X).

menucolo2(X):-couleur(X),
  write('                          '),nl,
  write('   Entrez sa position (1,2,3,4)  '),nl,
  write('                          '),nl,
  write('===>'),nl,
  read(Y),colorier(X,Y).

colorier(X,1):-
  coloriage(X,C2,C3,C4), write(X ),write(" "), write(C2 ),write(" "), write(C3 ),write(" "), write(C4 ), nl.

colorier(X,2):-
  coloriage(C1,X,C3,C4), write(C1 ),write(" "), write(X ),write(" "), write(C3 ),write(" "), write(C4 ), nl.

colorier(X,3):-
  coloriage(C1,C2,X,C4), write(C1 ),write(" "), write(C2 ),write(" "), write(X ),write(" "), write(C4 ), nl.

colorier(X,4):-
  coloriage(C1,C2,C3,X), write(C1 ),write(" "), write(C2 ),write(" "), write(C3 ),write(" "), write(X ), nl.
