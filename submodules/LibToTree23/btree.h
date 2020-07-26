#ifndef BTREE_H
#define BTREE_H

#include "nodeOfBTree.h"
#include <iostream>

/*!
 * \brief The BTree class
 */
class BTree
{
public:
    /*!
     * \brief BTree
     * \param degree
     */
    BTree(int degree = 4);
    ~BTree();

    /*!
     * \brief getDegree
     * \return
     */
    int getDegree();
    /*!
     * \brief entriesSize
     * \return
     */
    int entriesSize();

    /*!
     * \brief getDotFileContent
     * \return
     */
    std::string getDotFileContent();

    /*!
     * \brief insert
     * \param number
     */
    bool insert(int number);
    /*!
     * \brief search
     * \param number
     * \return
     */
    NodeOfBTree* search(int number);
    /*!
     * \brief remove
     * \param number
     * \return
     */
    bool remove(int number);

    /*!
     * \brief getRoot
     * \return
     */
    NodeOfBTree* getRoot();

private:
    NodeOfBTree* root = nullptr;

    //Is the number of cell's son
    int degree = 2;

    /*!
     * \brief fixNodeOfBTreeWithSmallCountOfElements
     * \param NodeOfBTreeToFix
     */
    void fixNodeOfBTreeWithSmallCountOfElements(NodeOfBTree *nodeOfBTreeToFix);
    /*!
     * \brief getAncestor
     * \param NodeOfBTree
     * \param number
     * \return
     */
    NodeOfBTree *getAncestor(NodeOfBTree *nodeOfBTree, int number);
    /*!
     * \brief dealockNodeOfBTrees
     */
    void dealockNodeOfBTrees();
};

#endif // BTREE_H
