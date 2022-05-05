#include <iostream>
#include "lectures.h"
#include "homeworks.h"
#include "phases.h"
#include "practice.h"
#include <set>


void lectures()
{
//    lec_1();
//    lec_2();
//    lec_3();
//    order_main();
//    orderbook_main();
//    lec_4();
//    vector_main();
//    curious_main();
//    rev_set_main();
    lec_5_order_main();
}

void homeworks()
{
//    std::cout << pthFactor(22876792454961, 28) << '\n'; // hw1.1
//    for (int i{0}; i<32; ++i) std::cout << arr[i] << ',';
//    std::cout << countPalindromes("abba") << '\n';
//    std::cout << countPowerNumbers(1, 1000000) << '\n';
//    isPossible(1,2,3,5);
    hw4_main();
}

void phases()
{
//    calculator(); // Phase 1
//    phase_3_main(); // phase 3 order book
    phase4_main();
}

void practice()
{
//    int arr[32] {0};
//    factor(2147483648/2, arr, 0, 3);
//    selection_sort();
    merge_sort_main();
}

int main()
{
//    lectures();
//    homeworks();
    phases();
//    practice();
    return 0;
}
