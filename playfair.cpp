#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string prepareText(string text) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I'; // Replace J with I
            result += c;
        }
    }
    for (int i = 0; i < result.length(); i += 2) {
        if (i + 1 == result.length()) {
            result += 'X'; // If odd length, append 'X'
        } else if (result[i] == result[i + 1]) {
            result.insert(i + 1, 1, 'X'); // Insert 'X' between duplicate letters
        }
    }
    return result;
}

void generateMatrix(string key, char matrix[5][5]) {
    string keyString = "";
    bool exists[26] = {false};
    key += "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Include all alphabets except J

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I'; // Replace J with I
        if (isalpha(c) && !exists[c - 'A']) {
            keyString += c;
            exists[c - 'A'] = true;
        }
    }

    int idx = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = keyString[idx++];
        }
    }
}

pair<int, int> findPosition(char matrix[5][5], char ch) {
    if (ch == 'J') ch = 'I'; // Replace J with I
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == ch) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should never happen
}

string encrypt(string plaintext, char matrix[5][5]) {
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i += 2) {
        char num1 = plaintext[i];
        char num2 = plaintext[i + 1];
        auto [row1, col1] = findPosition(matrix, num1);
        auto [row2, col2] = findPosition(matrix, num2);

        if (row1 == row2) {
            ciphertext += matrix[row1][(col1 + 1) % 5];
            ciphertext += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext += matrix[(row1 + 1) % 5][col1];
            ciphertext += matrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext += matrix[row1][col2];
            ciphertext += matrix[row2][col1];
        }
    }
    return ciphertext;
}

int main() {
    string key, plaintext;
    cout << "Enter key: ";
    getline(cin, key);

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    plaintext = prepareText(plaintext);

    char matrix[5][5];
    generateMatrix(key, matrix);

    string ciphertext = encrypt(plaintext, matrix);
    cout << "\nCiphertext: " << ciphertext << endl;

    return 0;
}
