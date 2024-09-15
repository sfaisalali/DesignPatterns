#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
using namespace std;

// Non linear data structure.
// Have multiple levels.

template <typename T>
class BST {

protected:
    struct Node {

        Node* _left;
        Node* _right;
        T _data;

        Node(T data) : _left(nullptr), _right(nullptr), _data(data) {}
        ~Node() {
            delete _left;
            delete _right;
        }
        void setLeft(Node* left) { _left = left; }
        void setRight(Node* right) { _right = right; }
        void SetVal(T data) { _data = data; }
        Node* Left() { return _left; }
        Node* Right() { return _right; }
        T Data() { return _data; }
    };
    Node* _root;
public:
    enum class PrintMode {
        ePreOrder,
        eInOrder,
        ePostOrder
    };
    BST() : _root(nullptr) { }

    ~BST() { delete _root; _root = nullptr; }

    void CreateFromPreOrderInOrder(IArray<T>* pre, IArray<T>* in) {}

    void CreateFromPostOrderInOrder(IArray<T>* post, IArray<T>* in) {}

    void CreateFromPreOrder(IArray<T>* pre) {}

    void CreateFromPostOrder(IArray<T>* post) {}

    void CreateFromInOrder(IArray<T>* in) {}

    void Add(T obj) {
        if (_root == nullptr) {
            _root = new Node(obj);
        }
        else {
            AddChild(obj, _root);
        }
    }

    bool Remove(T obj) {
        if (_root == nullptr) {
            return false;
        }
        return RemoveChild(obj, _root, nullptr, NodeType::Left);
    }

    string toString(PrintMode mode = PrintMode::eInOrder) {
        switch (mode) {
        case PrintMode::eInOrder:
        {
            cout << "\nIn  -> L-C-R: ";
            return PrintInOrder(_root);
        }
        case PrintMode::ePreOrder:
        {
            cout << "\nPre -> L-R-C: ";
            return PrintPreOrder(_root);
        }
        case PrintMode::ePostOrder:
        {
            cout << "\nPre -> C-L-R: ";
            return PrintPostOrder(_root);
        }
        }
        return "";
    }
    void CreateDummy() {

        auto p31 = new Node(T());
        auto p32 = new Node(T());
        auto p33 = new Node(T());
        auto p34 = new Node(T());

        auto p21 = new Node(T());
        p21->setLeft(p31);
        p21->setRight(p32);

        auto p22 = new Node(T());
        p22->setLeft(p33);
        p22->setRight(p34);

        _root = new Node(T());
        _root->setLeft(p21);
        _root->setRight(p22);
    }

private:

    void AddChild(T obj, Node* root) {
        if (root == nullptr) return;

        if (root->Data() > obj) {
            if (root->Left() == nullptr) {
                root->setLeft(new Node(obj));
            }
            else {
                AddChild(obj, root->Left());
            }
        }
        else {
            if (root->Right() == nullptr) {
                root->setRight(new Node(obj));
            }
            else {
                AddChild(obj, root->Right());
            }
        }
    }

    enum class NodeType {
        Left, Right
    };

