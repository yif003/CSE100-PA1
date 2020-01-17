/**
 * TODO: add file header
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /** TODO */
    ~BST() {
        destroy(root);
        root = 0;
        return;
    }

    /** TODO */
    bool insert(const Data& item) {
        BSTNode<Data>** curr = &root;
        BSTNode<Data>* parent = 0;
        int h = 0;
        while ((*curr) != 0) {
            parent = *curr;
            if ((*curr)->getData() == item) {
                return false;
            } else if (item < (*curr)->getData()) {
                h++;
                curr = &(*curr)->left;
            } else {
                h++;
                curr = &(*curr)->right;
            }
        }
        iheight = max(iheight, h);

        (*curr) = new BSTNode<Data>(item);
        (*curr)->parent = parent;

        isize++;

        return true;
    }

    /** TODO */
    iterator find(const Data& item) const {
        BSTNode<Data>* curr = root;
        while (curr != 0 && curr->getData() != item) {
            if (item < curr->getData())
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr;
    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }

    /** TODO */
    bool empty() const {
        if (isize == 0) {
            return true;
        } else {
            return false;
        }
    }

    /** TODO */
    iterator begin() const {
        BSTNode<Data>* curr = root;

        if (curr != 0) {
            while (curr->left != 0) {
                curr = curr->left;
            }
        }
        return typename BST<Data>::iterator(curr);
    }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {}

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** TODO Helper function for begin() */
    static BSTNode<Data>* first(BSTNode<Data>* root) { return 0; }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        if (0 == n) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete n;
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
    static void destroy(BSTNode<Data>* TRoot) {
        if (TRoot != 0) {
            destroy(TRoot->left);
            TRoot->left = 0;
            destroy(TRoot->right);
            TRoot->right = 0;
            TRoot->parent = 0;
            delete (TRoot);
        }
        return;
    }
};

#endif  // BST_HPP
