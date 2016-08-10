#include <iostream> //COUT
#include <vector>
#include <fstream> //ARQUIVOS

using namespace std;

int main()
{
    /**

- Criação interativa da árvore de decisão: com capacidade para: inserir, remover, alterar nós.  OK
- Cada pergunta terá pelo menos duas respostas.                                                 NOT NOT
- Ao sair do programa a árvore deverá ser serializada e salva em um arquivo de texto.           NOT ok
- Ao iniciar o programa a árvore deverá ser carregada do arquivo de texto.                      NOT ok
- Modo de jogo onde o usuário vai fazendo as escolhas até chegar em uma decisão.                NOT

    **/

    DCTree tree; //Cria a arvore padrao
    string arq = "DecisionTree.txt"; //Arquivo para salvar/carregar arvore
    string opcao;
    //CASO NECESSITE QUE A ARVORE SEJA CARREGADA AO INICIAR A APLICACAO DESCOMENTE AS LINHAS ABAIXO
    //ifstream arquivo(arq);
    //tree.dserialize(arquivo);
    //arquivo.close();

    do
    {

        cout << "CRIAR - Cria ou altera a arvore de decisão!" << endl;
        cout << "CARREGAR - Carrega arvore de decisão de um arquivo!" << endl;
        cout << "INICIAR - Executa a arvore de decisao!" << endl;
        cout << "SALVAR - Salva a arvore de decisao em arquivo!" << endl;
        cout << "SAIR - Sai e salva à arvore em arquivo!" << endl;
        cin >> opcao;
        cout << endl;

        if (opcao == "CRIAR")
            tree.criar();

        if (opcao == "CARREGAR"){
            ifstream arquivo(arq); //Abre arquivo para leitura
            tree.dserialize(arquivo);
            tree.show();
            arquivo.close();
        }
        if (opcao == "INICIAR"){
            tree.executar();
        }
        if (opcao == "SAIR" || opcao == "SALVAR"){
            ofstream arquivo(arq); //Abre arquivo para escrita e truca os dados
            tree.serialize(arquivo);
            arquivo.close();
        }
        cout << endl;

    }
    while(opcao != "SAIR");

    return 0;
}

