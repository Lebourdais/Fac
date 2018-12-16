module Fonction2 where
-- Q1
somme(n)
  | n == 0 = 0
  |otherwise = n+somme(n-1);

-- Q2

fibolist = 0 : 1 : zipWith (+) fibolist (tail fibolist)
fibomarrante n = fibolist!!n

fib(n)
  | n == 0 = 0
  | n == 1 = 1
  | otherwise = fib (n-1) + fib (n-2);

-- Fonction qui teste si un nombre est puissance de 2
pow2_test(n)
    | n == 1 = True
    | (n `mod` 2) == 1 = False
    | otherwise = pow2_test(n `div` 2)

fact(n)
  | n == 0 = 1
  |otherwise = n*fact(n-1);

fac1_cpt(n)
  | n == 0 = 0
  |otherwise = 1+(fac1_cpt(n-1));


fact2(n)=fact2t(n,1);

fact2t(n,acc)
  | n == 1 = acc
  | otherwise = fact2t(n-1 , n*acc);

fact2_cpt(n) = fact2_cptemp(n,0);

fact2_cptemp(n,acc)
  | n == 1 = acc
  | otherwise = fact2t(n-1,1+acc)

shuffle n1 n2
 | n1 == 1 = n2+1
 | n2 == 1 = n1+1
 | otherwise = (shuffle (n1-1) (n2)) + (shuffle (n1) (n2-1))

-- multiplication_russe::(Int,Int)->Int
multiplication_russe(x,y)
  | (x==0 || y==0) = 0
  | (x `mod` 2 == 0) = (x `div` 2)*(2*y)
  | otherwise = ((x-1) `div` 2)*(2*y) +y;

ackermann(m,n)
  | m==0 = n+1
  | m>0 && n==0 = ackermann(m-1,1)
  | otherwise = ackermann(m-1,ackermann(m,n-1));

f91(n)
  | n>100 = n-10
  | n<=100 = f91(f91(n+11));

fleche(a,b,n)
  | n == 1 = a**b
  | b == 0 = 1
  | otherwise = fleche(a,fleche(a,b-1,n),n-1)
