#include<iostream>
#include<string>


bool checkPalindrome(char* ss, size_t pos, size_t npos)
{
    bool is_equal {true};
    size_t half {npos/2}, middle {pos+half};
    char* start {ss+pos};

    for (size_t idx{0}; idx<=half; ++idx)
    {
        if (*(start+idx)==*(start+npos-1-idx)) continue;
        else {is_equal=false; break;}
    }

    return is_equal;
}

int countPalindromes(std::string s) {
    int n { static_cast<int>(s.length()) };
    int palindromes {0};
    std::cout << s << '\n';

    bool is_repeat{true};
    char last{ s[0] };
    for (int pos{1}; pos<n; ++pos)
    {
        if (last!=s[pos]) is_repeat = false;
    }
    if (is_repeat) return n*(n+1)/2;

    for (int pos{0}; pos<n; ++pos)
    {
        for (int npos{1}; npos<=n-pos; ++npos)
        {
            palindromes += checkPalindrome(&s[0], pos, npos);
        }
    }
    return palindromes;
}