byCar(auckland,hamilton).
byCar(hamilton,raglan).
byCar(valmont,saarbruecken).
byCar(valmont,metz).
byTrain(metz,frankfurt).
byTrain(saarbruecken,frankfurt).
byTrain(metz,paris).
byTrain(saarbruecken,paris).
byPlane(frankfurt,bangkok).
byPlane(frankfurt,singapore).
byPlane(paris,losAngeles).
byPlane(bangkok,auckland).
byPlane(singapore,auckland).
byPlane(losAngeles,auckland).


voyage(X, Y) :- byCar(X, Y); byTrain(X, Y); byPlane(X, Y).
voyage(X, Y) :- voyage(X, Z),(byTrain(Z, Y); byCar(Z, Y);byPlane(Z, Y)).

voyage(X, Y, byCar(X, Y)) :- byCar(X, Y).
voyage(X, Y, byTrain(X, Y)) :- byTrain(X, Y).
voyage(X, Y, byPlane(X, Y)) :- byPlane(X, Y).

voyage(X, Y, byCar(X, Z, Res)) :- byCar(X, Z) , voyage(Z, Y, Res).
voyage(X, Y, byTrain(X, Z, Res)) :- byTrain(X, Z), voyage(Z, Y, Res).
voyage(X, Y, byPlane(X, Z, Res)) :- byPlane(X, Z), voyage(Z, Y, Res).
