#ifndef PREF_COUNTER__
#define PREF_COUNTER__
#include<windows.h>
typedef DWORD PrefTime;
typedef unsigned __int64 PrefTick;
void pref_time(PrefTime *);
void pref_time_tick(PrefTime *);
void tick_to_time(const PrefTick*, PrefTime *);
#endif