#include <stdio.h>
#include <stdint.h>

inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ (
      "xorl %%eax, %%eax\n"
      "cpuid\n"
      "rdtsc\n"
      : "=a" (lo), "=d" (hi)
      :
      : "%ebx", "%ecx");
    return (uint64_t)hi << 32 | lo;
}

main()
{
    unsigned long long x;
    unsigned long long y;
    x = rdtsc();
    printf("%lld\n",x);
    y = rdtsc();
    printf("%lld\n",y);
    printf("it took this long to call printf: %lld\n",y-x);
}