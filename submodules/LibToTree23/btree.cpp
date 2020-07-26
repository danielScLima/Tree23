#include "btree.h"
#include <queue>

BTree::BTree(int degree):
    degree(degree)
{

}

BTree::~BTree()
{
    dealockNodeOfBTrees();
}

void BTree::dealockNodeOfBTrees()
{
    if (root != nullptr)
    {
        root->dealockSubTree();
        delete root;
    }
}

int BTree::getDegree()
{
    return this->degree;
}

int BTree::entriesSize()
{
    return this->degree - 1;
}

std::string BTree::getDotFileContent()
{
    std::string msg = "digraph g { ";
    msg += "ROOT [shape=none fontcolor=blue];";
    msg += "node [shape=record, height=0.1];";

    std::string msgLinks;

    std::queue<NodeOfBTree*> queue;

    if (root != nullptr)
        queue.push(root);
    while(queue.size() > 0)
    {
        NodeOfBTree* nodeOfBTree = queue.front(); //acessa o primeiro
        queue.pop(); //remove o primeiro

        nodeOfBTree->getDotFileRepresentation(msg);
        std::vector<NodeOfBTree *> vec = nodeOfBTree->getVectorOfPointers();
        for (auto pointer: vec)
        {
            queue.push(pointer);
            msgLinks += "\""+nodeOfBTree->getNodeName()+"\"->\""+pointer->getNodeName()+"\";";
        }
    }

    if (root != nullptr)
    {
        std::string rootName = root->getNodeName();
        msg += "ROOT->\""+rootName+"\";";
    }

    msg += msgLinks;

    msg += "}";

    return msg;
}

bool BTree::insert(int number)
{
    if (root == nullptr)
        root = new NodeOfBTree(nullptr, this->degree);
    return root->insert(number);
}

NodeOfBTree* BTree::search(int number)
{
    NodeOfBTree* temp = root;
    bool goToNext = false;
    while (true)
    {
        const std::vector<int> vec = temp->getVectorOfEntries();
        for (int index = 0; index < vec.size(); ++index)
        {
            if (number == vec[index])
                return temp;
            else if (number < vec[index])
            {
                if (index < temp->getVectorOfPointers().size())
                {
                    temp = temp->pointerByIndex(index);
                    goToNext = true;
                    break;
                }
                else
                    return nullptr;
            }
        }
        if (goToNext == false)
        {
            //Verificar no último ponteiro
            if (temp->getVectorOfPointers().size() > 1) //deve ter pelo menos 2 ponteiros
            {
                temp = temp->getVectorOfPointers().back();
            }
            else
                return nullptr;
        }
        else
        {
            goToNext = false;
        }
    }
    return nullptr;
}

bool BTree::remove(int number)
{
    int maxSize = degree-1;
    NodeOfBTree* n = search(number);
    if (n == nullptr)
        return false;
    else
    {
        //Verifica se o nó é uma folha
        if (n->getVectorOfPointers().size() == 0)
        {
            //caso 1: Verifica se tem mais elementos do que a metade
            //do tamanho máximo (antes de remover)
            int size = n->getVectorOfEntries().size();
            if (size > maxSize/2)
            {
                //A função abaixo remove posições internas do vetor tmb
                n->removeEntryOfVectorOfEntries(number);
            }
            else
            {
                //remove
                n->removeEntryOfVectorOfEntries(number);

                //verifica como resolver, se for preciso
                size = n->getVectorOfEntries().size();
                if (size < maxSize/2)
                    fixNodeOfBTreeWithSmallCountOfElements(n);
            }
        }
        else //Não é uma folha
        {
            //caso 2: troca com o seu antecessor
            //isso implica em remover do antecessor um numero (o maior)
            //Pode ter que resolver o problema do antecessor
            NodeOfBTree* ancestor = getAncestor(n, number);
            int numberAncestor = ancestor->getVectorOfEntries().back();
            ancestor->removeEntryOfVectorOfEntries(numberAncestor);

            //ancestor é folha, não tem ponteiros filhos

            //Em n, troca o número number por numberAncestor
            n->replaceEntryInVectorOfEntries(number, numberAncestor);

            //Verifica se tem que resolver e resolve, se necessário
            int size = ancestor->getVectorOfEntries().size();
            if (size < maxSize/2)
                fixNodeOfBTreeWithSmallCountOfElements(ancestor);
        }

        return true;
    }
}

