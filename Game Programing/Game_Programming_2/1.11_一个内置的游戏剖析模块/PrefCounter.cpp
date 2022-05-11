#include"PrefCounter.h"

#include<windows.h>
#include<stdio.h>

void pref_time(PrefTime *p_pref_time){
    *p_pref_time = GetTickCount();
}
//void pref_time_tick(PrefTime *p_pref_time){
//    PrefTick tick;
//    pref_tick(&tick);
//    tick_to_time(&tick, p_pref_time);
//}
//void pref_tick(PrefTick* p){
//    //DWORD dwLow, dwHigh;
//    __asm {
//        cpuid
//        rdtsc
//        shl     rdx, 32
//        or      rax, rdx
//    }
//    //*p_pref_tick = (PrefTick)( ((DWORD64)dwHigh << 32) | ((DWORD64)dwLow) );
//}
//#define PREF_COUNTER_DELTA_TIME 4000
//void tick_to_time(const PrefTick *p_pref_tick, PrefTime *p_pref_time){
//    static PrefTick d_tick = 0;
//    if(d_tick == 0){
//        PrefTime s=0, e=0;
//        PrefTick t0=0, t1=0;
//        pref_tick(&t0);
//        pref_time(&s);
//        do{
//            pref_time(&e);
//        }while(e<s+PREF_COUNTER_DELTA_TIME);
//        pref_tick(&t1);
//        d_tick = t1 - t0;
//    }
//    //printf("tick: %llu d_tick: %llu double: %f ", *p_pref_tick, d_tick, (double)*p_pref_tick * PREF_COUNTER_DELTA_TIME / d_tick + 0.5);
//    *p_pref_time = (PrefTime)( (double)*p_pref_tick * PREF_COUNTER_DELTA_TIME / d_tick + 0.5 );
//}