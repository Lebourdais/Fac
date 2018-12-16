module Fonction4 where

-- Question 1
somme (h:t)
  |t == [] = h
  |otherwise = h + somme t;

produit (h:t)
  |t == [] = h
  |otherwise = h * produit t;

longueur (h:t)
  |t == [] = 1
  |otherwise = 1 + longueur t;

insertion x [] = [x]
insertion x (h:t)
  |x < h = x:h:t
  |otherwise=h : (insertion x t);

tri []=[];
tri (h:t) = insertion h (tri t);

concatenate l1 l2 = l1++l2;
inverse [] = [];
inverse (h:t) = inverse t ++ [h]

-- Question 2
maxi [h] = h
maxi (h:t)
 | (maxi t) > h = maxi t
 | otherwise = h;

is_max x l = (maxi l) == x
maxi_deux l = ((maxi l),maxi (filter ( \x -> x `elem` l && x /= maxi l) l ))
maxi_trois l = (max1,max2,max3)
  where
    max1 = (maxi l)
    max2 = maxi (filter ( \x -> x `elem` l && x /= max1) l )
    max3 = maxi (filter ( \x -> x `elem` l && x /= max1 && x /= max2) l )

-- Question 3

intervalle_asc inf sup = [inf..sup];
intervalle_desc sup inf = inverse [inf..sup];

-- Question 4
prefixes (h:t) = [] : (map (h:) (prefixes t))
prefixes [] = [[]]

-- Question 5

inferieur l [] = False
inferieur [] l = True
inferieur (h:t) (y:ys)
  |t==[] && ys==[] && h==y = False
  |(h:t)==(y:ys)=False
  |h < y = True
  |h > y = False
  |otherwise = inferieur t ys;

conjugue l n
    |n==1 = l
    |otherwise = conjugue ((drop 1 l)++[l!!0]) (n-1)

lyndon l =  lyndontemp l taille
  where
  taille = longueur l

lyndontemp l t
  |t == 1 = True
  |not(inferieur l (conjugue l t)) = False
  |otherwise =lyndontemp l (t-1);

insertgen x [] inf = [x]
insertgen x (h:t) inf
  |inf x h = x:h:t
  |otherwise = h : (insertgen x t inf)

insere_liste [] [] = []
insere_liste (h:t) l
  | t == [] = insertgen h l inferieur
  | h `elem` l = insere_liste t l
  | otherwise = insere_liste t (insertgen h l inferieur)

fusion_liste l l2 =
  let conclist1 = [m1 ++ m2 | m1 <- l, m2 <- l2] in
  let conclist2 = [m1 ++ m2 | m1 <- l2, m2 <- l] in
  let conclist = conclist1 ++ conclist2 in
  filter ( \x -> lyndon x ) conclist

suppdoublon [] = []
suppdoublon (h:t) = h : filter (/= h) (suppdoublon t)

genere n = suppdoublon (genere_ n)
genere_ n
  |n==1 = ["0","1"]
  |otherwise = generetemp 1 (n-1)
generetemp n f
  |f==0 = []
  |otherwise = (generetemp (n+1) (f-1)) ++ (fusion_liste (genere_ n) (genere_ f))
