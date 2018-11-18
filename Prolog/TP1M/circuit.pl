not(0,1).
not(1,0).

xor(0,1,1).
xor(1,0,1).
xor(A,A,0).

nand(0,0,1).
nand(1,1,0).
nand(0,1,0).
nand(1,0,0).

circuit(X,Y,Z):-
  nand(X,Y,S1),not(X,S2),xor(S1,S2,S3),not(S3,Z).
