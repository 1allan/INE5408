#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <iostream>
#include "trie.h"

struct Trie {

    char letter{'\0'};
    unsigned long position{0};
    unsigned long length{0};
    bool leaf{false};
    Trie *children[26];

    Trie() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }

    Trie(char letter_) :
        letter{letter_}
    {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }


    /**
    * @brief Insere uma nova palavra à trie
    *
    * Verifica se a letra já está na lista de filhos da Trie atual e, se
    * estiver, continua na próxima até que não esteja na lista, realizando a
    * inserção. A inserção termina ao inserir (ou não) a última letra da 
    * palavra e definindo o tamanho e posição da mesma em relação ao arquivo de
    * entrada.
    *
    * @param word Palavra a ser inserida.
    * @param position Posição da palavra no arquivo de entrada.
    * @param length Tamanho de texto de definição da palavra.
    */
    void insert(std::string word, std::size_t position, std::size_t length) {
        auto current = this;

        for (std::size_t i = 0; i < word.length(); i++) {
            int char_idx = word[i] - 'a';
            
            if (current->children[char_idx] == nullptr) {
                current->children[char_idx] = new Trie(word[i]);
            }
            current = current->children[char_idx];
        }
        current->leaf = true;
        current->length = length;
        current->position = position;
    }

    /**
    * @brief Verifica a existência de uma palavra na Trie.
    *
    * Verifica a existência de uma palavra na Trie chamando o método get(word),
    * caso a Trie retornada não seja nullptr e seja uma folha da Trie, então
    * a palavra está presente na Trie.
    *
    * @param word Palavra a ser verificada na se está presente na Trie.
    *
    * @return verdadeiro caso a palavra esteja presente na Trie e falso caso
    * não.
    */
    bool contains(std::string word) {
        auto current = this->get(word);

        return (current != nullptr && current->leaf);
    }


    /**
    * @brief Busca o nodo que representa uma dada palavra.
    *
    * Percorre a Trie de acordo com as letras da palavra passada como parâmetro
    * caso uma letra não seja encontrada em uma lista de filhos, retorna
    * nullptr.
    *
    * @param word Palavra do nodo a ser buscado.
    *
    * @return O nodo que representa a palavra ou nullptr caso a palavra não
    * esteja presente.
    */   
    Trie* get(std::string word) {
        auto current = this;

        for (std::size_t i = 0; i < word.length(); i++) {
            int char_idx = word[i] - 'a';
            if (current->children[char_idx] == nullptr){
                current = nullptr;
                break;
            }    
            current = current->children[char_idx];
        }
        return current;
    }

    /**
    * @brief Conta o número de folhas na Trie.
    *
    * Conta o número de folhas na tree percorrendo a Trie recursivamente. Ao
    * encontrar uma folha, soma 1 ao contador e, ao final da recursão, retorna
    * o valor final.
    *
    * @param root Trie à qual será iniciada a checagem.
    *
    * @return Quantidade de folhas em uma Trie.
    */
    int count_leafs(Trie* root) {
        int leafs = 0;

        for (std::size_t i = 0; i < 26; i++) {
            if (root->children[i] != nullptr) {
                if (root->children[i]->leaf) {
                    leafs += 1;
                }
                leafs += count_leafs(root->children[i]);
            }
        }
        return leafs;
    }

    /**
    * @brief Conta quantas palavras são prefixadas por uma dada sequência de 
    * caracteres.
    *
    * Inicia a checagem pelo nodo da sequência de caractêres passada por
    * parâmetro e, de forma recursive, conta as folhas desta subtree.
    *
    * @param word Prefixo tido como base para a contagem.
    *
    * @return quantidade de palavras que têm o parâmtro word como prefixo.
    */
    int count_prefixes(std::string word) {
        auto current = this->get(word);
        auto count = 0;

        if (current == nullptr) {
            return 0;
        } else if (current->leaf) {
            count += 1;
        }

        return count + count_leafs(current);
    }

};

#endif