#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) huffmanCode[root->ch] = str;
    buildCodes(root->left, str + "0", huffmanCode);
    buildCodes(root->right, str + "1", huffmanCode);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: compression <input_file> <output_file>\n";
        return 1;
    }

    ifstream inFile(argv[1], ios::binary);
    if (!inFile) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    unordered_map<char, int> freq;
    string text;
    char ch;

    while (inFile.get(ch)) {
        freq[ch]++;
        text += ch;
    }
    inFile.close();

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto pair : freq) pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    unordered_map<char, string> huffmanCode;
    buildCodes(pq.top(), "", huffmanCode);

    ofstream outFile(argv[2], ios::binary);
    for (char c : text)
        outFile << huffmanCode[c];
    outFile.close();

    cout << "\n✅ Compression Complete!" << endl;
    cout << "📦 Original size: " << text.size() * 8 << " bits" << endl;
    cout << "📦 Compressed size: " << outFile.tellp() << " bytes" << endl;
    cout << "📁 Output saved to: " << argv[2] << endl;

    deleteTree(pq.top());
    return 0;
}
