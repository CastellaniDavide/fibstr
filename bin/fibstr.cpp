/**
 * @file fibstr.cpp
 *
 * @version 01.01 2020-11-15
 *
 * @brief https://training.olinfo.it/#/task/fibstr/statement
 *
 * @ingroup fibstr
 * (Note: this needs exactly one @defgroup somewhere)
 *
 * @author Castellani Davide
 *
 * Contact: contacts@castellanidavide.it
 *
 */

// Includes
#include <bits/stdc++.h>
using namespace std;

// To debug code
#define DEBUG

// My structure
typedef struct
{
    int init_;
    int end_;
    bool continue_;
    bool stable_;
    char a;
    char b;
} sequence;

// Variabiles
int N;
char c;
vector <sequence> sequences;
int max_lenght = 0;
int max_lenght_pos;

string memory_temp = "b";
string memory = "a";

bool my_checker(sequence check, char my_char)
{
    while (check.end_ - check.init_ + 1 >= memory.size()) // Update "memory"
    {
        string temp = memory;
        memory = memory + memory_temp;
        memory_temp = temp;
    }

#ifdef DEBUG
    cout << "My string: " << memory << endl;
    cout << "Wanted char: " << memory[check.end_ - check.init_ + 1] << "\ta: " << check.a << "\tb:" << check.b << endl;
#endif // DEBUG

    return (memory[check.end_ - check.init_ + 1] == 'a' && my_char == check.b) || (memory[check.end_ - check.init_ + 1] == 'b' && my_char == check.a); // Get my result
}

// Main code
int main()
{
    // Cncomment the following lines if you want to read/write from files
    freopen("input.txt", "r", stdin);
#ifndef DEBUG
    freopen("output.txt", "w", stdout);
#endif // DEBUG

    // Input
    cin >> N;

    for (int i = 0; i < N; ++i) // For every char
    {
        cin >> c;

        // Update old sequences
        for (int j = 0; j < sequences.size(); ++j)
        {
            // If avariable to be updated
            if(sequences[j].continue_)
            {
                // If it's known the two chars
                if(sequences[j].stable_)
                {
                    // If is possible continue go on else stop sequence
                    if(my_checker(sequences[j], c))
                    {
                        sequences[j].end_ = i;
                        if(sequences[j].end_ - sequences[j].init_ + 1 > max_lenght)
                        {
                            max_lenght = sequences[j].end_ - sequences[j].init_ + 1;
                            max_lenght_pos = j;
                        }
                    }
                    else
                    {
                        sequences[j].continue_ = false;
                    }
                }
                else // If it's not known the two chars take the "second" only if new char is different
                {
                    if (c != sequences[j].b){
                        sequences[j].end_ = i;
                        sequences[j].stable_ = true;
                        sequences[j].a = c;

                        if(sequences[j].end_ - sequences[j].init_ + 1 > max_lenght)
                        {
                            max_lenght = sequences[j].end_ - sequences[j].init_ + 1;
                            max_lenght_pos = j;
                        }
                    }
                    else
                    {
                        sequences[j].continue_ = false;
                    }
                }
            }
        }

        // New sequences
        {
            sequence temp;
            temp.init_ = i;
            temp.end_ = i;
            temp.continue_ = true;
            temp.stable_ = false;
            temp.a = '-';
            temp.b = c;

            sequences.push_back(temp);

            if(max_lenght == 0)
            {
                max_lenght = 1;
                max_lenght_pos = sequences.size()-1;
            }
        }

#ifdef DEBUG
        for (int j = 0; j < sequences.size(); ++j)
        {
            cout << j << ": " << sequences[j].continue_ << "\t" << sequences[j].stable_ << "\t" << sequences[j].init_ << "\t" << sequences[j].end_ << "\t" << sequences[j].a << "\t" << sequences[j].b << endl;
        }
        cout << "---------------------------------------" << endl;
#endif // DEBUG
    }

#ifdef DEBUG
    cout << "My string:" << memory << endl;
#endif // DEBUG

    // Output
    cout << sequences[max_lenght_pos].init_ + 1 << " " << sequences[max_lenght_pos].end_ + 1 << endl;

    // End
    return 0;
}
