module Fonction3 where
somme(n)
  | n == 0 = 0
  |otherwise = n+somme(n-1);

est_impair(x)
  | x `mod` 2 == 0 = False
  | otherwise = True;

somme_impaires(n) = somme_filtre n est_impair ;
switch(n)
  | n `mod` 2 == 0 = n
  | otherwise = -n;

somme2(n)
  | n == 0 = 0
  | otherwise = switch(n)+somme2(n-1);

inv100(x) = inv100temp(x,100);

inv100temp(x,n)
  | n == 0 = 1
  | otherwise = (1-x)**n + inv100temp(x,n-1);

somme_termes(nom_fonc,n) = nom_fonc(n);

pair(x)
  | x `mod` 2 == 0 = True
  | otherwise = False;

diviseur x y
  |x `mod` y == 0 = True
  |otherwise = False

somme_filtre n f
  | n == 0 = 0
  | f(n) = n+somme_filtre (n-1) f
  | otherwise = somme_filtre (n-1) f;


parfait(x)
  | somme_filtre x (diviseur x) `div` 2 == x = True
  | otherwise = False;

apply n f x
  | n == 1 = f(x)
  | otherwise = (apply (n-1) f (f(x)));

ftest(x) = x+1;
mult x y = x*y
power (x,n) = apply (n-1) (mult (x)) x;

exemple i j
  | (1<=i) && (i<=6) && (1<=j) && (j<=5) = (True,2*i+j)
  | otherwise = (False,0);

identite_6_5 i j
  | (1<=i) && (i<=6) && (1<=j) && (j<=5) && (i == j) = (True,1)
  | (1<=i) && (i<=6) && (1<=j) && (j<=5) = (True,0)
  | otherwise = (False,0)
identite_4_4 i j
  | (1<=i) && (i<=4) && (1<=j) && (j<=4) && (i == j) = (True,1)
  | (1<=i) && (i<=4) && (1<=j) && (j<=4) = (True,0)
  | otherwise = (False,0)

matrice_test_4_4 i j
  | (1<=i) && (i<=4) && (1<=j) && (j<=4) = (True,1)
  | otherwise = (False,0);

dims m = ((dimhor m 1),(dimvert m 1));

dimvert m j
  | m 1 j == (False,0) = j-1
  | otherwise = dimvert m (j+1);


dimhor m i
  | m i 1 == (False,0) = i-1
  | otherwise = dimhor m (i+1);

add_mat mat_A mat_B
  | (dims mat_A) /= (dims mat_B) = \i j -> (False,0)
  | otherwise = \i j -> if not((1>i) || (i>fst(dims mat_A)) || (1>j) || (j>snd(dims mat_A))) then (True,snd(mat_A i j) + snd(mat_B i j)) else (False,0);
