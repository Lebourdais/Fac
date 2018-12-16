import Fonction3
main = do
  print $ "Somme des entiers de 0 Ã  100 = " ++ show(somme(100))
  print $ "Somme des nombres impairs < 10 = "++ show(somme_impaires(10))
  print $ "Somme de 1-2+3-4+5-6+7...+99 =  "++ show(somme2(100))
  print $ "Resultat de (1-x)^0+(1-x)^1...+(1-x)^100 pour x = 0.5 = " ++ show(inv100(0.5))
  print $ "6 Est un nombre parfait = " ++ show(parfait(6))
  print $ "28 est un nombre parfait = " ++ show(parfait(28))
  print $ "8128 est un nombre parfait = " ++ show(parfait(8128))
  print $ "53 est un nombre parfait = " ++ show(parfait(53))
  print $ "f(f(f(f(f(x))))) avec f(x) = x+1 et x = 10 = " ++ show(apply 5 ftest 10)
  print $ "2 ^ 3 = " ++ show(power(2,3))
  print $ "Matrice exemple en 3 3 = " ++ show(exemple 3 3)
  print $ "Matrice identite en 2 2 = " ++ show(identite_4_4 2 2)
  print $ "Dimension d'une matrice 4x4 = " ++ show(dims identite_4_4)
  print $ "Addition de la matrice exemple et une matrice identite 4 * 4  :"
  print $ "resultat en 1 1 = " ++ show((add_mat identite_4_4 exemple) 1 1)
  print $ "Addition de la matrice exemple et une matrice identite 6 * 5  :"
  print $ "resultat en 1 1 = " ++ show((add_mat identite_6_5 exemple) 1 1)
  print $ "resultat en 2 1 = " ++ show((add_mat identite_6_5 exemple) 2 1)
  print $ "resultat en 5 3 = " ++ show((add_mat identite_6_5 exemple) 5 3)