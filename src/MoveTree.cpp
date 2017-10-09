//
// Created by tekiflo on 07/01/17.
//

#include <list>
#include "../include/MoveTree.h"

using namespace std;

MoveTree::MoveTree(int src) : m_src(src) {
    m_lowest = 0;
    m_children = new list<MoveNode *>();
    m_lowestLeafs = new list<MoveNode *>();
}

MoveTree::~MoveTree() {
    delete m_lowestLeafs;
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        delete *it;
    }
    delete m_children;
}

std::list<MoveNode *> MoveTree::getLowestLeafs() const {
    return *m_lowestLeafs;
}

void MoveTree::addLeaf(MoveNode *move, int height) {
    if (height == m_lowest) {
        m_lowestLeafs->push_front(move);
    } else if (height > m_lowest) {
        m_lowest = height;
        m_lowestLeafs->clear();
        m_lowestLeafs->push_front(move);
    }
}

void MoveTree::addChild(MoveNode *node) {
    m_children->push_front(node);
}

int MoveTree::getHeight() const {
    return m_lowest;
}
