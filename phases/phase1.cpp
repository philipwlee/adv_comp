#include<iostream>
#include<climits>


template <typename T>
void verify(T ret, T sol)
{
    if (ret==sol) std::cout << "PASS";
    else std::cout << ret << "!=" << sol;
}

void verify(long* retarr, long* solarr, int sz)
{
    bool matches {true};
    for (int i {0}; i<sz; ++i) matches = matches && (retarr[i]==solarr[i]);
    if (matches) std::cout << "PASS";
    else std::cout << retarr << "!=" << solarr;
}

long my_factorial(int n)
{
    long fact {1};

    if (n==0) return fact;

    for (int i {1}; i<=n; ++i)
    {
        fact *= i;
    }
    return fact;
}

long my_addition(long a, long b)
{
    return a+b;
}

long my_power(double a, double b)
{
    double ret {1};
    for (double i{0.0}; i<b; ++i)
    {
        ret *= a;
    }
    return static_cast<long>(ret);
}

double my_average(double* arr, int sz)
{
    double summ {};
    for (int i {0}; i<sz; ++i) summ+=arr[i];
    return summ/sz;
}

int my_max(long* arr, int sz) // Returns the index of the max value
{
    long mxx {LLONG_MIN};
    int idx{-1};
    for (int i{0}; i<sz; ++i) if (arr[i]>mxx) {mxx=arr[i]; idx=i;}
    return idx;
}

long* my_sort(long* arr, int sz)
{
    long* retarr {new long[sz]}; // Allocate retarr in the HEAP
    int tempi{-1};
    for (int idx{sz-1}; idx>=0; --idx) // do this sz times
    {
        tempi = my_max(arr, sz);
        retarr[idx] = arr[tempi];
        arr[tempi] = LLONG_MIN;
    }
    return retarr;
}

int main_phase1();

int calculator()
{
    std::cout << "Enter a Number\n0:factorial\n1:addition\n2:power\n3:average\n4:max\n5:sort\n[in] >> ";
    return main_phase1();
}

// using namespace std;
int main_phase1() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int sel {-1};
    long retl {}, soll {};
    double retd {}, sold{};

    std::cin >> sel;

    // calls each calculation function after reading necessary input.
    switch(sel)
    {
        case 0: {   int n {1};
            std::cin >> n;
            retl = my_factorial(n);
            std::cin >> soll;
            verify(retl, soll);
            break;}
        case 1: {   long a{}, b{};
            std::cin >> a;
            std::cin >> b;
            retl = my_addition(a, b);
            std::cin >> soll;
            verify(retl, soll);
            break;}
        case 2: {   double a{}, b{};
            std::cin >> a;
            std::cin >> b;
            retl = my_power(a, b);
            std::cin >> soll;
            verify(retl, soll);
            break;}
        case 3: {   int sz{};
            std::cin >> sz;
            double arr[sz];

            for (int i {0}; i<sz; ++i) std::cin >> arr[i];

            retd = my_average(arr, sz);
            std::cin >> sold;
            verify(retd, sold);
            break;}
        case 4: {   int sz{}, idx{};
            std::cin >> sz;
            long arr[sz];

            for (int i {0}; i<sz; ++i) std::cin >> arr[i];

            idx = my_max(arr, sz);
            retd = arr[idx];
            std::cin >> sold;
            verify(retd, sold);
            break;}
        case 5: {   int sz{};
            std::cin >> sz;
            long arr[sz], solarr[sz];

            for (int i {0}; i<sz; ++i) std::cin >> arr[i];
            for (int i {0}; i<sz; ++i) std::cin >> solarr[i];

            long* retarr {my_sort(arr, sz)};
            verify(retarr, solarr, sz);
            break;}
        default: std::cout << "Please select 0-5.\n";
    }

    // std::cout << ret;
    return 0;
}