module List where

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

  
