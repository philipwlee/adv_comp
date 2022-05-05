//#include <bits/stdc++.h>
#include<iostream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

#include<math.h>

/*
 * Complete the 'pthFactor' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER n
 *  2. LONG_INTEGER p
 */

long pthFactor(long n, long p) {
    long remain {p}, fact {0}, stop {static_cast<long>(sqrt(n)+1)}, temp {0};
    // cout << stop <<'\n';
    for (long i=1; remain!=0 && i<stop; ++i)
    {
        if (n%i==0)
        {
            fact = i;
            // cout << p-remain << ". " << fact << '\n';
            --remain;
        }
    }
    for (long i=stop-1; remain!=0 && i>0; --i)
    {
        if (n%i==0 && n/i > fact)
        {
            fact = n/i;
            // cout << p-remain+1 << ". " << fact << '\n';
            --remain;
        }
    }

    if (remain>0) fact = 0;

    return fact;
}

//int main()
//{
//    ofstream fout(getenv("OUTPUT_PATH"));
//
//    string n_temp;
//    getline(cin, n_temp);
//
//    long n = stol(ltrim(rtrim(n_temp)));
//
//    string p_temp;
//    getline(cin, p_temp);
//
//    long p = stol(ltrim(rtrim(p_temp)));
//
//    long result = pthFactor(n, p);
//
//    fout << result << "\n";
//
//    fout.close();
//
//    return 0;
//}
//
//string ltrim(const string &str) {
//    string s(str);
//
//    s.erase(
//            s.begin(),
//            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
//    );
//
//    return s;
//}
//
//string rtrim(const string &str) {
//    string s(str);
//
//    s.erase(
//            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
//            s.end()
//    );
//
//    return s;
//}
