//
// Created by 赵德金 on 2021/8/22.
//

#ifndef C_FORCOMPUTER_RBTREE_H
#define C_FORCOMPUTER_RBTREE_H
#include "utils/utils.h"
#define  RB_RED 1
#define  RE_BLOCK 0

template<typename _KeyType,typename  _ValType>
class BRTree;
template<typename _KeyType,typename  _ValType>
class RbNode{
public:
    _KeyType Key;
    _ValType value;
private:
    friend class BRTree<_KeyType,_ValType>;
    RbNode<_KeyType,_ValType> *rb_parent;
    RbNode<_KeyType,_ValType> *rb_left;
    RbNode<_KeyType,_ValType> *rb_right;
    int rb_color;
};
template<typename _KeyType,typename  _ValType>
class BRTree{
    typedef RbNode<_KeyType,_ValType> NodeLink;
public:
    BRTree():m_root(NULL){}
    ~BRTree();

    NodeLink* search(_KeyType key){
        NodeLink *node = m_root;
        while(node){
            if(key <node->key)
                node = node->rb_left;
           else if(key>node->Key){
               node = node->rb_right;
           }
           else
           {
               return node;
           }
        }
        return NULL;
    }
    void insert(_KeyType key,_ValType value)
    {
        NodeLink *node = new NodeLink;
        if(insert_new_node(key,value))
        {
            insert_fix(node);
        }
    }

    void erase_node(NodeLink *node);
    void erase(_KeyType key);

    NodeLink* minimum()
    {
        NodeLink *p = m_root;
        while(p->rb_left!=NULL)
            p = p->rb_left;
        return p;
    }

    NodeLink maximum()
    {
        NodeLink *p = m_root;
        while(p->rb_right != NULL)
        {
            p = p->rb_right;
        }
    }

protected:
    bool insert_new_node(_KeyType key,_ValType value,BRTree::NodeLink* node);
    void insert_fix(NodeLink *node);
    void rotate_left(NodeLink *node);
    void rotate_right(NodeLink *node);
    void erase_fixup(NodeLink* node, NodeLink *parent);
    NodeLink *m_root;
};

template<typename _KeyType, typename _ValType>
BRTree<_KeyType, _ValType>::~BRTree() {
    while(m_root!=NULL)
        erase_node(m_root);
}

template<typename _KeyType, typename _ValType>
bool BRTree<_KeyType, _ValType>::insert_new_node(_KeyType key, _ValType value, BRTree::NodeLink *node) {
    RbNode<_KeyType,_ValType> **pp = &m_root;
    RbNode<_KeyType,_ValType> *parent = NULL;
    RbNode<_KeyType,_ValType> *pnode;
    while (*pp)
    {
        pnode = parent = *pp;
        if (key < pnode->key)
        {
            pp = &pnode->rb_left;
        }
        else if (key > (*pp)->key)
        {
            pp = &pnode->rb_right;
        }
        else{
            pnode->value = value;
            return false;
        }
    }

    node->rb_parent = parent;
    node->Key = key;
    node->value = value;
    node->rb_color = RB_RED;
    node->rb_left = node->rb_right = NULL;
    *pp = node;
    return true;
}

