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
    BST(const BST<Data>& bst)
        : root(bst.root), isize(bst.isize), iheight(bst.iheight) {
        vector<Data> data(bst.begin(), bst.end());
        sort(data.begin(), data.end());
        this->root = buildSubtree(data, 0, data.size(), iheight);
    }

    /** TODO */
    ~BST() {
        deleteAll(root);
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
    bool deleteNode(const Data& item) {
        return deleteNodeHelper(root, item);
    }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const {
        return iheight;
    }

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
    vector<Data> inorder() {
        vector<Data> mydata;
        helper(mydata, root);
        return mydata;
    }
    void setHeight(const Data& iheight){
        iheight = height(root)-1;
    }

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
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end, int depth) {
        if(start > end){
        return NULL;
        }
        int mid = (start + end)/2;
        BSTNode<Data>* root = new BSTNode<Data>(data[mid]);
        root->right = buildSubtree(data, mid+1, end, depth);
        root->left = buildSubtree(data, start, mid-1, depth);
        return root;
    }

    // Add more helper functions below
    int height(BSTNode<Data>* root){
        int h=0;
        int b=0;
        if(!root){
            return -1;
        }
        else{
            height(root->right);
            h++;
            height(root->left);
            b++;
        }
        return max(h, b);
    }
    void helper(vector<Data>& mydata, BSTNode<Data>* root) {
        if (root == nullptr) return;
        if (root->left != nullptr) helper(mydata, root->left);
        mydata.push_back(root->getData());
        if (root->right != nullptr) helper(mydata, root->right);
    }
    
    BSTNode<Data>* deleteNodeHelper(BSTNode<Data>* root, const Data& key) {
        if (!root) return nullptr;
        if (root->getData() == key) {
            if (!root->right) {
                BSTNode<Data>* left = root->left;
                delete root;
                return left;
            }
            else {
                BSTNode<Data>* succ = root->right;
                while (succ->left) succ = succ->left;
                BSTNode<Data>* temp = new BSTNode<Data>(root->getData());
                root->setData(succ->getData());
                succ->setData(temp->getData());
                root->right = deleteNodeHelper(root->right, key);
                
            }
            isize--;
        }
        else {
            root->left = deleteNodeHelper(root->left, key);
            root->right = deleteNodeHelper(root->right, key);
        }
        return root;
    }

};

#endif  // BST_HPP
