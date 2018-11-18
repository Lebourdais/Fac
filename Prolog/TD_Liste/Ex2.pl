
sport(football).
sport(tennis).
sport(natation).

couleur(blanche).
couleur(bleu).
couleur(verte).

pays(anglais).
pays(espagnol).
pays(francais).

emplacement(1).
emplacement(2).
emplacement(3).

couple(E,C,N,S):-
  couple(place(1),couleur(C),pays(N),sport(tennis)),
  couple(place(E),couleur(verte),pays(_),sport(natation)),
  couple(place(_),couleur(blanche),pays(anglais),sport(S)).
