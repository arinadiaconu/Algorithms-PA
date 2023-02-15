#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <utility>
using namespace std;

class Prinel {
 public:
    void solve_prinel() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, k, el;
    int target[1000], p[1000000], nr_operations[1000];

    // reads input from the given file
    void read_input() {
        ifstream fin("prinel.in");
        fin >> n >> k;
        if (k > 24000) {
            k = 24000;
        }
        for (int i = 1; i <= n; i++) {
            fin >> el;
            target[i - 1] = el;     // the target vector
        }
        for (int i = 1; i <= n; i++) {
            fin >> el;
            p[i - 1] = el;          // the points vector
        }
        fin.close();
    }

    // this function is given a minimum and compares it to the number
    // in the given vector equal to dp[element - x], where x is a
    // divizor of element
    int my_compare(int minn, int element, int x, vector<int> &dp) {
        if (minn > dp[element - x]) {
            return dp[element - x];
        }
        return minn;
    }

    // this function iterates through all divisors of an element
    // except the actual element and keeps the minimum between
    // all dp[element - div]
    int my_min(vector<int> &dp, int element) {
        int minn;
        minn = dp[element - 1];
        for (int i = 2; i <= sqrt(element); i++) {
            if ((element % i) == 0) {
                if ((element / i) == i) {   // i * i == element
                    minn = my_compare(minn, element, i, dp);
                } else {
                    minn = my_compare(minn, element, i, dp);
                    minn = my_compare(minn, element, (element / i), dp);
                }
            }
        }
        return minn;
    }

    // this function calculates the vector that keeps the number of
    // operations to reach each target in the target vector
    // first, it keeps in a vector that goes from 1 to the maximum
    // number in the target vector, the number of operations to reach
    // each of these targets
    // dp[i] = 1 + min(dp[i - div1], dp[i - div2], ...)
    // after that, it simply iterates through the target vector
    // and keeps the number of operations from dp
    void number_of_operations() {
        int max_target = *max_element(target, target + n);
        vector<int> dp(max_target + 1);
        dp[1] = 0;
        dp[2] = 1;
        for (int i = 3; i <= max_target; i++) {
            dp[i] = 1 + my_min(dp, i);
        }
        for (int i = 0; i < n; i++) {
            nr_operations[i] = dp[target[i]];
        }
    }

    // this function implements the knapsack algorithm for an array
    int most_points() {
        int dp[1000001];

        // all elements are initialized with zero
        for (int i = 0; i < k + 1; i++) {
            dp[i] = 0;
        }

        for (int i = 0; i < n; ++i) {
            int points_left = k - nr_operations[i];
            if (points_left >= 0) {
                for (int j = points_left; j >= 0; --j) {
                    dp[j + nr_operations[i]] = max(dp[j] + p[i],
                                        dp[j + nr_operations[i]]);
                }
            }
        }
        return dp[k];
    }

    int get_result() {
        number_of_operations();
        return most_points();
    }

    void print_output(int max) {
        ofstream fout;
        fout.open("prinel.out");
        fout << max << endl;
        fout.close();
    }
};

int main() {
    auto* task3 = new (nothrow) Prinel();
    if (!task3) {
        return -1;
    }
    task3->solve_prinel();
    delete task3;
    return 0;
}
