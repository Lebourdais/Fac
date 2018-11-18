my_last(X,[X|_],0).

my_last(X,[_|T],M):-
    my_last(X,T,N),
    N is M-1.
