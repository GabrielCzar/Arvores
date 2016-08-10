#ifndef BTREE_H
#define BTREE_H

#include <sstream>

#include <iostream>
#include "node.h"
#include "../libs/btreeview.h"


//arvore binaria de busca
class bstree
{

public:
    bnode * root{nullptr};

    bstree(){}

    //construtor de copia
    //btree(const btree &other);

    //desaloca todos os nós
    ~bstree(){
        this->clear();
		root = nullptr;
    }

    void gambi_fill(){
        root = new bnode(6);
        root->left = new bnode(3);
        root->left->right = new bnode(4);
        auto nove = new bnode(9);
        root->right = nove;
        nove->left = new bnode(7);
        nove->right = new bnode(10);
        nove->right->right = new bnode(11);
    }

    int _size(bnode * node){
        if(node == nullptr)
            return 0;
        return 1 + _size(node->left) + _size(node->right);
    }

    ///retorna a quantidade de elementos da arvore
    int size(){
        return _size(root);
    }

    ///retorna a altura da arvore
    int altura (bnode * node) {
       if (node == nullptr)
          return -1; // altura da árvore vazia;
       return std::max(1 + altura (node->left), 1 + altura (node->right));
    }

    int altura(){
        return altura(root);
    }

    ///retorna a altura do no passado
    int altura_node(bnode *node, bnode * nodeSearch){
        if(node == nodeSearch || node == nullptr) //Termina se encontrar o no ou se chegar ao final
            return 0; //padrao -1 mas so da certo com zero
         return std::min(1 + altura_node(node->left, nodeSearch), 1 + altura_node(node->right, nodeSearch));
    }

    int altura_node(bnode * node){
        return altura_node(root, node);
    }

    ///preenche o vetor utilizando o percurso pre-order
    std::vector<int> pre_order(std::vector<int> &vet, bnode * node){
        if(node == nullptr)
            return vet;
        vet.push_back(node->value);
        pre_order(vet, node->left);
        pre_order(vet, node->right);
        return vet;
    }

    std::vector<int> pre_order(){
        std::vector<int> vet;
        return pre_order(vet, root);
    }

    ///imprime a arvore na saida padrao
    void _print(bnode * node){
        if(node == nullptr)
            return;
        cout << node->value << " ";
        _print(node->left);
        _print(node->right);
    }

    void print(){
        _print(root);
    }

    //imprime a arvore formatada
    void printTree(bnode * node, int nivel){
    	int tab = 4;
    	if (node == nullptr)
    		return;
    	cout << string (tab * nivel, ' ') << node->value << endl;
    	printTree(node->left, nivel + 1);
    	printTree(node->right, nivel + 1);
    }

    bnode * _insert(bnode * node, int value){
        if(node == nullptr)
            return new bnode(value);
        //o seguinte comando desenha a arvore
        my_tview->paint_tree(root);
        //o seguinte comando desenha o no em superposicao dada a cor, o valor
        //e o no sobre o qual ele deve estar em cima
        my_tview->focus_node(node, 'b', value);
        //o seguinte comando mostra o que foi desenhado
        my_player->show();

        if(value > node->value)
            node->right = _insert(node->right, value);
        if(value < node->value)
            node->left = _insert(node->left, value);
        return node;
    }

    ///insere o valor usando o algoritmo de inserção
    ///em árvore binária de busca

    void insert(int value){  //OLD
        root = _insert(root, value);
    }

    bool elo_insert(bnode * node, int value, bnode ** elo){
        if(node == nullptr)
            return (*elo = new bnode(value));

        my_tview->paint_tree(root);
        my_tview->focus_node(node, 'b', value);
        my_player->show();

        if(node->value == value)
            return false;
        if(value < node->value)
            return elo_insert(node->left, value, &node->left);
        return elo_insert(node->right, value, &node->right);
    }

    bool elo_insert(int value){
        return elo_insert(root, value, &root);
    }

    bool smart_insert(int value){
        auto elo = smart_find(value);

        my_tview->paint_tree(root);
        my_tview->focus_node(*elo, 'b', value);
        my_player->show();

        if(*elo == nullptr)
            return (*elo = new bnode(value));
        return false;
    }



        //gera uma string que representa a árvore
   std::string serialize(bnode * node){
       if(node == nullptr)
           return "# ";
       string text = to_string(node->value) + " ";
       text += serialize(node->left);
       text += serialize(node->right);
       return text;
   }


   //apaga a arvore atual e monta uma nova árvore através da string
   //que foi resultado da serialização
   void load(std::string tree){
       clear();
       stringstream t(tree);
       _load(t, root);
   }

