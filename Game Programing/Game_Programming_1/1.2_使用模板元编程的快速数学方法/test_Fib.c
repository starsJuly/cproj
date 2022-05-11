#include"Fib.h"

#include<assert.h>
#include<stdbool.h>
#include<Windows.h>
#include<stdio.h>

static void test_RecursiveFib(){
    unsigned val = RecursiveFib(0);
    assert(1 == val && "test_Fib(0)");
    val = RecursiveFib(1);
    assert(1 == val && "test_Fib(1)");
    val = RecursiveFib(2);
    assert(2 == val && "test_Fib(2)");
    val = RecursiveFib(3);
    assert(3 == val && "test_Fib(3)");
    val = RecursiveFib(4);
    assert(5 == val && "test_Fib(4)");
    val = RecursiveFib(5);
    assert(8 == val && "test_Fib(5)");
    val = RecursiveFib(6);
    assert(13 == val && "test_Fib(6)");
    //Test execution time of RecursiveFib:
    const int NUMTIMES = 44;
    __int64 timelist[NUMTIMES];
    unsigned vallist[NUMTIMES+2];
    vallist[0] = RecursiveFib(0);
    assert(vallist[0] == 1 && "test_RecursiveFib(): failed");
    vallist[1] = RecursiveFib(1);
    assert(vallist[1] == 1 && "test_RecursiveFib(): failed");
    for(int i=0; i < NUMTIMES ; ++i){
        timelist[i] = GetTickCount();
        //test code:
        vallist[i+2] = RecursiveFib(i+2);
        timelist[i] = GetTickCount() - timelist[i];

        assert(vallist[i+2] == vallist[i+1] + vallist[i] && "test_RecursiveFib(): failed");
        printf("\ncalc finished: %d", i+1);
    }
    printf("\ntest\t\tExecution Time\n");
    for(int i=0; i < NUMTIMES; ++i){
        printf("\n%-8d%9d ", i+1, timelist[i]);
    }
}



static void test_CacheFib(){
    unsigned val = CacheFib(0);
    assert(1 == val && "test_Fib(0)");
    val = CacheFib(1);
    assert(1 == val && "test_Fib(1)");
    val = CacheFib(2);
    assert(2 == val && "test_Fib(2)");
    val = CacheFib(3);
    assert(3 == val && "test_Fib(3)");
    val = CacheFib(4);
    assert(5 == val && "test_Fib(4)");
    val = CacheFib(5);
    assert(8 == val && "test_Fib(5)");
    val = CacheFib(6);
    assert(13 == val && "test_Fib(6)");
    //Test execution time of CacheFib:
    const int NUMTIMES = 256;
    __int64 timelist[NUMTIMES];
    unsigned vallist[NUMTIMES+2];
    vallist[0] = CacheFib(0);
    assert(vallist[0] == 1 && "test_CacheFib(): failed");
    vallist[1] = CacheFib(1);
    assert(vallist[1] == 1 && "test_CacheFib(): failed");
    for(int i=0; i < NUMTIMES ; ++i){
        timelist[i] = GetTickCount();
        //test code:
        vallist[i+2] = CacheFib(i+2);
        timelist[i] = GetTickCount() - timelist[i];

        assert(vallist[i+2] == vallist[i+1] + vallist[i] && "test_CacheFib(): failed");
        printf("\ncalc finished: %d", i+1);
    }
    printf("\ntest\t\tExecution Time\n");
    for(int i=0; i < NUMTIMES; ++i){
        printf("\n%-8d%9d ", i+1, timelist[i]);
    }
    printf("\nn\t\t\tValue\n");
    for(int i=0; i < NUMTIMES+2; ++i){
        printf("\n%-8d\t\t%u ", i, vallist[i]);
    }
}

int main(){
    test_RecursiveFib();
    test_CacheFib();
    printf("\nCacheFib: %u\n", CacheFib(47));
}