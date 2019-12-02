#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
    string line;

    cout << "please enter a string: ";
    getline(cin, line);
    cout << "\n";

    vector<string> tokens;

    stringstream check1(line);

    string intermediate;

    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }

    for (int i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i] << '\n';
    }

    return 0;
}

