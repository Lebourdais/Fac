import List
import Intervalle

prefixes (h:t) = [] : (map (h:) (prefixes t))
prefixes [] = [[]]


main = do
  print $ "Test pour liste [1,3,5]"
  print $ "Somme liste = " ++ show(somme [1,3,5])
  print $ "Produit liste = " ++ show(produit [1,3,5])
  print $ "Longueur liste = " ++ show(longueur [1,3,5])
  print $ "Insertion de 2 liste = " ++ show(insertion 2 [1,3,5] )
  print $ "tri liste [3,1,5] = "
  print $ tri [3,1,5]
  print $ "concatenate liste [1,3,5] + [6,7,8] = "
  print $ concatenate [1,3,5] [6,7,8]
  print $ "inverse [1,3,5]"
  print $ inverse [1,3,5]
  print $ "Maximum de la liste = " ++ show(maxi [1,3,5])
  print $ "2 Maximum de la liste = " ++ show(maxi_deux [1,3,5,8,4,9])
  print $ "Max 3 = "++ show(maxi_trois [1,3,5,8,4,9])
  print $ "Fin LISTES"
  print $ "Intervalle croissant entre 1 et 20 = "++ show(intervalle_asc 1 20)
  print $ "Intervalle decroissant entre 20 et 1 = "++ show(intervalle_desc 20 1)
