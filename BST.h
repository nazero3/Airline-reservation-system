#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void deleteSubtree(BSTNode<T>* node);
    BSTNode<T>* findMin(BSTNode<T>* t);
    BSTNode<T>* findParent(BSTNode<T>* t) const;
    BSTNode<T>* copyTree(BSTNode<T>* t);
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    this->root = new BSTNode<T>;
    
    
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    *this = obj;
}

template<class T>
BST<T>::~BST() {
    deleteSubtree(this->root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    if (this->isEmpty())
        return NULL;
    else {
        return this->root;
    }
}

template<class T>
bool BST<T>::isEmpty() const {
    if (this->root == NULL)
        return true;
    else
        return false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    if (this->root == node)
        return true;
    else if (this->root->data > node->data)
        return BST::contains(this->root->left);
    else if (this->root->data < node->data)
        return BST::contains(this->root->right);
    else
        return false;
}

template<class T>
void BST<T>::insert(const T &data) {
    if (this->root->data == T{})
    {
        this->root->data = data;
        return;
    }
    BSTNode<T>* current = this->root;
    BSTNode<T>* parentNode = new BSTNode<T>();
    while (current != NULL)
    {
        parentNode = current;
    
        if (current->data < data)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    if (data > parentNode->data)
    {
        parentNode->right = new BSTNode<T>(data, NULL, NULL);
    }
    else
    {
        parentNode->left = new BSTNode<T>(data, NULL, NULL);
    }

    
        
}

template<class T>
void BST<T>::remove(const T &data) {
    BSTNode<T>* current = this->root;
    BSTNode<T>* oldNode = new BSTNode<T>();
    while (current->data != data)
    {
        
        if (current->data > data)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    if (current->left != NULL && current->right != NULL)
    {
        current->data = findMin(current->right)->data;
        current = current->right;
        while (current->data != data)
        {

            if (current->data > data)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        oldNode = current;
        current = (current->left != NULL) ? current->left : current->right;
        delete oldNode;
    }
    else
    {
        oldNode = current;
        current = (current->left != NULL) ? current->left : current->right;
        delete oldNode;
    }
    



}

template<class T>
void BST<T>::removeAllNodes() {
    if (this == NULL)
    {
        return;
    }
    deleteSubtree(this->root);
    
    
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    BSTNode<T>* current = this->root;
    if (data == current->data)   return current;
     
    while (current != NULL && current->data != data)
    {
        if (current->data < data)
        {
            current = current->right;
        }
        else if(current->data > data)
        {
            current = current->left;
        }
        
    }
    return current;

    }
    
    

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    
    if (tp == inorder) {
        BSTNode<T>* current = node->right;
        if (current != NULL) {
            while (current->left)
            {
                current = current->left;
            }
            return current;
        }
        else {
            BSTNode<T>* successor = NULL;
            BSTNode<T>* anode = this->root;
            while (anode != node)
            {
                if (anode->data > node->data) {
                    successor = anode;
                    anode = successor->left;
                }
                else
                {
                    anode = anode->right;
                }
            }
            return successor;
        }
    } else if (tp == preorder) {
        if (node->left)
            return node->left;

        if (node->right)
            return node->right;
        
        BSTNode<T>* tmp = findParent(node);
        BSTNode<T>* current = node;
        while (tmp != NULL && tmp->right == current) {
            current = findParent(current);
            tmp = findParent(tmp);
        }
        if (tmp)
            return tmp->right;
        else
            return NULL;
        
    } else if (tp == postorder) {
        BSTNode<T>* pnode = findParent(node);
        if (pnode->right == NULL || pnode->right == node)
            return (pnode->data == T{}) ? NULL : pnode;
        BSTNode<T>* current = pnode->right;
        while (current->left != NULL)
            current = current->left;
        if (current->data == T{})
            return NULL;
        else if (current->right)
            return current->right;
        else return current;
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    
    this->removeAllNodes();
    this->root = copyTree(rhs.root);
    return *this;
    

}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        std::cout << "\t" << node->data;
        
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    } else if (tp == postorder) {
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        std::cout << "\t" << node->data;
    }
}

template<class T>
void BST<T>::deleteSubtree(BSTNode<T>* node) {
    if (node != NULL) {
        if (node->left != NULL) {
            deleteSubtree(node->left);
        }
        if (node->right != NULL) {
            deleteSubtree(node->right);
        }
        delete node;
    }
}
template<class T>
BSTNode<T>* BST<T>::findMin(BSTNode<T> *t) {
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);

}
template<class T>
BSTNode<T>* BST<T>::findParent(BSTNode<T>* t) const {
    BSTNode<T>* current = this->root;
    BSTNode<T>* parentNode = new BSTNode<T>();
    while (current != t)
    {
        parentNode = current;
        if (current->data < t->data)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return parentNode;
}
template<class T>
BSTNode<T>* BST<T>::copyTree(BSTNode<T>* t) {
    if (t == NULL)
        return NULL;
    BSTNode<T>* croot = new BSTNode<T>();
    croot->data = t->data;
    croot->left = copyTree(t->left);
    croot->right = copyTree(t->right);
    return croot;
}