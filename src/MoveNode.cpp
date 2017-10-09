//
// Created by tekiflo on 07/01/17.
//

#include <list>
#include "../include/MoveNode.h"
#include "../include/MoveTree.h"

using namespace std;

MoveNode::MoveNode(MoveTree *tree, MoveNode *parent, Move *move)
        : m_move(move), m_parent(parent), m_root(tree) {
    m_height = parent->m_height + 2;
    if (move->hasJumped())
        m_height++;
    m_children = new list<MoveNode *>();
    m_root->addLeaf(this, m_height);
    m_parent->addChild(this);
}

MoveNode::MoveNode(MoveTree *tree, Move *move)
        : m_move(move), m_parent(nullptr), m_root(tree) {
    m_height = 2;
    if (move->hasJumped())
        m_height++;
    m_children = new list<MoveNode *>();
    m_root->addChild(this);
    m_root->addLeaf(this, m_height);
}

MoveNode::~MoveNode() {
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        delete *it;
    }
    delete m_children;
    delete m_move;
}

MoveNode* MoveNode::getParent() const {
    return m_parent;
}

MoveTree* MoveNode::getRoot() const {
    return m_root;
}

std::list<MoveNode *> MoveNode::getChildren() const {
    return *m_children;
}

void MoveNode::addChild(MoveNode *child) {
    m_children->push_front(child);
}

Move *MoveNode::getMove() const {
    return m_move;
}