    bool RemoveChild(T obj, Node* root, Node* parent, NodeType type) {
        if (root == nullptr)return false;
        // Node to delete is the current one..
        // deletion logic here.
        if (root->Data() == obj) {
            auto left = root->Left();
            auto right = root->Right();

            // four scenarios.
            // 1 -> Leaf.
            if (left == nullptr && right == nullptr) {
                // If it is a leaf, simply delete the node and assign null to parent's side.
                delete root;
                if (parent != nullptr)
                    type == NodeType::Left ? parent->setLeft(nullptr) : parent->setRight(nullptr);
                else
                    _root = nullptr;
            }
            // 2 -> Have one left child and no right child.
            if (left != nullptr && right == nullptr) {
                // Here, as it have a left child, the current node will be replaced with the immediate left child. 
                // For that, inform the parent of current node (based on type) that the child is replaced with new one.

                if (type == NodeType::Left) {
                    if (parent == nullptr) {
                        _root = left;
                    }
                    else {
                        parent->setLeft(left);
                    }
                    root->setLeft(nullptr);
                }
                else {
                    if (parent == nullptr) {
                        _root = left;
                    }
                    else {
                        parent->setRight(left);
                    }
                    root->setLeft(nullptr);
                }
                delete root;
            }
            // 3 -> Have one right child and no left child.
            if (left == nullptr && right != nullptr) {
                //auto val = GetMinValue(right, root, NodeType::Right, true);
                //root->SetVal(val);

                if (type == NodeType::Left) {
                    if (parent == nullptr) {
                        _root = right;
                    }
                    else {
                        parent->setLeft(right);
                    }
                    root->setRight(nullptr);
                }
                else {
                    if (parent == nullptr) {
                        _root = right;
                    }
                    else {
                        parent->setRight(right);
                    }
                    root->setRight(nullptr);
                }
                delete root;
            }
            // 4 -> Have both left & right child.
            if (left != nullptr && right != nullptr) {

                //if (parent == nullptr) {
                //    // when it is the root.!
                //    // Handle it seperately.
                //    _root = right;
                //} else {
                //    type == NodeType::Left ? parent->setLeft(right) : parent->setRight(right);
                //}
                //AppendToExtremeLeft(right, left);
                if (parent == nullptr) {
                    // when it is the root.!
                    // Handle it seperately.
                    _root = left;
                }
                else {
                    type == NodeType::Left ? parent->setLeft(left) : parent->setRight(left);
                }
                AppendToExtremeRight(left, right);
                root->setLeft(nullptr);
                root->setRight(nullptr);
                delete root;
            }
        }
        else if (root->Data() > obj) {
            return RemoveChild(obj, root->Left(), root, NodeType::Left);
        }
        else {
            return RemoveChild(obj, root->Right(), root, NodeType::Right);
        }
        return true;
    }

    string PrintInOrder(Node* node) {
        string str = "";
        if (node != nullptr) {
            str += PrintInOrder(node->Left());
            str += node->Data();
            str += '-';
            str += PrintInOrder(node->Right());
        }
        return str;
    }

    string PrintPreOrder(Node* node) {
        string str = "";
        if (node != nullptr) {
            str += node->Data();
            str += PrintPreOrder(node->Left());
            str += PrintPreOrder(node->Right());
        }
        return str;
    }

    string PrintPostOrder(Node* node) {
        string str = "";
        if (node != nullptr) {
            str += PrintPostOrder(node->Left());
            str += PrintPostOrder(node->Right());
            str += node->Data();
        }
        return str;
    }
    T GetMaxValue(Node* node) {
        while (node != nullptr) {
            if (node->Right() == nullptr) {
                return node->Data();
            }
            node = node->Right();
        }
        throw "There is a loop in this tree!";
    }

    T GetMinValue(Node* node) {
        while (node != nullptr) {
            if (node->Left() == nullptr) {
                return node->Data();
            }
            node = node->Left();
        }
        throw "There is a loop in this tree!";
    }

    void AppendToExtremeLeft(Node* node, Node* left) {
        while (node != nullptr && node->Left() != nullptr) {
            node = node->Left();
        }
        node->setLeft(left);
    }

    void AppendToExtremeRight(Node* node, Node* right) {
        while (node != nullptr && node->Right() != nullptr) {
            node = node->Right();
        }
        node->setRight(right);
    }
};

/// Full binary tree
// -  Each node will have either 0 child or 2 children. In other words, each node will have 


// construct binary tree from post and in order
// 9    1   2   12  7   5   3   11  4   8       -> Post [Left-Right-Root]
// 9    5   1   7   2   12  8   4   3   11      -> IN   [Left-Root-Right]

//                          8
//[9,5,1,7,2,12]      5                  [4,3,11]
//                      [1,7,2,12]
//             9           7            4
//                     1       12           11
//                           2            3
//
//
//
//
//

#endif