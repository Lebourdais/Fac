import Tree

a = (Noeud 27
      (Noeud 12
        (Noeud 5 Feuille Feuille)
        (Noeud 19
          (Noeud 17 Feuille Feuille)
          (Noeud 24 Feuille Feuille)
        )
      )
      (Noeud 43
        (Noeud 36 Feuille Feuille)
        (Noeud 77 Feuille Feuille)
      )
    )
tas = (Noeud 8
        (Noeud 20
          (Noeud 21
            (Noeud 90 Feuille Feuille)
            (Noeud 22 Feuille Feuille)
          )
          (Noeud 80 Feuille
            (Noeud 81 Feuille Feuille)
          )
        )
        (Noeud 10
          (Noeud 12
            (Noeud 75 Feuille Feuille)
            (Noeud 20 Feuille Feuille)
          )
          (Noeud 11 (Noeud 80 Feuille Feuille) Feuille)
        )
      )
main = do
  affichage_arbre a
  print $ " infix de a = " ++ show(creation_list_infix a)
  print $ " A bien_forme = " ++ show(bst_bien_forme a)
  print $ "insertion de 42"
  affichage_arbre (bst_insere 42 a)
  print $ "Création de l'arbre a avec sa liste en prefixe"
  affichage_arbre (bst_listToAbr (creation_list_prefix a))
