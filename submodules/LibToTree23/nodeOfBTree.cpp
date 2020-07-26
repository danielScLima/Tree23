#include "nodeOfBTree.h"
#include <algorithm>
#include <string>

NodeOfBTree::NodeOfBTree(NodeOfBTree* father, int degree):
    degree(degree), father(father)
{

}

void NodeOfBTree::dealockSubTree()
{
    NodeOfBTree* child = nullptr;
    for (int index = 0; index < vectorOfPointers.size(); ++index)
    {
        child = vectorOfPointers.at(index);
        if (child != nullptr)
        {
            child->dealockSubTree();
            delete child;
            vectorOfPointers[index] = nullptr;
        }
    }

    vectorOfPointers.clear();
    vectorOfEntries.clear();
}

NodeOfBTree *NodeOfBTree::getFather()
{
    return this->father;
}

void NodeOfBTree::setFather(NodeOfBTree *father)
{
    this->father = father;
}

void NodeOfBTree::removeEntryOfVectorOfEntries(int number)
{
    std::vector<int>::iterator position = std::find
    (
        vectorOfEntries.begin(),
        vectorOfEntries.end(),
        number
    );
    if (position != vectorOfEntries.end())
        vectorOfEntries.erase(position);
}

void NodeOfBTree::removePointerOfVectorOfPointers(int index)
{
    vectorOfPointers.erase(vectorOfPointers.begin()+index);
}

int NodeOfBTree::removeLastPositionOfVectorOfEntries()
{
    int last = vectorOfEntries.back();
    vectorOfEntries.pop_back();
    return last;
}

int NodeOfBTree::removeFirstPositionOfVectorOfEntries()
{
    int first = vectorOfEntries.front();
    vectorOfEntries.erase(vectorOfEntries.begin());
    return first;
}

NodeOfBTree* NodeOfBTree::removeLastPointer()
{
    NodeOfBTree* last = vectorOfPointers.back();
    vectorOfPointers.pop_back();
    return last;
}

NodeOfBTree* NodeOfBTree::removeFirstPointer()
{
    NodeOfBTree* first = vectorOfPointers.front();
    vectorOfPointers.erase(vectorOfPointers.begin());
    return first;
}

void NodeOfBTree::insertInFirstPositionOfVectorOfEntries(int number)
{
    vectorOfEntries.insert(vectorOfEntries.begin(), number);
}

void NodeOfBTree::insertInFirstPositionOfVectorOfPointers(NodeOfBTree* pointer)
{
    vectorOfPointers.insert(vectorOfPointers.begin(), pointer);
}

void NodeOfBTree::insertInLastPositionOfVectorOfEntries(int number)
{
    vectorOfEntries.push_back(number);
}

void NodeOfBTree::insertInLastPositionOfVectorOfPointers(NodeOfBTree* pointer)
{
    vectorOfPointers.push_back(pointer);
}

void NodeOfBTree::replaceEntryInVectorOfEntries(int number, int ancestorNumber)
{
    std::replace
    (
        vectorOfEntries.begin(),
        vectorOfEntries.end(),
        number,
        ancestorNumber
    );
}

std::vector<int> NodeOfBTree::getVectorOfEntries()
{
    return this->vectorOfEntries;
}

void NodeOfBTree::removeByIndexInVectorOfEntries(int index)
{
    if (index < vectorOfEntries.size())
        vectorOfEntries.erase(vectorOfEntries.begin()+index);
    else
        throw std::invalid_argument("Invalid index");
}

int NodeOfBTree::entryByIndex(int index)
{
    if (index < vectorOfEntries.size())
        return vectorOfEntries.at(index);
    else
        throw std::invalid_argument("Invalid index");
}

void NodeOfBTree::setEntryByIndex(int index, int number)
{
    if (index < vectorOfEntries.size())
        vectorOfEntries[index] = number;
}

NodeOfBTree *NodeOfBTree::pointerByIndex(int index)
{
    if (index < this->vectorOfPointers.size())
        return this->vectorOfPointers.at(index);
    else
        throw std::invalid_argument("Invalid index");
}

void NodeOfBTree::setDegree(int degree)
{
    this->degree = degree;
}

const std::string NodeOfBTree::getNodeName()
{
    std::string name;
    int maxEntries = this->degree - 1;
    for (int index = 0; index < maxEntries; ++index)
    {
        if (index < vectorOfEntries.size())
            name += std::to_string(vectorOfEntries[index]);
        else
            name += "-";

        if (index < maxEntries-1)
            name += "_";
    }
    return name;
}

