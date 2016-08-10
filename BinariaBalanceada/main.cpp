#include <iostream>
#include "../ArvoreRubroNegra/Headers/Tree.h"
#include "Libs/bTreeView.h"

using namespace std;

int main()
{
    srand(time(NULL));
    my_player->set_buffer_size(100);
    Tree tree;

    int value;

    for(int i = 0; i < 10; i++){
        value = rand();
        tree.insert(value % 10);
    }

    my_tview->paint_tree(tree.root);
    my_player->show();
    my_player->wait();

    tree.show();

    tree.balacear_tree();

    my_tview->paint_tree(tree.root);
    my_player->show();
    my_player->wait();


    return 0;
}
