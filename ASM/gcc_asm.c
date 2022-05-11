#include<stdio.h>

int main(){
    int result = 0;
    int input = 1;
    asm volatile (
        "mov %1, %0\n"
        : "=r"(result)
        : "r"(input)
    );
    printf("result = %d\n", result);
    printf("input = %d\n", input);
}