bool NodeOfBTree::insert(int number)
{
    //apenas para ter algo
    bool numberInserted = false;
    bool stopProcessHere = false;

    int maxEntries = this->degree - 1;
    for (int index = 0; index < this->vectorOfEntries.size(); ++index)
    {
        if (number == vectorOfEntries[index])
            return false;
        if (number < vectorOfEntries[index])
        {
            //Existe um ponteiro com posição: index?
            //Se sim, manda inserir neste ponteiro
            if (index < vectorOfPointers.size())
            {
                bool ret = vectorOfPointers[index]->insert(number);
                if (!ret)
                    return false;
                stopProcessHere = true;
                break;
            }
            else //Se não, insere no nó atual, deslocando
            {
                //Verifica se tem espaço nesse nó
                //Deve verificar a quantidade de entradas
                //se é menor que a máxima
                if (this->vectorOfEntries.size() < maxEntries)
                {
                    //A chamada abaixo já desloca as entradas
                    vectorOfEntries.insert(vectorOfEntries.begin()+index, number);
                    numberInserted = true;
                    break;
                }
            }
        }
    }

    if (numberInserted || stopProcessHere)
    {
        //não tem mais nada a fazer
    }
    else
    {
        if (this->vectorOfEntries.size() < maxEntries)
        {
            //Insere depois do último
            //Se esse ponteirofor diferente de null, insere lá
            int sizeEntries = this->vectorOfEntries.size();
            if (sizeEntries < vectorOfPointers.size() &&
                    vectorOfPointers.back() != nullptr)
            {
                bool ret = vectorOfPointers.back()->insert(number);
                if (!ret)
                    return false;
            }
            else
            {
                this->vectorOfEntries.push_back(number);
                numberInserted = true;
            }
        }
        else //tem q inserir e quebrar
        {
            if
            (
                vectorOfPointers.size() > vectorOfEntries.size() &&
                vectorOfPointers.back() != nullptr
            )
            {
                bool ret = vectorOfPointers.back()->insert(number);
                if (!ret)
                    return false;
            }
            else
            {

                //Neste ponto o novo número é maior que todos os numeros existentes
                //Deve verificar se o pai é nulo ou não
                //se for nulo (é o root), faz o codigo abaixo
                if (father == nullptr)
                {
                    numberInserted = false;
                    int pos = -1;
                    for (int index = 0; index < this->vectorOfEntries.size(); ++index)
                    {
                        if (number == vectorOfEntries[index])
                            return false;
                        if (number < vectorOfEntries[index])
                        {
                            vectorOfEntries.insert(vectorOfEntries.begin()+index, number);
                            numberInserted = true;
                            pos = index;
                            break;
                        }
                    }
                    if (numberInserted == false)
                        vectorOfEntries.push_back(number);

                    int middle = maxEntries / 2;
                    //Neste ponto existe uma entrada a mais
                    //end of new

                    //Deve quebrar o nó, pois a quantidade de elementos lotou
                    //Deve saber qual a ordem de inserção
                    NodeOfBTree* left = new NodeOfBTree(this, this->degree);
                    NodeOfBTree* right = new NodeOfBTree(this, this->degree);
                    for (int index = 0; index < middle; ++index)
                    {
                        left->insert(vectorOfEntries[index]);
                    }
                    for (int index = middle+1; index < vectorOfEntries.size(); ++index)
                    {
                        right->insert(vectorOfEntries[index]);
                    }
                    int backupNumber = vectorOfEntries[middle];
                    vectorOfEntries.clear();
                    vectorOfPointers.clear();
                    vectorOfEntries.push_back(backupNumber);
                    vectorOfPointers.push_back(left);
                    vectorOfPointers.push_back(right);
                }
                else
                {
                    //Deve dividir e enviar para o pai receber
                    //pai recebe:
                    //O ponteiro antigo (ele não deve ser mais usado)
                    //Os dois novos ponteiros
                    //O valor que deve ser recebido

                    //Deve quebrar o nó, pois a quantidade de elementos lotou
                    //Deve saber qual a ordem de inserção
                    numberInserted = false;
                    int pos = -1;
                    for (int index = 0; index < this->vectorOfEntries.size(); ++index)
                    {
                        if (number == vectorOfEntries[index])
                            return false;
                        if (number < vectorOfEntries[index])
                        {
                            vectorOfEntries.insert(vectorOfEntries.begin()+index, number);
                            numberInserted = true;
                            pos = index;
                            break;
                        }
                    }
                    if (numberInserted == false)
                        vectorOfEntries.push_back(number);

                    int middle = maxEntries / 2;

                    NodeOfBTree* left = new NodeOfBTree(this, this->degree);
                    NodeOfBTree* right = new NodeOfBTree(this, this->degree);
                    for (int index = 0; index < middle; ++index)
                    {
                        left->insert(vectorOfEntries[index]);
                    }
                    for (int index = middle+1; index < vectorOfEntries.size(); ++index)
                    {
                        right->insert(vectorOfEntries[index]);
                    }
                    int backupNumber = vectorOfEntries[middle];

                    vectorOfEntries.clear();
                    vectorOfPointers.clear();

                    //faz chamada para o pai receber tudo
                    father->receiveNodeToInsertFromDownside
                    (
                        this,
                        left,
                        right,
                        backupNumber
                    );
                }
            }
        }
    }

    return true;
}

