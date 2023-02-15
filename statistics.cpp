#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
using namespace std;

class Statistics {
 public:
    void solve_statistics() {
        read_input();
        print_output(max_number_of_strings());
    }

 private:
    int n;
    string word;
    vector<string> words;   // keeps the strings from input

    // reads input from the given file
    void read_input() {
        ifstream fin("statistics.in");
        fin >> n;
        for (int i = 1; i <= n; i++) {
            fin >> word;
            words.push_back(word);
        }
        fin.close();
    }

    // this function calculates the frequency of a letter
    // in a string given as a parameter
    // this frequency sums up all matched characters and
    // decreses the frequency for each character that does
    // not match the letter given as a parameter
    int frequency_for_a_word(int character, string curr_word) {
        int character_frequency = 0;
        for (auto curr_character : curr_word) {
            if (curr_character == character) {
                character_frequency++;
            } else {
                character_frequency--;
            }
        }
        return character_frequency;
    }

    // this function calculates the frequency of a
    // character in each string of the vector
    // by calling the function above for each word
    vector<int> frequency_of_each_letter(int character) {
        vector<int> frequency;
        for (auto word : words) {
            int frequency_for_this_word = frequency_for_a_word(character,
                                                                    word);
            frequency.push_back(frequency_for_this_word);
        }
        return frequency;
    }

    // this function gets for each letter in the alphabet the frequency
    // vector and sums up all the strings. While they still mantain a
    // dominant character (curr_sum > 0), it increments a maximum of words
    // In the end, it returns that maximum
    int max_number_of_strings_for_each_letter(vector<int> &frequency) {
        int curr_max = 0, curr_sum = 0;
        for (auto n : frequency) {
            curr_sum = curr_sum + n;
            if (curr_sum > 0) {
                curr_max++;
            }
        }
        return curr_max;
    }

    // this function iterates through all the letters of the alphabet
    // and for each letter, it calculates a frequency vector that contains
    // the frequency of each letter - each character that doesn't match the
    // letter. It then sorts this vector in descending order and then calls
    // a function that sums up the strings containg that dominant letter.
    // In the end it compares that current maximum of concatenated strings
    // with the count and updates that number if smaller than what is being
    // returned
    int max_number_of_strings() {
        int count = 0;
        for (char i = 'a'; i <= 'z'; i++) {
            vector<int> frequency = frequency_of_each_letter(i);
            sort(frequency.begin(), frequency.end(), greater<int>());
            int curr_max = max_number_of_strings_for_each_letter(frequency);
            if (curr_max > count) {
                count = curr_max;
            }
        }
        return count;
    }

    void print_output(int count) {
        ofstream fout;
        fout.open("statistics.out");
        fout << count << endl;
        fout.close();
    }
};

int main() {
    auto* task2 = new (nothrow) Statistics();
    if (!task2) {
        return -1;
    }
    task2->solve_statistics();
    delete task2;
    return 0;
}
