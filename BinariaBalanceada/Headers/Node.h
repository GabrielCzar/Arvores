#ifndef NODE_H
#define NODE_H

#include <SFML/System/Vector2.hpp>

//essas variaveis sao utilizadas para o desenho
struct nodeview{
    sf::Vector2f _pos;
    float _asa_esq;
    float _asa_dir;
    char color{'g'};
};

struct Node : public nodeview{
    int value;
    Node * left;
    Node * right;

    Node (int value, Node * left = nullptr, Node * right = nullptr){
        this->value = value;
        this->left = left;
        this->right = right;
    }
};

#endif // NODE_H