NodeOfBTree *BTree::getRoot()
{
    return this->root;
}

NodeOfBTree* BTree::getAncestor(NodeOfBTree * nodeOfBTree, int number)
{
    int pos = 0;
    std::vector<int> vecOfEntries = nodeOfBTree->getVectorOfEntries();
    for (int index = 0; index < vecOfEntries.size(); ++index)
    {
        if (vecOfEntries[index] == number)
            pos = index;
    }

    NodeOfBTree* nodeOfBTreePointer = nodeOfBTree->getVectorOfPointers().at(pos);
    while (nodeOfBTreePointer->getVectorOfPointers().size() > 0)
    {
        nodeOfBTreePointer = nodeOfBTreePointer->getVectorOfPointers().back();
    }
    return nodeOfBTreePointer;
}

void BTree::fixNodeOfBTreeWithSmallCountOfElements(NodeOfBTree *NodeOfBTreeToFix)
{
    int maxSize = degree-1;
    if (NodeOfBTreeToFix->getVectorOfEntries().size() >= maxSize/2)
        return; //está resolvido

    if (NodeOfBTreeToFix == root) //o root pode ter menos elementos
    {
        if (NodeOfBTreeToFix->getVectorOfEntries().size() == 0)
        {
            //juntar filhos
            //Tem 2 filhos restantes (pelas propriedades da remoção)
            std::vector<NodeOfBTree*> pointers = NodeOfBTreeToFix->getVectorOfPointers();
            for (auto tmp: pointers)
            {
                while (tmp->getVectorOfEntries().size() > 0)
                {
                    int first = tmp->removeFirstPositionOfVectorOfEntries();
                    NodeOfBTreeToFix->insertInLastPositionOfVectorOfEntries(first);
                }
            }
            while (NodeOfBTreeToFix->getVectorOfPointers().size() > 0)
            {
                //change 1 is here
                NodeOfBTree* n = NodeOfBTreeToFix->removeLastPointer();

				//só removeu da lista do nodetofix
            }

            std::vector<NodeOfBTree*> childrens;
            for (auto tmp: pointers)
            {
                while (tmp->getVectorOfPointers().size() > 0)
                {
                    NodeOfBTree* firstP = tmp->removeFirstPointer();
                    childrens.push_back(firstP);
                }
            }
            for (auto ptr: childrens)
            {
                NodeOfBTreeToFix->insertInLastPositionOfVectorOfPointers(ptr);
                ptr->setFather(NodeOfBTreeToFix);
            }
			//aqui sim, deletar
			for (auto tmp : pointers)
			{
				delete tmp;
			}
        }

        return;
    }

    int indexFound = 0;
    //Verifica se pode obter de algum irmão, um valor excedente
    NodeOfBTree* father = NodeOfBTreeToFix->getFather();
    std::vector<NodeOfBTree *> pointers = father->getVectorOfPointers();
    for (int index = 0; index < pointers.size(); ++index)
    {
        if (NodeOfBTreeToFix == pointers[index])
        {
            indexFound = index;
            //Verifica o irmão esquerdo, se tiver
            if (index >= 1)
            {
                NodeOfBTree* leftBrother = pointers[index-1];
                if (leftBrother->getVectorOfEntries().size() > maxSize/2)
                {
                    //faz e retorna
                    //Este faz não esta considerando ponteiros filhos
                    int last = leftBrother->removeLastPositionOfVectorOfEntries();
                    int top = father->entryByIndex(index-1); // obtem o numero de cima
                    father->setEntryByIndex(index-1, last);
                    //insere número de cima na posição zero de NodeOfBTreeToFix
                    NodeOfBTreeToFix->insertInFirstPositionOfVectorOfEntries(top);

                    //Verificar se tem irmão da direita
                    //Verifica se o irmao tem ponteiro. Se tiver, remove o ultimo
                    if (leftBrother->getVectorOfPointers().size() > 0 &&
                            (index+1) < pointers.size())
                    {
                        NodeOfBTree* last = leftBrother->removeLastPointer();
                        NodeOfBTree* rightBrother = pointers[index+1];
                        rightBrother->insertInFirstPositionOfVectorOfPointers(last);
                        last->setFather(rightBrother);
                    }

                    return;
                }
            }

            if (index < pointers.size()-1)
            {
                NodeOfBTree* rightBrother = pointers[index+1];
                if (rightBrother->getVectorOfEntries().size() > maxSize/2)
                {
                    //faz e retorna
                    //Este faz não esta considerando ponteiros filhos
                    int first = rightBrother->removeFirstPositionOfVectorOfEntries();
                    int top = father->entryByIndex(index); // obtem o numero de cima
                    father->setEntryByIndex(index, first);
                    NodeOfBTreeToFix->insertInLastPositionOfVectorOfEntries(top);

                    //Verificar se tem irmão da direita
                    //Verifica se o irmao tem ponteiro. Se tiver, remove o ultimo
                    if (rightBrother->getVectorOfPointers().size() > 0 &&
                            (index-1) >= 0)
                    {
                        NodeOfBTree* first = rightBrother->removeFirstPointer();
                        NodeOfBTree* leftBrother = pointers[index-1];
                        leftBrother->insertInFirstPositionOfVectorOfPointers(first);
                        first->setFather(leftBrother);
                    }

                    return;
                }
            }

            break; //tratar fora do laço
        }
    }

    //Se chegou aqui, é porque nem o esquerdo, nem o direito, tinham
    //possibilidade de ajudar
    //Junta com o irmão esquerdo (podia ser o direito também)
    if (indexFound > 0) //tem irmão esquerdo
    {
        //Juntar com o esquerdo
        //deletar o esquerdo
        //Remover primeira entrada do pai (valor)
        int top = father->entryByIndex(indexFound-1);
        father->removeByIndexInVectorOfEntries(indexFound-1);
        NodeOfBTreeToFix->insertInFirstPositionOfVectorOfEntries(top);
        NodeOfBTree* leftBrother = pointers[indexFound-1];
        while(leftBrother->getVectorOfEntries().size() > 0)
        {
            int last = leftBrother->removeLastPositionOfVectorOfEntries();
            NodeOfBTreeToFix->insertInFirstPositionOfVectorOfEntries(last);
        }
        while(leftBrother->getVectorOfPointers().size() > 0)
        {
            NodeOfBTree* pointer = leftBrother->removeLastPointer();
            NodeOfBTreeToFix->insertInFirstPositionOfVectorOfPointers(pointer);
            pointer->setFather(NodeOfBTreeToFix);
        }

        //remover o left do pai
        father->removePointerOfVectorOfPointers(indexFound-1);
        //Deve propagar checagens para cima
        //mas agora não

        delete leftBrother;
    }
    else if (indexFound < pointers.size()-1) //tem irmão direito
    {
        //Juntar com o direito
        int top = father->entryByIndex(indexFound);
        father->removeByIndexInVectorOfEntries(indexFound);
        NodeOfBTreeToFix->insertInLastPositionOfVectorOfEntries(top);
        NodeOfBTree* rightBrother = pointers[indexFound+1];
        while(rightBrother->getVectorOfEntries().size() > 0)
        {
            int first = rightBrother->removeFirstPositionOfVectorOfEntries();
            NodeOfBTreeToFix->insertInLastPositionOfVectorOfEntries(first);
        }
        while(rightBrother->getVectorOfPointers().size() > 0)
        {
            NodeOfBTree* pointer = rightBrother->removeFirstPointer();
            NodeOfBTreeToFix->insertInLastPositionOfVectorOfPointers(pointer);
            pointer->setFather(NodeOfBTreeToFix);
        }

        //remover o right do pai
        father->removePointerOfVectorOfPointers(indexFound+1);
        
        delete rightBrother;
    }

    if (father->getVectorOfEntries().size() < maxSize/2)
        fixNodeOfBTreeWithSmallCountOfElements(father);
}
