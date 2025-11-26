#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    string inputFileName;
    cout << "Enter file name to compress (with extension): ";
    cin >> inputFileName;

    ifstream inFile(inputFileName, ios::binary);
    if (!inFile.is_open()) {
        cerr << "❌ Error opening file!" << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    cout << "✅ File loaded successfully. Size: " << content.size() << " bytes" << endl;

    unordered_map<char, int> freq;
    for (char c : content) {
        freq[c]++;
    }

    cout << "\nCharacter Frequency Table:\n";
    for (auto pair : freq) {
        if (pair.first == '\n')
            cout << "'\\n': " << pair.second << endl;
        else
            cout << "'" << pair.first << "': " << pair.second << endl;
    }

    return 0;
}
