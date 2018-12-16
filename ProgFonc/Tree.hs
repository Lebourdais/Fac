module Tree where

  data Tree a = Noeud a (Tree a) (Tree a)
                |Feuille
                 deriving Show


  hauteur Feuille = 0
  hauteur (Noeud _  gauche droite) = 1 + max (hauteur gauche) (hauteur droite)

  feuilles Feuille = 0
  feuilles (Noeud _ Feuille Feuille) = 1
  feuilles (Noeud _ g d) = feuilles g + feuilles d

  creation_list_prefix Feuille = []
  creation_list_prefix (Noeud elt gauche droite) = [elt]++(creation_list_prefix gauche)++(creation_list_prefix droite)
  creation_list_infix Feuille = []
  creation_list_infix (Noeud elt gauche droite) = (creation_list_infix gauche)++[elt]++(creation_list_infix droite)
  creation_list_postfix Feuille = []
  creation_list_postfix (Noeud elt gauche droite) = (creation_list_postfix gauche)++(creation_list_postfix droite)++[elt]

  affichage_arbre a = affiche_temp a 2

  print_space x
    |x == 0 = ""
    |otherwise = " "++print_space (x-1)
  affiche_temp Feuille prof = putStr ""
  affiche_temp (Noeud elt gauche droite) prof = do
     print $ ((print_space (prof-2)) ++ "|--" ++ show(elt))
     (affiche_temp gauche (prof+3))
     (affiche_temp droite (prof+3))

  croissant [x] = True
  croissant (x:xs) = x <= head (xs) && croissant xs

  bst_bien_forme a = croissant (creation_list_infix a)

  bst_insere x Feuille = (Noeud x Feuille Feuille)
  bst_insere x (Noeud elt gauche droite)
    |x<elt = (Noeud elt (bst_insere x gauche) droite)
    |otherwise = (Noeud elt gauche (bst_insere x droite))

  bst_listToAbr [] = Feuille
  bst_listToAbr (h:t) = bst_listToAbr_ (Noeud h Feuille Feuille) t

  bst_listToAbr_ a [] = a
  bst_listToAbr_ a (h:t) = bst_listToAbr_ (bst_insere h a ) t

  bst_abrToList a = creation_list_infix a

  bst_tri l = bst_abrToList (bst_listToAbr l)

  est_feuilles (Noeud _ Feuille Feuille) = True
  est_feuilles (Noeud _ gauche droite)= not(est_feuilles gauche) || not(est_feuilles droite)

  tas_bien_forme Feuille = True

  tas_bien_forme (Noeud elt gauche droite)
    |((est_feuilles gauche) && (elt > eltgauche)) = False
    |((est_feuilles droite) && (elt > eltdroit)) = False
    |otherwise = (tas_bien_forme gauche) && (tas_bien_forme droite)
    where
      (Noeud eltgauche ggauche gdroite)=gauche
      (Noeud eltdroit dgauche ddroite)=droite
