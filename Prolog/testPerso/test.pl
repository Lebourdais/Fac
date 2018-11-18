animal(chat).
animal(cheval).
animal(poisson).

maison(chateau).
maison(studio).
maison(pavillon).

relation(max,M,chat):-maison(M).
relation(luc,studio,A):-
  A\==cheval,
  animal(A).

relation(eric,M,A):-
  animal(A),
  maison(M),
  M\==pavillon.

different(X,X,_):-!,fail.
different(X,_,X):-!,fail.
different(_,X,X):-!,fail.
different(_,_,_).

resoudre(MMax,MEric,AEric,ALuc):-
  relation(max,MMax,chat),
  relation(eric,MEric,AEric),
  different(MMax,MEric,studio),
  relation(luc,studio,ALuc),
  different(chat,AEric,ALuc).
