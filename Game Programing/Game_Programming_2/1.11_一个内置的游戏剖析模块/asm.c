//
//extern void pref_tick();
//int main() {
//	pref_tick();
//}
//void test_counting_tick_times(const DWORD BLOCK_TIME){
//    PrefTick tick0=0, tick1=0, tick_diff=0;
//    PrefTime tick_to_time_val=0;
//    DWORD tStart=0, tEnd=0;
//    // count tick --
//    pref_tick(&tick0);
//    tStart = GetTickCount();
//    while( (tEnd=GetTickCount()) < tStart+BLOCK_TIME );//Block in a certain time.
//    pref_tick(&tick1);
//    // -- count tick
//    tick_diff=tick1-tick0;
//    tick_to_time( &tick_diff, &tick_to_time_val ); 
//    printf("elapsed time: %d tick_to_time_val: %d\n", tEnd - tStart, tick_to_time_val);
//    assert(abs(tick_to_time_val - tEnd + tStart) * 100.0 / (tEnd - tStart) <=1.0 && "test_counting_tick_times(): failed");
//    printf("Passed test_counting_tick_times(%d)\n", BLOCK_TIME);
//}
//
//void test_timing(const DWORD BLOCK_TIME){
//    DWORD tStart=0, tEnd=0;
//    PrefTime time0=0, time1=0;
//    // count time --
//    pref_time(&time0);
//    tStart = GetTickCount();
//    while( (tEnd=GetTickCount()) < tStart+BLOCK_TIME );//Block in a certain time.
//    pref_time(&time1);
//    // -- count time
//    printf("elapsed time: %d time: %d\n", tEnd - tStart, time1 - time0);
//    assert(abs(time1 - time0 - tEnd + tStart) * 100.0 / (tEnd - tStart) <=1.0 && "test_pref_time(): failed");
//    printf("Passed test_timing(%d)\n", BLOCK_TIME);
//}


//void test_compare_pref_time(int c) {
//    PrefTime t; PrefTick tk;
//    DWORD tStart = 0, tEnd = 0;
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
//    PrefTime t; PrefTick tk;
//    DWORD tStart = 0, tEnd = 0;
//    //=================================================
//    {
//        c = 100000000;
//        tStart = GetTickCount();
//        while (c--) {
//            pref_tick();
//        }
//        tEnd = GetTickCount();
//        printf("pref_time_tick - time: %d\n", tEnd - tStart);
//    }
//}