   void _load(stringstream &tree, bnode * &node){
        string text;
        tree >> text;
        if (text == "#" || text == "")
            return;

        stringstream t(text);
        int v;
        t >> v;
        node = new bnode(v);

        _load(tree, node->left);
        _load(tree, node->right);
   }

   void _clear(bnode *node){
       if(node == nullptr)
           return;
       _clear(node->left);
       _clear(node->right);
       delete(node);
   }

    ///    //apaga e desaloca todos os nós da árvore incluindo o root
    ///    //é utilizado no destrutor e antes do load
    void clear(){
        _clear(root);
        root = nullptr;
    }

    //    //metodo para recursao recursiva
    //    bnode *_remove(bnode *node, int value);
    int roubar_e_matar(bnode * node, bnode ** elo){
        if(node ->right == nullptr){
            int value = node->value;
            _kill(node,elo);
            return value;
        }
        return roubar_e_matar(node->right, &node->right);
    }

    void _kill(bnode * node, bnode  ** elo){
        if(node->left == nullptr && node->right == nullptr){
            *elo = nullptr;
            delete node;
            return;
        }
        if(node->left != nullptr && node->right == nullptr){
            *elo = node->left;
            delete node;
            return;
        }if(node->left == nullptr && node->right != nullptr){
            *elo = node->right;
            delete node;
            return;
        }
        node->value = roubar_e_matar(node, elo);
    }

    ///remove a chave usando o algoritmo de remoção em árvore binária de busca
    bool _remove(bnode * node, int value, bnode ** elo){
        if(node == nullptr)
            return false;
        if(node->value == value){
            _kill(node, elo);
            return true;
        }
        if(value < node->value)
            return _remove(node->left, value, &node->left);
        return _remove(node->right, value, &node->right);

    }

    bool remove(int value){
        auto elo = smart_find(value);
        if(*elo == nullptr)
            return false;
        _kill(*elo, elo);
        return true;
    }
    ///busca o no utilizando o algoritmo da busca em árvore binária de busca
    ///bnode *find(int value);
    bnode ** _smart_find(bnode * node, int value, bnode ** elo){
        if(node == nullptr || node->value == value)
            return elo;
        if(value < node->value)
            return _smart_find(node->left, value, &node->left);
        return _smart_find(node->right, value, &node->right);
    }

    bnode ** smart_find(int value){
        return _smart_find(root, value, &root);
    }

    ///Saber se um determinado valor existe
    bool old_exist(bnode * node, int value){
        if(node == nullptr)
            return false;
        if(node->value == value)
            return true;
        if(value < node->value)
            return old_exist(node->left, value);
        return old_exist(node->right, value);
    }

    bool old_exist(int value){
        return old_exist(root, value);
    }

    bool exist(int value){
        return !*smart_find(value);
    }

    ///retorna a soma de todos os elementos a partir de node incluindo node
    int _soma(bnode * node){
        if(node == nullptr)
            return 0;
        return node->value + _soma(node->left) + _soma(node->right);
    }

    int soma(){
        return _soma(root);
    }

    ///retorna o menor nó de uma árvore não ordenada
    bnode * min(bnode * node){
        if(node->left == nullptr && node->right == nullptr)
            return node;
        if(node->left->value < node->right->value)
            return min(node->left);
        return min(node->right);
    }

    bnode * min(){
        return min(root);
    }

    ///inverte os nós filhos da esquerda com os da direita
    void reflexao(bnode * node){
        if(node == nullptr)
            return;
        std::swap(node->left, node->right);
        reflexao(node->left);
        reflexao(node->right);
    }

    ///a arvore eh balanceada se a diferenca entre as alturas dos filhos
    ///esquerda e direita for máximo 1
    bool eh_balanceada(){
        if(root == nullptr)
            return true;
        return std::abs(altura(root->left) - altura(root->right)) < 2;
    }

    void _show(bnode * node, string her, bnode * ref = nullptr, int value = 0){
        if(node != nullptr)
            if((node->left != nullptr) || (node->right != nullptr))
                _show(node->left, her + "l");

        for(int i = 0; i < ((int)her.size() - 1); i++){
            if(her[i] != her[i + 1])
                cout << "│   ";
            else
                cout << "    ";
        }
        if(her != ""){
            if(her.back() == 'l')
                cout << "<───";
            else
                cout << ">───";
        }
        if(node == nullptr){
            cout << "#" << endl;
            return;
        }
        cout << node->value;
        if(ref == node)
            cout << "(" << value << ")";
        cout << endl;

        if((node->left != nullptr) || (node->right != nullptr))
            _show(node->right, her + "r");
    }
    void show(bnode * ref = nullptr, int value = 0){
        cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVV" << endl;
        _show(root, "", ref, value);
        cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl << endl;
    }

};

#endif // BTREE_H