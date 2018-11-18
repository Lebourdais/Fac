color(vert).
color(jaune).
color(rouge).
coloriage(C1,C2,C3,C4):-
  color(C1),
  color(C2),
  C1 \== C2,
  color(C3),
  C1 \== C3,
  C2 \== C3,
  color(C4),
  C1 \== C4,
  C3 \== C4.

choix1(1):- coloriage(C1,C2,C3,C4),write("C1 = "),write(C1),write(", C2 = "),write(C2 ),write(", C3 = "), write(C3 ),write(", C4 = "), write(C4 ), nl.
choix1(2):- write("Vous êtes chiant !"),nl,
            write("Quelle case souhaitez vous prendre ?"),nl,
            write("1- C1"),nl,
            write("2- C2"),nl,
            write("3- C3"),nl,
            write("4- C4"),nl,
            write("5- Abort"),nl,
            read(X),choix2(X).
choix2(1):- write("Vous avez choisi la case C1:"),nl,
            write("Quelle couleur souhaitez vous ?(en lettre)"),nl,
            write("- vert"),nl,
            write("- jaune"),nl,
            write("- rouge"),nl,
            write("- abort"),nl,
            read(X),run(X,1).
choix2(2):- write("Vous avez choisi la case C2:"),nl,
            write("Quelle couleur souhaitez vous ?(en lettre)"),nl,
            write("- vert"),nl,
            write("- jaune"),nl,
            write("- rouge"),nl,
            write("- abort"),nl,
            read(X),run(X,2).
choix2(3):- write("Vous avez choisi la case C3:"),nl,
            write("Quelle couleur souhaitez vous ?(en lettre)"),nl,
            write("- vert"),nl,
            write("- jaune"),nl,
            write("- rouge"),nl,
            write("- abort"),nl,
            read(X),run(X,3).
choix2(4):- write("Vous avez choisi la case C4:"),nl,
            write("Quelle couleur souhaitez vous ?(en lettre)"),nl,
            write("- vert"),nl,
            write("- jaune"),nl,
            write("- rouge"),nl,
            write("- abort"),nl,
            read(X),run(X,4).
choix2(5):- menu.
run(abort,_):-menu.
run(X,4):- coloriage(C1,C2,C3,X),write("C1 = "),write(C1 ),write(" "),write(", C2 = "), write(C2 ),write(" "), write(", C3 = "),write(C3 ), nl.
run(X,3):- coloriage(C1,C2,X,C4),write("C1 = "),write(C1 ),write(" "),write(", C2 = "), write(C2 ),write(" "),write(", C4 = "), write(C4 ), nl.
run(X,2):- coloriage(C1,X,C3,C4),write("C1 = "),write(C1 ),write(" "),write(", C3 = "), write(C3 ),write(" "),write(", C4 = "), write(C4 ), nl.
run(X,1):- coloriage(X,C2,C3,C4),write("C2 = "),write(C2 ),write(" "),write(", C3 = "), write(C3 ),write(" "),write(", C4 = "), write(C4 ), nl.
menu():- write("Choisissez un numéro de la liste"),nl,
        write("1- Laisser faire le système"),nl,
        write("2- imposer une couleur"),nl,
        read(X),choix1(X).
