//
//  main.cpp
//  COP3530_Project2
//
//  Created by Jason Cochran on 11/28/16.
//  Copyright (c) 2016 Jason Cochran. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Modified KMP search algorithm
int Search(string key, vector<char> string) {
    int count = 0; // Keeps count of how many times we encountered the string
    int keylength = key.size();
    int stringLength = string.size();
    
    // values for pattern
    int pattern[keylength];
    
    // Preprocess the pattern
    int size = 0;
    pattern[0] = 0;
    int i = 1;
    while (i < keylength)
    {
        if (key[i] == key[size]) {
            size++;
            pattern[i] = size;
            i++;
        } else {
            if (size != 0) {
                size = pattern[size-1];
            } else {
                pattern[i] = 0;
                i++;
            }
        }
    }
    
    // Actually determine how many occurences are in our string
    int stringI = 0;  // string indexer
    int keyI = 0;  // key indexer
    while (stringI < stringLength) {
        if (key[keyI] == string[stringI]) {
            stringI++;
            keyI++;
        }
        
        if (keyI == keylength) {
            count++;
            keyI = pattern[keyI-1];
        } else if (key[keyI] != string[stringI] && stringI < stringLength) {
            if (keyI != 0) {
                keyI = pattern[keyI-1];
            } else {
                stringI = stringI+1;
            }
        }
    }
    return count;
}

vector<int> commonSS(vector<int> row, vector<int> col) {
    
    int n = col.size();
    vector<vector<int>> storage(n + 1, vector<int>(n + 1) );
    
    // First get the gth of our longest common substring
    // n^2
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                storage[0][0] = 0;
            } else if (row[i-1] == col[j-1]) {
                storage[i][j] = storage[i-1][j-1] + 1;
            } else {
                if( storage[i-1][j] >= storage[i][j-1] ) {
                    storage[i][j] = storage[i-1][j];
                } else {
                    storage[i][j] = storage[i][j-1];
                }
            }
        }
    }
    
    int length = storage[n][n];
    vector<int> string(length);
    int i = n;
    int j = n;
    
    // Now lets get what our longest common substring actually is
    // n^2
    while (i > 0 && j > 0) {
        if (row[i-1] == col[j-1])  {
            string[length-1] = row[i-1];
            i--;
            j--;
            length--;
        } else if (storage[i-1][j] > storage[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return string;
}

int main() {
    string hint;
    int n;
    cin >> hint;
    // const vector<char> hintV(hint.begin(), hint.end());
    
    cin >> n;
    vector<vector<char>> column(n, vector<char>(n));
    vector<vector<char>> row(n, vector<char>(n));
    
    // n^2 takes input one char at a time
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            char c;
            cin >> c;
            column[i][j] = c;
            row[j][i] = c;
        }
    }

    vector<int> countRow(n, 0);
    vector<int> countCol(n, 0);
    
    // Column
    // n for each iteration.. n^2
    for (int i = 0; i < n; i++) {
        countCol[i] = Search(hint, column[i]);
    }
    
    // Row
    // n for each iteration.. n^2
    for (int i = 0; i < n; i++) {
        countRow[i] = Search(hint, row[i]);
    }
    
    // Find maximum gth acceptable... aka our password
    vector<int> answer = commonSS(countRow, countCol);
    
    for(int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }
    
    return 0;
}
