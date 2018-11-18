% Devant est le danger, le salut est derrière.
% Deux sauront parmi nous conduire à la lumière,
% L’une d’entre les sept en avant te protège,
% Et une autre en arrière abolira le piège,
% Deux ne pourront t’offrir que simple vin d’ortie,
% Trois sont mortels poisons, promesse d’agonie,
% Choisis, si tu veux fuir un éternel supplice,
% Pour t’aider dans ce choix, tu auras quatre indices.
% Le premier : si rusée que soit leur perfidie,
% Les poisons sont à gauche des deux vins d’ortie,
% Le second : différente à chaque extrémité,
% Si tu vas de l’avant, nulle n’est ton alliée.
% Le troisième : elles sont de tailles inégales,
% Ni naine ni géante en son sein n’est fatale.
% Quatre enfin : les deuxièmes, à gauche comme à droite,
% Sont jumelles de goût, mais d’aspect disparates.
occurrence([],_,0).
occurrence([X|L],X,N) :- occurrence(L,X,N1),N is N1+1.
occurrence([Y|L],X,N) :- X\==Y,occurrence(L,X,N).
vin(vin).
poison(poison).
avant(avant).
arriere(arriere).
rightof(A,B,A|[B|_]).
rightof(A,B,_|T):-rightof(A,B,T).
potion(P):-member(P,[vin,poison,avant,arriere]).
potions([A,B,C,D,E,F,G]):-
  potion(A),
  potion(B),
  potion(C),
  potion(D),
  potion(E),
  potion(F),
  potion(G),
  avant(H),
  arriere(I),
  A \= H,
  A \= G,
  B == F,
  vin(Y),
  poison(X),
  occurrence([A,B,C,D,E,F,G],X,3),
  occurrence([A,B,C,D,E,F,G],Y,2),
  occurrence([A,B,C,D,E,F,G],H,1),
  occurrence([A,B,C,D,E,F,G],I,1),
  nextto(X,Y,[A,B,C,D,E,F,G]).
