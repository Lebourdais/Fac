import Fonction2

main = do
  print $ "somme des entiers de 0 a 100 = " ++ show(somme(100))
  print $ "Factorielle non terminale de 5 = " ++ show(fact(5))
  print $ "Nombre d'appels effectues = " ++ show(fac1_cpt(5))
  print $ "Factorielle terminale de 5 = " ++ show(fact2(5))
  print $ "Nombre d'appels effectues = " ++ show(fact2_cpt(5))
  print $ "5 Est une puissance de 2 = " ++ show(pow2_test(5))
  print $ "8 Est une puissance de 2 = " ++ show(pow2_test(8))
  print $ "Melange de 2 paquets de 3 cartes = " ++ show((shuffle 3 3))
  print $ "8 * 9 = " ++ show(multiplication_russe(8,9))
  print $ "0 * 9 = " ++ show(multiplication_russe(0,9))
  print $ "Ackermann de 3 3 = " ++ show(ackermann(3,3))
  print $ "f91 de 5 = " ++ show(f91(5))
  print $ "f91 de 80 = " ++ show(f91(80))
  print $ " 3 ->-> 2 = " ++ show(fleche(3,2,2))
  print $ " 3 ->-> 3 = " ++ show(fleche(3,3,2))

