#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <sstream>
#include <iostream>
#include "../Balanceada/Headers/Node.h"
#include "../Libs/bTreeView.h"

struct Tree {
    Node * root {nullptr};

    Tree (){}

    ~Tree (){
        this->clear();
    }

    void clear(){
        _clear(root);
        root = nullptr;
    }

    void _clear(Node *node){
        if(node == nullptr)
            return;
        _clear(node->left);
        _clear(node->right);
        delete(node);
    }

    void insert (int value){
        root = _insert(root, value);
    }

    Node * _insert(Node * node, int value){
        if(node == nullptr)
            return new Node(value);
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

    int _size(Node * node){
        if(node == nullptr)
            return 0;
        return 1 + _size(node->left) + _size(node->right);
    }

    int size(){
        return _size(root);
    }

//    bool eh_balanceada(){
//        if(root == nullptr)
//            return true;
//        return std::abs(altura(root->left) - altura(root->right)) < 2;
//    }

    void rotacao_esquerda (Node * &node){
        auto aux = node;
        node = aux->right;
        aux->right = node->left == nullptr ? nullptr : node->left;
        node->left = aux;
    }

    void rotacao_direita (Node * &node){
        auto aux = node;
        node = aux->left;
        aux->left = (node->right != nullptr) ? node->right : nullptr;
        node->right = aux;
    }

    void rotacao_dupla_esquerda (Node * &node){
        rotacao_direita(node->right);
        rotacao_esquerda(node);
    }

    void rotacao_dupla_direita (Node * &node){
        rotacao_esquerda(node->left);
        rotacao_direita(node);
    }

    void balancear(Node * &node){
        if (node == nullptr)
            return;

        balancear(node->left);
        balancear(node->right);

        int fb = is_balanceada(node);
        cout << "+value: " << node->value << " balanceada: " << fb << endl;
        if (fb >= -1 && fb <= 1)
            return;
        else if (fb > 1){
            if (is_balanceada(node->right) < 0)
                rotacao_dupla_esquerda(node);
            else
                rotacao_esquerda(node);
        }else if (fb < -1){
            if (is_balanceada(node->left) > 0)
                rotacao_dupla_direita(node);
            else
                rotacao_direita(node);
        }

    }

    void balancear_no (Node * node){
        balancear(node);
    }

    void balacear_tree (){
        balancear(root);
    }

    int is_balanceada (Node * node){
        if (node == nullptr)
            return 0;
        return altura(node->right) - altura(node->left);
    }


    int altura (Node * node) {
       if (node == nullptr)
          return -1; // altura da árvore vazia;
       return std::max(1 + altura (node->left), 1 + altura (node->right));
    }

    int altura(){
        return altura(root);
    }

    int roubar_e_matar(Node * node, Node ** elo){
        if(node ->right == nullptr){
            int value = node->value;
            _kill(node,elo);
            return value;
        }
        return roubar_e_matar(node->right, &node->right);
    }

    void _kill(Node * node, Node  ** elo){
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

    bool _remove(Node * node, int value, Node ** elo){
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

    Node ** _smart_find(Node * node, int value, Node ** elo){
        if(node == nullptr || node->value == value)
            return elo;
        if(value < node->value)
            return _smart_find(node->left, value, &node->left);
        return _smart_find(node->right, value, &node->right);
    }

    Node ** smart_find(int value){
        return _smart_find(root, value, &root);
    }

    void _show(Node * node, string her, Node * ref = nullptr, int value = 0){
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

    void show(Node * ref = nullptr, int value = 0){
        cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVVV" << endl;
        _show(root, "", ref, value);
        cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl << endl;
    }
};

#endif // TREE_H