template<typename _KeyType, typename _ValType>
void BRTree<_KeyType, _ValType>::insert_fix(BRTree::NodeLink *node) {
    RbNode<_KeyType, _ValType> *parent, *grandparent, *uncle, *tmp;

    //fix if two consecutive red node
    while ((parent = node->rb_parent) && parent->rb_color == RB_RED)
    {
        grandparent = parent->rb_parent;    //grandparent sure to be not null
        //begin left-branch case
        if (parent == grandparent->rb_left) {
            uncle = grandparent->rb_right;
            //parent and uncle are both red
            if (uncle && uncle->rb_color == RB_RED) {
                uncle->rb_color = RE_BLOCK;       //color flip
                parent->rb_color = RE_BLOCK;
                grandparent->rb_color = RB_RED;
                node = grandparent;
                continue;     //up to the root
            }
            //black uncle
            if (parent->rb_right == node) {
                rotate_left(parent);       //left-leaning
                tmp = parent;     //update pointers after rotation
                parent = node;
                node = tmp;
            }
            parent->rb_color = RE_BLOCK;     //color update before rotation
            grandparent->rb_color = RB_RED;
            rotate_right(grandparent);
        }
        else {  //begin right branch case
            uncle = grandparent->rb_left;
            if (uncle && uncle->rb_color == RB_RED) {
                uncle->rb_color = RE_BLOCK;
                parent->rb_color = RE_BLOCK;
                grandparent->rb_color = RB_RED;
                node = grandparent;
                continue;
            }

            if (parent->rb_left == node) {
                rotate_right(parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            parent->rb_color = RE_BLOCK;
            grandparent->rb_color = RB_RED;
            rotate_left(grandparent);
        }
    }

    m_root->rb_color = RE_BLOCK;    //root should be black
}

template<typename _KeyType, typename _ValType>
void BRTree<_KeyType, _ValType>::rotate_left(BRTree::NodeLink *node) {
    RbNode<_KeyType,_ValType> *right = node->rb_right;
    if((node->rb_right = right->rb_left)!=NULL)
    {
        right->rb_left->rb_parent = node;
    }
    right->rb_left = node;
    if((right->rb_parent = node->rb_parent)!=NULL)
    {
        if(node==node->rb_parent->rb_left)
            node->rb_parent->rb_left = right;
        else
            node->rb_parent->rb_right = right;
    }
    else
    {
        m_root = right;

    }
    node->rb_parent = right;
}

template<typename _KeyType, typename _ValType>
void BRTree<_KeyType, _ValType>::rotate_right(BRTree::NodeLink *node ) {
    RbNode<_KeyType,_ValType> *left = node->rb_left;
    if((node->rb_left = left->rb_right)!=NULL)
    {
        left->rb_right->rb_parent = node;
    }
    left->rb_right = node;
    if((left->rb_parent = node->rb_parent)!=NULL)
    {
        if(node==node->rb_parent->rb_right)
            node->rb_parent->rb_right = left;
        else
            node->rb_parent->rb_left = left;
    }
    else
    {
        m_root = left;

    }
    node->rb_parent = left;
}

template<typename _KeyType, typename _ValType>
void BRTree<_KeyType, _ValType>::erase_fixup(BRTree::NodeLink *node, BRTree::NodeLink *parent) {
    RbNode<_KeyType, _ValType> *other;
    //only to fix black child
    while ((!node || node->rb_color == RE_BLOCK) && node != m_root)
    {
        //handle left-branch case
        if (parent->rb_left == node)
        {
            other = parent->rb_right;
            if (other->rb_color == RB_RED) {   //red brother. just flip color
                other->rb_color = RE_BLOCK;
                parent->rb_color = RB_RED;
                rotate_left(parent);
                other = parent->rb_right;     //go down a level after rotation and go on fixing up
            }
            //black brother case and two black nephew
            if ((!other->rb_left ||
            other->rb_left->rb_color == RE_BLOCK) &&
            (!other->rb_right ||
            other->rb_right->rb_color == RE_BLOCK))
            {
                other->rb_color = RB_RED;
                node = parent;               //go up
                parent = node->rb_parent;

            }
            else  //less than two black nephew
            {
                //there's one black nephew
                if (!other->rb_right ||
                other->rb_right->rb_color == RE_BLOCK)
                {
                    RbNode<_KeyType, _ValType> *o_left;
                    if ((o_left = other->rb_left) != NULL) {
                        o_left->rb_color = RE_BLOCK;
                    }
                    other->rb_color = RB_RED;
                    rotate_right(other);
                    other = parent->rb_right;
                }
                other->rb_color = parent->rb_color;
                parent->rb_color = RE_BLOCK;
                if (other->rb_right)
                    other->rb_right->rb_color = RE_BLOCK;
                rotate_left(parent);
                node = m_root;
                break;    //finish
            }
        }
        else   //right case. symmetry code
        {
            other = parent->rb_left;
            if (other->rb_color == RB_RED)
            {
                other->rb_color = RE_BLOCK;
                parent->rb_color = RB_RED;
                rotate_right(parent);
                other = parent->rb_left;
            }
            if ((!other->rb_left ||
            other->rb_left->rb_color == RE_BLOCK)
            && (!other->rb_right ||
            other->rb_right->rb_color == RE_BLOCK))
            {
                other->rb_color = RB_RED;
                node = parent;
                parent = node->rb_parent;
            }
            else
            {
                if (!other->rb_left ||
                other->rb_left->rb_color ==  RE_BLOCK)
                {
                    RbNode<_KeyType, _ValType> *o_right;
                    if ((o_right = other->rb_right) != NULL) {
                        o_right->rb_color = RE_BLOCK;
                    }
                    other->rb_color = RB_RED;
                    rotate_left(other);
                    other = parent->rb_left;
                }
                other->rb_color = parent->rb_color;
                parent->rb_color = RE_BLOCK;
                if (other->rb_left) {
                    other->rb_left->rb_color = RE_BLOCK;
                }
                rotate_right(parent);
                node = m_root;
                break;
            }
        }
    }//end loop

    if (node != NULL) {
        node->rb_color = RE_BLOCK;
    }
}

template<typename _KeyType, typename _ValType>
void BRTree<_KeyType, _ValType>::erase_node(BRTree::NodeLink *node) {
    RbNode<_KeyType, _ValType> *child, *parent;
    int color;
    if (node == NULL) return;

    if (!node->rb_left)         //right single link or leaf
        child = node->rb_right;
    else if (!node->rb_right)   //left single link
        child = node->rb_left;
    else  //internal node
    {
        NodeLink *old = node, *left;
        node = node->rb_right;
        //find successor
        while ((left = node->rb_left) != NULL) {
            node = left;
        }
        child = node->rb_right;   //succesor's child
        parent = node->rb_parent;
        color = node->rb_color;
        //update link
        if (child)
            child->rb_parent = parent;
        if (parent) {
            if (parent->rb_left == node)
                parent->rb_left = child;
            else
                parent->rb_right = child;
        }
        else {  //delete root
            m_root = child;
        }

        if (node->rb_parent == old) {
            parent = node;
        }
        //succussor replace the node to be deleted
        node->rb_parent = old->rb_parent;
        node->rb_color = old->rb_color;
        node->rb_right = old->rb_right;
        node->rb_left = old->rb_left;

        if (old->rb_parent) {
            if (old->rb_parent->rb_left == old)
                old->rb_parent->rb_left = node;
            else
                old->rb_parent->rb_right = node;
        }
        else {
            m_root = node;
        }

        old->rb_left->rb_parent = node;
        if (old->rb_right) {
            old->rb_right->rb_parent = node;
        }
        delete old;     //release memory
        goto fixup_color;   //jump to fix-up
    }

    //handle single link case or leaf
    parent = node->rb_parent;
    color = node->rb_color;

    if (child)
        child->rb_parent = parent;
    if (parent)
    {
        if (parent->rb_left == node)
            parent->rb_left = child;
        else
            parent->rb_right = child;
    }
    else {
        m_root = child;
    }
    delete node;

    fixup_color:
    if (color == RE_BLOCK) {
        erase_fixup(child, parent);
    }
}

template<typename _KeyType, typename _ValType>
void BRTree<_KeyType, _ValType>::erase(_KeyType key) {
    RbNode<_KeyType, _ValType> *node = search(key);
    erase_node(node);

}


#endif //C_FORCOMPUTER_RBTREE_H
