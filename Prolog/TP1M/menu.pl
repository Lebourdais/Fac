entree(crudites).
entree(terrine).
entree(melon).

/*Les viandes (avec légumes)*/
viande(steack).
viande(poulet).
viande(gigot).

/*Les Poissons (avec légumes)*/
poisson(bar).
poisson(saumon).

/*Les desserts*/
dessert(sorbet).
dessert(creme).
dessert(tarte).

menu_simple(E,P,D) :- entree(E), plat(P), dessert(D).

plat(P) :- viande(P).
plat(P) :- poisson(P).
