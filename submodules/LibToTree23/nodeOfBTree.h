#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>

/*!
 * \brief The NodeOfBTree class
 */
class NodeOfBTree
{
public:
    /*!
     * \brief NodeOfBTree
     * \param father
     * \param degree
     */
    NodeOfBTree(NodeOfBTree* father, int degree);

    /*!
     * \brief dealockSubTree
     */
    void dealockSubTree();

    /*!
     * \brief getFather
     * \return
     */
    NodeOfBTree* getFather();

    /*!
     * \brief setFather
     * \param father
     */
    void setFather(NodeOfBTree* father);

    /*!
     * \brief entryByIndex
     * \param index
     * \return
     */
    int entryByIndex(int index);

    /*!
     * \brief setEntryByIndex
     * \param index
     * \param number
     */
    void setEntryByIndex(int index, int number);

    /*!
     * \brief pointerByIndex
     * \param index
     * \return
     */
    NodeOfBTree* pointerByIndex(int index);

    /*!
     * \brief setDegree
     * \param degree
     */
    void setDegree(int degree);

    /*!
     * \brief getDotFileRepresentation
     * \param msg
     */
    void getDotFileRepresentation(std::string &msg);

    /*!
     * \brief getVectorOfPointers
     * \return
     */
    std::vector<NodeOfBTree*> getVectorOfPointers();

    /*!
     * \brief getNodeName
     * \return
     */
    const std::string getNodeName();

    /*!
     * \brief insert
     * \param number
     * \return
     */
    bool insert(int number);

    /*!
     * \brief receiveNodeToInsertFromDownside
     * \param originalNode
     * \param left
     * \param right
     * \param numberToInsert
     */
    void receiveNodeToInsertFromDownside
    (
        NodeOfBTree *originalNode,
        NodeOfBTree *left,
        NodeOfBTree *right,
        int numberToInsert
    );

    /*!
     * \brief getVectorOfEntries
     * \return
     */
    std::vector<int> getVectorOfEntries();

    /*!
     * \brief removeEntryOfVectorOfEntries
     * \param number
     */
    void removeEntryOfVectorOfEntries(int number);

    /*!
     * \brief removeLastPositionOfVectorOfEntries
     * \return
     */
    int removeLastPositionOfVectorOfEntries();

    /*!
     * \brief removeFirstPositionOfVectorOfEntries
     * \return
     */
    int removeFirstPositionOfVectorOfEntries();

    /*!
     * \brief insertInFirstPositionOfVectorOfEntries
     * \param number
     */
    void insertInFirstPositionOfVectorOfEntries(int number);

    /*!
     * \brief insertInLastPositionOfVectorOfEntries
     * \param number
     */
    void insertInLastPositionOfVectorOfEntries(int number);

    /*!
     * \brief replaceEntryInVectorOfEntries
     * \param number
     * \param ancestorNumber
     */
    void replaceEntryInVectorOfEntries(int number, int ancestorNumber);

    /*!
     * \brief removeLastPointer
     * \return
     */
    NodeOfBTree *removeLastPointer();

    /*!
     * \brief removeFirstPointer
     * \return
     */
    NodeOfBTree *removeFirstPointer();

    /*!
     * \brief insertInFirstPositionOfVectorOfPointers
     * \param pointer
     */
    void insertInFirstPositionOfVectorOfPointers(NodeOfBTree *pointer);

    /*!
     * \brief insertInLastPositionOfVectorOfPointers
     * \param pointer
     */
    void insertInLastPositionOfVectorOfPointers(NodeOfBTree *pointer);

    /*!
     * \brief removeByIndexInVectorOfEntries
     * \param index
     */
    void removeByIndexInVectorOfEntries(int index);

    /*!
     * \brief removePointerOfVectorOfPointers
     * \param index
     */
    void removePointerOfVectorOfPointers(int index);
private:
    int degree = 2;
    NodeOfBTree* father = nullptr;

    std::vector<int> vectorOfEntries;
    std::vector<NodeOfBTree*> vectorOfPointers;
};

#endif // NODE_H
