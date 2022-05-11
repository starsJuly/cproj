//#pragma warning(disable:28159)
//#include"PrefCounter.h"
//
//#include<stdio.h>
//#include<assert.h>
//#include<stdbool.h>
//#include<math.h>
//#include<windows.h>
//
//
//extern void pref_tick(PrefTick*);
//extern void pref_time_tick(PrefTick*, PrefTime*);
//double CPUSpeed()
//{
//    wchar_t Buffer[_MAX_PATH];
//    DWORD BufSize = _MAX_PATH;
//    DWORD dwMHz = _MAX_PATH;
//    HKEY hKey;
//
//    // open the key where the proc speed is hidden:
//    long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
//        L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
//        0,
//        KEY_READ,
//        &hKey);
//    if (lError != ERROR_SUCCESS)
//    {// if the key is not found, tell the user why:
//        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
//            NULL,
//            lError,
//            0,
//            Buffer,
//            _MAX_PATH,
//            0);
//        wprintf(Buffer);
//        return 0;
//    }
//
//    // query the key:
//    RegQueryValueEx(hKey, L"~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
//    return (double)dwMHz;
//}
//
//void test_compare_pref_time(int c){
//    PrefTime t;PrefTick tk;
//    DWORD tStart=0, tEnd=0;
//    //=================================================
//    {
//        c = 100000000;
//        tStart = GetTickCount();
//        while (c--) {
//            pref_time(&t);
//        }
//        tEnd = GetTickCount();
//        printf("pref_time - time: %i\n", tEnd - tStart);
//    }
//}
//void test_compare_pref_tick(int c) {
//    PrefTime t; PrefTick tk = 0xf12;
//    DWORD tStart = 0, tEnd = 0;
//    //=================================================
//    {
//        c = 100000000;
//        tStart = GetTickCount();
//        while (c--) {
//            pref_time_tick(&tk, &t);
//        }
//        tEnd = GetTickCount();
//        printf("pref_time_tick - time: %d\n", tEnd - tStart);
//    }
//}
//
//int main(){
//    PrefTick pft = 0;
//    PrefTick* ppft = &pft;
//    *ppft = 5;
//    //tick_to_time(&pft, (PrefTime*)&pft);
//    //test_timing(4000);
//    //test_timing(2000);
//    //test_counting_tick_times(4000);
//    //test_counting_tick_times(2000);
//    double cpuspeed = CPUSpeed();
//    PrefTick t0=0, t1=0;
//    pref_tick(&t0);
//    Sleep(2000);
//    pref_tick(&t1);
//    printf("time: %f\n", (t1 - t0)/cpuspeed/1000000);
//    test_compare_pref_time(10000000);
//    test_compare_pref_tick(10000000);
//    return 0;
//}