#ifndef DCNODE_H
#define DCNODE_H
#include <iostream>

const string gap = "VAZIO";

struct DCNode{
    string key; //Resposta
    string value; //Pergunta ou Afirmacao
    vector<DCNode *> filhos; //Possiveis respostas

    DCNode (string key = gap, string value = gap){
        this->key = key;
        this->value = value;
    }

};


#endif // DCNODE_H
