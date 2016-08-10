#ifndef BTREEVIEW_H
#define BTREEVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//#include "../player/mplayer.h"
//#include "../player/sfline.h"
//#include "../player/sftext.h"
//#include "../player/colormap.h"
//#include "../player/mywindow.h"

#include "../ArvoreRubroNegra/Libs/Player.h"
#include "../ArvoreRubroNegra/Headers/Node.h"
#include "../ArvoreRubroNegra/Headers/Tree.h"

#include <queue>
#include <sstream>
#include <vector>

#define my_tview (BTreeView::instance())

class BTreeView{

private:
    int raio;
    float deltax;
    int deltay;
    sf::Color cor_nodo;
    sf::Color cor_borda;
    sf::Color cor_linha = sf::Color::White;
    sf::Color cor_fundo;
public:

    static BTreeView * instance(){
        static BTreeView stview;
        (void) stview;
        return &stview;
    }

private:

    BTreeView():
        raio(20),
        cor_nodo(153, 204, 0),
        cor_borda(77, 153, 0),
        cor_fundo(77, 77, 77)
    {
        deltax = raio * 0.6;
        deltay = 2 * raio;
    }


    int _calcular_largura(Node * n)
    {
        if (n == nullptr){
            return raio/2;
        }

        n->_asa_esq = _calcular_largura(n->left) + deltax;
        n->_asa_dir = _calcular_largura(n->right) + deltax;
        return n->_asa_dir + n->_asa_esq;
    }

    void _reposicionar(Node * n)
    {
        if (n == nullptr)
            return;
        if (n->left != nullptr) {
            n->left->_pos = n->_pos + sf::Vector2f(-n->left->_asa_dir, deltay);
            _reposicionar(n->left);
        }

        if (n->right != nullptr) {
            n->right->_pos = n->_pos + sf::Vector2f(n->right->_asa_esq, deltay);
            _reposicionar(n->right);
        }
    }

    void _draw_tree(Node * n)
    {
        if (n == nullptr)
            return;

        // Desenhando linhas
        if (n->left != nullptr){
            my_painel->draw(sfLine(n->_pos, n->left->_pos, 3, cor_linha));
        }
        if (n->right != nullptr){
            my_painel->draw(sfLine(n->_pos, n->right->_pos, 3, cor_linha));
        }

        _draw_node(n);


        _draw_tree(n->left);
        _draw_tree(n->right);

    }

    void _print_pos(Node *node, int nivel){
        if(node == nullptr){
            std::cout << std::string(2 * nivel, ' ') << "#" << std::endl;
            return;
        }
        _print_pos(node->left, nivel + 1);

        std::cout << std::string(2 * nivel, ' ') << "(" << node->_pos.x
                  << ", " << node->_pos.y << ")" << std::endl;

        _print_pos(node->right, nivel + 1);
    }

    void _draw_node(Node * n){
        sf::CircleShape noShape(raio);
        noShape.setOrigin(sf::Vector2f(raio, raio));
        noShape.setPosition(n->_pos);
        char char_color = n->color;
        sf::Color color =  my_colors->get(char_color);
        noShape.setFillColor(color);
        noShape.setOutlineColor(cor_borda);
        noShape.setOutlineThickness(1);

        // Desenhando no
        my_painel->draw(noShape);

        // Desenhando valor do no
        sfText text(n->_pos, std::to_string(n->value), sf::Color::Black, 20);
        sf::Vector2f v(text.getGlobalBounds().width/2, 10 + text.getGlobalBounds().height/2);
        text.setPosition(n->_pos - v);
        my_painel->draw(text);
    }

public:
    void paint_tree(Node * root, const std::string &msg = ""){
        _calcular_largura(root);
        root->_pos.x = my_painel->getSize().x/2;
        root->_pos.y = 70;
        _reposicionar(root);
        _draw_tree(root);
        //_print_pos(root, 0);

        cout << msg << endl;
        //my_painel->draw(sfText(sf::Vector2f(0, my_painel->getSize().y - 20), msg, my_player->color_front));
        //painel.display();
    }

    void focus_node(Node * ref_node, char color, int value){
        Node * aux = new Node(value);
        aux->color = color;
        aux->_pos = ref_node->_pos + sf::Vector2f(10, 10);
        _draw_node(aux);
        delete(aux);
    }


};
#endif // BTREEVIEW_H
