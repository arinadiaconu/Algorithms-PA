#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

class WalshTable {
 public:
    void solve_wash_table() {
        read_input();
        print_output();
    }

 private:
    int n, k, x, y;
    vector<int> my_results;  // keeps the results from the walsh
                             // table for each pair of x y

    // reads input from the given file
    void read_input() {
        ifstream fin("walsh.in");
        fin >> n >> k;
        for (int i = 1; i <= k; i++) {
            fin >> x >> y;
            get_result();
        }
        fin.close();
    }

    // this function verifies whether a pair of indexes is
    // inside the rectangle formed by a set of 2 pairs
    // tlx - top left x and tly - top left y
    // drx - down right x and dry - down right y
    bool in_rectangle(int x, int y, int tlx, int tly, int drx, int dry) {
        return (tlx <= x && x <= drx) &&  (tly <= y && y <= dry);
    }

    // this function recursively searches in the walsh table
    // for the pair of x y and counts how many times that
    // pair is in the down right square of the table
    int recursive_search(int x, int y, int tlx, int tly,
                            int dimension, int count) {
        if (dimension == 1) {   // a walsh table with only one element
            return count;
        }

        // calculates the down right indexes
        int drx = tlx + dimension - 1;
        int dry = tly + dimension - 1;

        // calculates the middle indexes between left and right
        int mx = (tlx + drx) / 2;
        int my = (tly + dry) / 2;

        // each time the dimension for new walsh table
        // will be 2 times smaller than the previous one
        int new_dimension = (dimension / 2);

        // case 1 - top left square in the walsh table
        if (in_rectangle(x, y, tlx, tly, mx, my)) {
            return recursive_search(x, y, tlx, tly, new_dimension, count);
        }

        // case 2 - top right square in the walsh table
        if (in_rectangle(x, y, tlx, my + 1, mx, dry)) {
            return recursive_search(x, y, tlx, my + 1, new_dimension, count);
        }

        // case 3 - down left square in the walsh table
        if (in_rectangle(x, y, mx + 1, tly, drx, my)) {
            return recursive_search(x, y, mx + 1, tly, new_dimension, count);
        }

        // case 4 - down right square in the walsh table
        // this is the only case that matters and the count increses by 1
        if (in_rectangle(x, y, mx + 1, my + 1, drx, dry)) {
            return recursive_search(x, y, mx + 1, my + 1,
                                    new_dimension, count + 1);
        }

        // there's always a way out of this recursion
        // so this return statement is for the sake of no warnings
        return -1;
    }

    // this function is called for each pair of x y read from the file
    // it calls the recursive search in the walsh table and returns the
    // number of times that pair is in the right down square of the walsh table
    int solve_recursively(int n, int x, int y) {
        return recursive_search(x, y, 1, 1, n, 0);
    }

    // for each pair of x y this function verifies if the number of times
    // that the pair was in the right down square of the walsh table is even
    // and if so, the result in the table will always be a 0 (zero) and if
    // the number is odd, the result will always be a 1 (one)
    void get_result() {
        int count = solve_recursively(n, x, y);
        if ((count % 2) == 0) {
            my_results.push_back(0);    // it keeps all results in a vector
        } else {
            my_results.push_back(1);
        }
    }

    void print_output() {
        ofstream fout;
        fout.open("walsh.out", ios::out | ios::app);
        for (int x : my_results) {
            fout << x << endl;
        }
        fout.close();
    }
};

int main() {
    auto* task1 = new (nothrow) WalshTable();
    if (!task1) {
        return -1;
    }
    task1->solve_wash_table();
    delete task1;
    return 0;
}
