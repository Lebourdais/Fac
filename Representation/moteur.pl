:-use_module(tictactoe).


campCPU(x).

% coordonneesOuListe(NomCol, NumLigne, Liste).
% ?- coordonneesOuListe(a, 2, [a,2]).
% true.
coordonneesOuListe(NomCol, NumLigne, [NomCol, NumLigne]).


% duneListeALautre(LC1, Case, LC2)
% ?- duneListeALautre([[a,1],[a,2],[a,3]], [a,2], [[a,1],[a,3]]). est vrai
duneListeALautre([A|B], A, B).
duneListeALautre([A|B], C, [A|D]):- duneListeALautre(B,C,D).


%Joue le coup demandé

coupJoueDansLigne(a, Val, [-|Reste],[Val|Reste]).
coupJoueDansLigne(NomCol, Val, [X|Reste1],[X|Reste2]):-
		display:succAlpha(I,NomCol),
		coupJoueDansLigne(I, Val, Reste1, Reste2).

coupJoueDansGrille(NCol,1,Val,[A|Reste],[B|Reste]):- coupJoueDansLigne(NCol, Val, A, B).
coupJoueDansGrille(NCol, NLig, Val, [X|Reste1], [X|Reste2]):- display:succNum(I, NLig),
					coupJoueDansGrille(NCol, I, Val, Reste1, Reste2).

% toutesLesCasesValides(Grille, LC1, C, LC2).
% Se verifie si l'on peut jouer dans la case C de Grille et que la liste
% LC1 est une liste composee de toutes les cases de LC2 et de C.
% Permet de dire si la case C est une case ou l'on peut jouer, en evitant
% de jouer deux fois dans la meme case.
toutesLesCasesValides(Grille, LC1, C, LC2) :-
	coordonneesOuListe(Col, Lig, C),
	regles:leCoupEstValide(Col, Lig, Grille),
	duneListeALautre(LC1, C, LC2).

joueLeCoup(Case, Valeur, GrilleDep, GrilleArr) :-
	coordonneesOuListe(Col, Lig, Case),
	regles:leCoupEstValide(Col, Lig, GrilleDep),
	coupJoueDansGrille(Col, Lig, Valeur, GrilleDep, GrilleArr),
	nl, display:affichage(GrilleArr), nl.

saisieUnCoup(NomCol,NumLig) :-
	writeln("entrez le nom de la colonne a jouer (a,b,c,...) :"),
	read(NomCol), nl,
	writeln("entrez le numero de ligne a jouer (1, 2, 3,...) :"),
	read(NumLig),nl.

moteur(Grille,_,Camp):-
	regles:partieGagnee(Camp, Grille), nl,
	write('le camp '), write(Camp), write(' a gagne').

% cas gagnant pour le joueur adverse
moteur(Grille,_,Camp):-
	regles:adversaire(CampGagnant, Camp),
	regles:partieGagnee(CampGagnant, Grille), nl,
	write('le camp '), write(CampGagnant), write(' a gagne').

% cas de match nul, plus de coups jouables possibles
moteur(_,[],_) :-nl, write('game over').

% cas ou l ordinateur doit jouer
moteur(Grille, [Premier|ListeCoupsNew], Camp) :-
	campCPU(Camp),
	joueLeCoup(Premier, Camp, Grille, GrilleArr),
	regles:adversaire(AutreCamp, Camp),
	moteur(GrilleArr, ListeCoupsNew, AutreCamp).

% cas ou c est l utilisateur qui joue
moteur(Grille, ListeCoups, Camp) :-
	campCPU(CPU),
	regles:adversaire(Camp, CPU),
	saisieUnCoup(Col,Lig),
	joueLeCoup([Col,Lig], Camp, Grille, GrilleArr),
	toutesLesCasesValides(Grille, ListeCoups, [Col, Lig], ListeCoupsNew),
	moteur(GrilleArr, ListeCoupsNew, CPU).

%implementation du minmax

/*
Il faut définire les fonctions suivantes pour chaque jeu

    move(+Pos, -NextPos) : states that NextPos is a legal move from Pos
    utility(+Pos, -Val) : states that Pos as a value equal to Val
    min_to_move(+Pos) : states that the current player in Pos is min
    max_to_move(+Pos) : states that the current player in Pos is max

*/

lanceJeu:-
  regles:grilleDeDepart(G),
	regles:toutesLesCasesDepart(ListeCoups),
	display:affichage(G),nl,
  writeln("L ordinateur est les x et vous etes les o."),
  writeln("Quel camp doit debuter la partie ? "),read(Camp),
	regles:toutesLesCasesDepart(ListeCoups),
	moteur(G,ListeCoups,Camp).
