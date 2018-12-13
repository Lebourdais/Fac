module Tree where

  data Tree a = Noeud a (Tree a) (Tree a)
                |Feuille
                 deriving Show


  hauteur Feuille = 0
  hauteur (Noeud _  gauche droite) = 1 + max (hauteur gauche) (hauteur droite)

  feuilles Feuille = 1
  feuilles (Noeud _  gauche droite) = feuilles gauche + feuilles droite
  creation_list_prefix Feuille = []
  creation_list_prefix (Noeud elt gauche droite) = [elt]++(creation_list_prefix gauche)++(creation_list_prefix droite)
  creation_list_infix Feuille = []
  creation_list_infix (Noeud elt gauche droite) = (creation_list_prefix gauche)++[elt]++(creation_list_prefix droite)
  creation_list_postfix Feuille = []
  creation_list_postfix (Noeud elt gauche droite) = (creation_list_prefix gauche)++(creation_list_prefix droite)++[elt]

  affichage_arbre a = affiche_temp a 2

  print_space x
    |x == 0 = ""
    |otherwise = " "++print_space (x-1)
  affiche_temp Feuille prof = putStr ""
  affiche_temp (Noeud elt gauche droite) prof = do
     print $ ((print_space (prof-2)) ++ "|--" ++ show(elt))
     (affiche_temp gauche (prof+3))
     (affiche_temp droite (prof+3))