void NodeOfBTree::receiveNodeToInsertFromDownside
(
    NodeOfBTree* originalNode,
    NodeOfBTree* left,
    NodeOfBTree* right,
    int numberToInsert
)
{
    left->father = this;
    right->father = this;

    int maxEntries = this->degree - 1;

    //caso no qual o nó não está full, assim ele não se divide
    int insertionPosition = 0;

    for (int index = 0; index < this->vectorOfPointers.size(); ++index)
    {
        if (vectorOfPointers[index] == originalNode)
        {
            insertionPosition = index;
        }
    }

    if (insertionPosition == vectorOfEntries.size())
    {
        vectorOfEntries.push_back(numberToInsert);
    }
    else //é menor
    {
        vectorOfEntries.insert
        (
            vectorOfEntries.begin()+insertionPosition,
            numberToInsert
        );
    }

    if (vectorOfPointers.size() == 0)
    {
        vectorOfPointers.push_back(left);
        vectorOfPointers.push_back(right);
    }
    else
    {
    	//verifiy the cleanup
    	if (vectorOfPointers.size() > insertionPosition)
    	{
    		if (vectorOfPointers.at(insertionPosition) != left && vectorOfPointers.at(insertionPosition) != right)
    			delete vectorOfPointers.at(insertionPosition);
    	}
    
        vectorOfPointers[insertionPosition] = left;
        vectorOfPointers.insert(vectorOfPointers.begin()+insertionPosition+1, right);
    }

    if (vectorOfEntries.size() > maxEntries)
    {
        if (father == nullptr)
        {
            int middle = vectorOfEntries.size() / 2;

            NodeOfBTree* leftMe = new NodeOfBTree(this, this->degree);
            NodeOfBTree* rightMe = new NodeOfBTree(this, this->degree);
            for (int index = 0; index < middle; ++index)
            {
                leftMe->insert(vectorOfEntries[index]);
            }
            for (int index = middle+1; index < vectorOfEntries.size(); ++index)
            {
                rightMe->insert(vectorOfEntries[index]);
            }
            int backupNumber = vectorOfEntries[middle];

            for (int index = 0; index <= middle; ++index)
            {
                vectorOfPointers[index]->father = leftMe;
                leftMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }
            for (int index = middle+1; index < vectorOfPointers.size(); ++index)
            {
                vectorOfPointers[index]->father = rightMe;
                rightMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }

            vectorOfEntries.clear();
            vectorOfPointers.clear();
            vectorOfEntries.push_back(backupNumber);
            vectorOfPointers.push_back(leftMe);
            vectorOfPointers.push_back(rightMe);
        } //fim de root
        else //quando não é root o full
        {
            int middle = vectorOfEntries.size() / 2;

            NodeOfBTree* leftMe = new NodeOfBTree(this, this->degree);
            NodeOfBTree* rightMe = new NodeOfBTree(this, this->degree);
            for (int index = 0; index < middle; ++index)
            {
                leftMe->insert(vectorOfEntries[index]);
            }
            for (int index = middle+1; index < vectorOfEntries.size(); ++index)
            {
                rightMe->insert(vectorOfEntries[index]);
            }
            int backupNumber = vectorOfEntries[middle];

            for (int index = 0; index <= middle; ++index)
            {
                vectorOfPointers[index]->father = leftMe;
                leftMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }
            for (int index = middle+1; index < vectorOfPointers.size(); ++index)
            {
                vectorOfPointers[index]->father = right;
                rightMe->vectorOfPointers.push_back(vectorOfPointers[index]);
            }

            vectorOfEntries.clear();
            vectorOfPointers.clear();

            //faz chamada para o pai receber tudo
            father->receiveNodeToInsertFromDownside
            (
                this,
                leftMe,
                rightMe,
                backupNumber
            );
        }
    }
}

void NodeOfBTree::getDotFileRepresentation(std::string & msg)
{
    int maxEntries = this->degree - 1;
    std::string name = getNodeName();

    msg += "\""+name+"\" [label = \"";

    //Inserir as partes internas
    for (int index = 0; index < maxEntries; ++index)
    {
        msg += "<"+std::to_string(index)+"> ";

        if (index < vectorOfEntries.size())
        {
            msg += std::to_string(vectorOfEntries[index])+" ";
        }

        if (index < maxEntries-1)
            msg += "| ";
    }

    msg += "\"];";
}

std::vector<NodeOfBTree *> NodeOfBTree::getVectorOfPointers()
{
    return this->vectorOfPointers;
}
