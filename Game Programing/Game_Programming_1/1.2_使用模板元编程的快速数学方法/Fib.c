#include"Fib.h"

#include<assert.h>

unsigned RecursiveFib(unsigned n)
{
    if( n<=1 )
        return 1;
    return RecursiveFib( n-2 ) + RecursiveFib( n-1 );
}
unsigned cache_n_1, cache_n_2;
unsigned CacheFib(unsigned n){
    if( n<=1 )
        return 1;
    cache_n_2 = CacheFib(n-2);
    if( n > 3)
        cache_n_1 = cache_n_2 + cache_n_1;
    else
        cache_n_1 = CacheFib(n-1);
    return cache_n_2 + cache_n_1;
}