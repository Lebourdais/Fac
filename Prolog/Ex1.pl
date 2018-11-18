cool(yolanda).
ecoute2LaMusique(mia).
ecoute2LaMusique(yolanda):-cool(yolanda).
joueAirGuitar(mia):-ecoute2LaMusique(mia).
joueAirGuitar(yolanda):-ecoute2LaMusique(yolanda).

/*
cool(yolanda).
  true

cool(hop).
  false
ecoute2LaMusique(butch).
  false
cool(X).
  X=yolanda
joueAirGuitar(X).
  X=mia;
  X=yolanda

mia = mia.
  true
mia = vincent.
  false
mia = X.
  X = mia.
X=mia, X=vincent.
  false
k(s(g),Y)=k(X,t(k)).
  Y = t(k),
  X = s(g).
k(s(g),t(k)) = k(X,t(Y)).
  X=s(g),
  Y=k.
*/
