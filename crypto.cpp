#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <utility>
using namespace std;

#define MOD 1000000007

class Crypto {
 public:
    void solve_crypto() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, l;
    string key, substring;

    // reads input from the given file
    void read_input() {
        ifstream fin("crypto.in");
        fin >> n >> l;
        fin >> key;
        fin >> substring;
        fin.close();
    }

    // this function calculates the number of distinct
    // characters in a string
    unsigned long long count_distinct_characters(string str) {
        set<int> my_set;        // stores only unique elements
        for (unsigned i = 0; i < str.size(); i++) {
            my_set.insert(str[i]);
        }
        return my_set.size();
    }

    // this function builds up a matrix using dinamic programming
    // which stores the maximum number of times the string subsequence
    // is found in the key at each step
    int count_substrings() {
        int dp[100001][11];
        unsigned long long distinct_ch_in_substring =
                            count_distinct_characters(substring);

        // the first line is initialized with zeros
        for (int j = 0; j <= l; j++) {
            dp[0][j] = 0;
        }

        // the first element is 1
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {  // each character of the key
            for (int j = 0; j <= l; j++) {  // each character of the string
                if (j == 0) {   // the initialization of the first column
                    if (key[i - 1] == '?') {
                        dp[i][j] = ((dp[i - 1][j] % MOD) *
                                (distinct_ch_in_substring % MOD)) % MOD;
                    } else {
                        dp[i][j] = dp[i - 1][j];
                    }
                } else {
                    if (key[i - 1] == '?') {
                        dp[i][j] = ((distinct_ch_in_substring % MOD) *
                                                (dp[i - 1][j] % MOD)) % MOD;
                        dp[i][j] = ((dp[i][j] % MOD) + (dp[i - 1][j - 1] %
                                                                MOD)) % MOD;
                    } else if (key[i - 1] != substring[j - 1]) {
                        dp[i][j] = dp[i - 1][j];
                    } else {
                        dp[i][j] = ((dp[i - 1][j - 1] % MOD) + (dp[i - 1][j]
                                                                % MOD)) % MOD;
                    }
                }
            }
        }
        return dp[n][l];
    }

    int get_result() {
        return count_substrings();
    }

    void print_output(int count) {
        ofstream fout;
        fout.open("crypto.out");
        fout << count << endl;
        fout.close();
    }
};

int main() {
    auto* task4 = new (nothrow) Crypto();
    if (!task4) {
        return -1;
    }
    task4->solve_crypto();
    delete task4;
    return 0;
}
