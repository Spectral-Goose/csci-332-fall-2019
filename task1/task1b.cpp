#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

int main () {
    string line;

    cout << "Please enter a string: ";
    getline(cin, line);
    cout << "\n"; 

    vector <string> tokens; 
      
    stringstream check1(line); 
      
    string intermediate; 
      
    while(getline(check1, intermediate, ' '))
    { 
        tokens.push_back(intermediate); 
    } 

    string keyword;

    cout << "Enter a keyword: ";
    cin >> keyword;
    cout << "\n";

    for(auto it:tokens) {
        if(strcmp(it.c_str(), keyword.c_str()) > 0) {
            cout << it.c_str() << ": greater than keyword\n";
        }
        else if (strcmp(it.c_str(), keyword.c_str()) < 0){
            cout << it.c_str() << ": smaller than keyword\n";
        }
        else {
            cout << it.c_str() << ": equal\n";
        }
    }
    
    return 0;
}