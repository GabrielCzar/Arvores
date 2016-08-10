#ifndef DCTREE_H
#define DCTREE_H
#include <iostream>
#include <DCNode.h>

struct DCTree{
    DCNode * root;

    DCTree (){
        root = new DCNode("*", gap);
    }

    DCTree (istream & serial){
        _dserialize (root, serial);
    }

    void dserialize(istream & serial){
        _dserialize (root, serial);
    }

    void show()
    {
        _show(root, 0, 0, root);
    }

    void criar()
    {
        _alterar(root);
    }

    void serialize(ostream & out)
    {
        _serialize(root, out);
    }

    void executar()
    {
        _executar(root, 0, 0);
    }

    ~DCTree (){
        _clear(root);
        root = nullptr;
    }

private:
    void _clear(DCNode * node){
        for (auto filho: node->filhos)
            _clear(filho);
        delete node;
    }


    void _show (DCNode * node, int nivel, int pos, DCNode * referencia){
        if (node == nullptr)
            return;
        char marker = (node == referencia) ? '>' : ' ';
        cout << marker;

        if(node == root)
            cout << node->value << endl;
        else
            cout << string(nivel * 4, marker) << pos << " - " << node->key << " : " << node->value << endl;

        for (int i = 0; i < (int)node->filhos.size(); i++)
            _show(node->filhos[i], nivel + 1, i, referencia);
    }

    void _executar(DCNode * node, int nivel, int pos){
        int op;

        if(node == root)
            cout << node->value << endl;
        else
            cout << string(nivel * 4, ' ') << pos << " - " << node->key << " : " << node->value << endl;

        if (!node->filhos.size())
            return;
        for (int i = 0; i < (int)node->filhos.size(); i++)
            cout << string((nivel + 1) * 4, ' ') << i << " - " << node->filhos[i]->key << endl;
        cout << "Digite a posicao de sua escolha: ";
        cin >> op;

        _executar(node->filhos[op], nivel + 1, op);
    }

    void _alterar (DCNode * node){
        while(true){
            _show(root, 0, 0, node);

            cout << "BACK | ADD _text | GO _num | VALUE _v | KEY _k | REM _num" << endl;

            string opcao;
            cin >> opcao;

            if (opcao == "ADD"){
                string texto;
                getline(cin, texto);
                node->filhos.push_back(new DCNode(texto.substr(1), gap));
            }
            if (opcao == "GO"){
                int pos;
                cin >> pos;
                _alterar(node->filhos[pos]);
            }
            if (opcao == "KEY"){
                string key;
                getline(cin, key);
                node->key = key.substr(1);
            }
            if (opcao == "VALUE"){
                string value;
                getline(cin, value);
                node->value = value.substr(1);
            }
            if (opcao == "REM"){
                int pos;
                cin >> pos;
                node->filhos.erase(node->filhos.begin() + pos);
            }
            if (opcao == "BACK")
                return;
        }
    }

    string converter(string text){
        for (int i = 0; i < (int)text.size(); ++i)
            if (text[i] == ' ')
                text[i] = '_';
        return text;
    }

    string dconverter(string text){
        for (int i = 0; i < (int)text.size(); ++i)
            if (text[i] == '_')
                text[i] = ' ';
        return text;
    }

    void _serialize (DCNode * node, ostream & out){
        if(node == nullptr)
            return;
        out << converter(node->key) << ' ' << converter(node->value) << ' ';
        for(auto filho: node->filhos)
            _serialize(filho, out);
        out << "# ";
    }

    int _dserialize (DCNode * &node, istream & serial){
        // Ler o proximo item do arquivo. Se nao a mais itens ou proximo
        // item is uma MARKER, entao retorna
        string key, value;
        serial >> key;
        if (key == "#")
           return 1;

        serial >> value;
        // Se nao cria o node com o item e chama a recursao para o filho
        node = new DCNode(dconverter(key), dconverter(value));

        for (int i = 0; /* ∞ */ ; i++){ //Nao ha limite porque nao se sabe o tamanho mas como é um arquivo ele tem limite(mesmo muito grande)
          auto aux = new DCNode;
          node->filhos.push_back(aux);
          if (_dserialize (node->filhos[i], serial)){
             node->filhos.pop_back();
             break;
          }
        }
        // Finalmente retorna 0 com sucesso
        return 0;

        ///Codigo adaptado do site http://www.geeksforgeeks.org/serialize-deserialize-n-ary-tree/
    }
};


#endif // DCTREE_H
