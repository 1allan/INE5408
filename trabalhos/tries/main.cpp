#include <iostream>
#include <fstream>
#include <sstream>

#include "trie.h"

int main() {
    
    std::ifstream file;
    std::string file_name;

    std::cin >> file_name;

    file.open(file_name);
    
    if (!file.is_open()) {
        std::cout << "error\n";
        return -1;
    }
    
    auto trie = Trie();

    std::string line;
    size_t char_count = 0;
    
    while (std::getline(file, line)) {
        std::string word = line.substr(1, line.find_first_of(']') - 1);
        trie.insert(word, char_count, line.length());
        char_count += line.length() + 1;
    }

    file.close();
    
    std::string word;
    while(1) {
        std::cin >> word;

        if (word.compare("0") == 0) {
            break;
        }

        int prefixes = trie.count_prefixes(word);

        if (prefixes > 0) {
            std::cout << word << " is prefix of " << prefixes << " words" << std::endl;
        } else {
            std::cout << word << " is not prefix" << std::endl;
        }

        if (trie.contains(word)) {
            auto node = trie.get(word);
            if (node == nullptr) {
                continue;
            }

            std::cout << word << " is at (" << node->position << "," << node->length << ")" << std::endl; 
        }
    }

    return 0;
}   