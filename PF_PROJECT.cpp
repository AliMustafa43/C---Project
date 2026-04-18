#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;


//SECTION 1: VALIDATION AND LOGGING

int getValidInt(string prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val)) {
        cout << "[!] Input Error (Please enter a valid number): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    return val;
}

string getValidAlphaKey(string prompt) {
    string key;
    bool isValid;
    do {
        isValid = true;
        cout << prompt;
        getline(cin, key);
        
        if (key.empty()) {
            isValid = false;
        } else {
            for (char c : key) {
                if (!isalpha(c)) {
                    isValid = false;
                    break;
                }
            }
        }
        if (!isValid) cout << "[!] Input Error: (Keyword must be letters only)\n";
    } while (!isValid);
    return key;
}

void logOperation(string tool, string action, string input, string output) {
    ofstream file("crypto_history.log", ios::app);
    if (file.is_open()) {
        file << "[" << tool << "] " << action << "\nInput:  " << input << "\nOutput: " << output << "\n-------------------"<<endl;
        file.close();
    }
}

//SECTION 2:CIPHER ENGINES

// 1. CAESAR
void cipherCaesar(string& text, int key, bool encrypt) {
    if (!encrypt) key = -key;
    key = (key % 26 + 26) % 26;
    
    char* ptr = &text[0]; 
    while (*ptr != '\0') {
        if (isalpha(*ptr)) {
            char base = islower(*ptr) ? 'a' : 'A';
            *ptr = char((*ptr - base + key) % 26 + base);
        }
        ptr++;
    }
}

// 2. ATBASH
void cipherAtbash(string& text) {
    for (char& c : text) {
        if (islower(c)) c = 'z' - (c - 'a');
        else if (isupper(c)) c = 'Z' - (c - 'A');
    }
}

// 3. VIGENERE
void cipherVigenere(string& text, string key, bool encrypt) {
    int keyIdx = 0;
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = islower(text[i]) ? 'a' : 'A';
            int k = tolower(key[keyIdx % key.length()]) - 'a';
            if (!encrypt) k = -k;
            text[i] = char((text[i] - base + k + 26) % 26 + base);
            keyIdx++;
        }
    }
}

// 4. RAIL FENCE
string runRailFence(string text, int rails, bool encrypt) {
    if (rails <= 1) return text;
    int len = text.length();
    vector<vector<char>> fence(rails, vector<char>(len, '\n'));
    
    int row = 0;
    bool down = false;
    for (int i = 0; i < len; i++) {
        fence[row][i] = (encrypt) ? text[i] : '*';
        if (row == 0 || row == rails - 1) down = !down;
        row += down ? 1 : -1;
    }

    if (encrypt) {
        string res = "";
        for (int i = 0; i < rails; i++)
            for (int j = 0; j < len; j++)
                if (fence[i][j] != '\n') res += fence[i][j];
        return res;
    } else {
        int idx = 0;
        for (int i = 0; i < rails; i++)
            for (int j = 0; j < len; j++)
                if (fence[i][j] == '*' && idx < len) fence[i][j] = text[idx++];
        
        string res = "";
        row = 0; down = false;
        for (int i = 0; i < len; i++) {
            res += fence[row][i];
            if (row == 0 || row == rails - 1) down = !down;
            row += down ? 1 : -1;
        }
        return res;
    }
}


//SECTION 3: MAIN INTERFACE


int main() {
    int choice = -1;
    while (choice != 0) {
        cout << "\n=------====================-----="<<endl;
        cout << "       CRYPTOGRAPHY TOOLKIT      "<<endl;
        cout << "=------====================-----="<<endl;
        cout << "1. Caesar (Pointers)\n2. Atbash (Substitution)\n3. Vigenere (Keyword)\n4. Rail Fence (Transposition)\n0. Exit\n";
        
        choice = getValidInt("Select Choice: ");
        if (choice == 0) break;
        if (choice < 1 || choice > 4) {
            cout << "[!] Invalid Selection."<<endl;
            continue;
        }

        int mode = getValidInt("1.Encrypt | 2.Decrypt: ");
        if (mode != 1 && mode != 2) {
            cout << "[!] Invalid Mode."<<endl;
            continue;
        }

        string text, original;
        cout << "Enter Message: ";
        getline(cin, text);
        original = text;

        if (choice == 1) {
            int key = getValidInt("Enter shift key (Number): ");
            cipherCaesar(text, key, mode == 1);
        } 
        else if (choice == 2) {
            cipherAtbash(text);
        } 
        else if (choice == 3) {
            string key = getValidAlphaKey("Enter Keyword (Letters): ");
            cipherVigenere(text, key, mode == 1);
        } 
        else if (choice == 4) {
            int rails = getValidInt("Enter Rail Depth (2 or more): ");
            text = runRailFence(text, (rails < 2 ? 2 : rails), mode == 1);
        }

        cout << "\n>>> FINAL RESULT: " << text <<endl;
        logOperation("Tool " + to_string(choice), (mode == 1 ? "Encryption" : "Decryption"), original, text);
    }

    cout << "Program Terminated. Log saved to 'crypto_history.log'"<<endl;
    return 0;
}