f(a).
f(b).
g(a).
g(b).
h(b).

k(X):-f(X),g(X),h(X).

/*
  Call: (7) k(_G553) ? creep
  Call: (8) f(_G553) ? creep
  Exit: (8) f(a) ? creep
  Call: (8) g(a) ? creep
  Exit: (8) g(a) ? creep
  Call: (8) h(a) ? creep
--Fail: (8) h(a) ? creep -- Il ne trouve pas le h(a).
  Redo: (8) f(_G553) ? creep
  Exit: (8) f(b) ? creep
  Call: (8) g(b) ? creep
  Exit: (8) g(b) ? creep
  Call: (8) h(b) ? creep
  Exit: (8) h(b) ? creep
  Exit: (7) k(b) ? creep
X = b.


*/
