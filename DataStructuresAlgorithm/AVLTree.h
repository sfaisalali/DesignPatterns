#ifndef E_H
#define E_H


template <typename T>
class AVL {

private:
    struct Node {

        Node* right = nullptr;
        Node* left = nullptr;
        T data;
        int height = 1;
        Node(T data):data(data), left(nullptr), right(nullptr){}
        ~Node() { delete right; delete left; }

    private:
        Node() = delete;
    };
    Node* _root;


public:
    AVL(): _root(nullptr){}
    ~AVL() { delete _root; _root = nullptr; }

    void Add(T data) {
        _root = insert(_root, data);
    }

    void Remove(T data) {
        _root = RemoveNode(_root, data);
    }

    enum class PrintMode {
        ePreOrder,
        eInOrder,
        ePostOrder,
        eInvalid
    };

    string toString(PrintMode mode = PrintMode::eInvalid) {
        cout << "\n-------------------------------------------------------------";
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
        case PrintMode::eInvalid:
            Print();
            break;
        }
        return "";
    }

    void Print() {
        PrintInPreOrder(_root, 'C');
    }
private:

    void PrintInPreOrder(Node* node, char c) {
        if (node == nullptr)return;
        cout << "\n";
        for (int i = 0; i < _root->height - node->height; i++)
            cout << "\t";
        cout << c << node->data;
        PrintInPreOrder(node->left, 'L');
        PrintInPreOrder(node->right, 'R');
    }

    string PrintInOrder(Node* node) {
        string str = "";
        if (node != nullptr) {
            str += PrintInOrder(node->left);
            str += node->data;
            str += PrintInOrder(node->right);
        }
        return str;
    }

    string PrintPreOrder(Node* node) {
        string str = "";
        if (node != nullptr) {
            str += node->data;
            str += PrintInOrder(node->left);
            str += PrintInOrder(node->right);
        }
        return str;
    }

    string PrintPostOrder(Node* node) {
        string str = "";
        if (node != nullptr) {
            str += PrintInOrder(node->left);
            str += PrintInOrder(node->right);
            str += node->data;
        }
        return str;
    }

    int height(Node* node) {
        if (node == nullptr)return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr)return 0;
        return height(node->left) - height(node->right);
    }



    Node* rotateLeft(Node* node) {

        auto newCenter = node->right;
        auto existingleftOfRight = newCenter->left;
        
        // perform rotation.
        newCenter->left = node;
        node->right = existingleftOfRight;

        // the height of the left node shal be updated first. coz, now the height has be
        // changed and this wil be considered for the new center's height calculation.
        node->height = 1 + max(height(node->left), height(node->right));
        newCenter->height = 1 + max(height(newCenter->left), height(newCenter->right));

        return newCenter;
    }

    Node* rotateRight(Node* node) {

        auto newCenter = node->left;
        auto existingrightofleft = newCenter->right;

        newCenter->right = node;
        node->left = existingrightofleft;


        // the height of the left node shal be updated first. coz, now the height has be
        // changed and this wil be considered for the new center's height calculation.
        node->height = 1 + max(height(node->left), height(node->right));
        newCenter->height = 1 + max(height(newCenter->left), height(newCenter->right));

        return newCenter;
    }

    Node* insert(Node* node, T data) {
        // If node is the actual root. then return a new node.
        if (node == nullptr)
            return new Node(data);

        // If value is less than the current one, add to the left and
        // balance the same, then return the root for the left branch.
        // then that will be the left of the current branch.
        if (data < node->data)
            node->left = insert(node->left, data);

        // Else if the current one is greater than the current node, then
        // add to the right node and replace the same with the root of the right side.
        else if (data > node->data)
            node->right = insert(node->right, data);

        // Else case means, the value of the current node and the node to insert are same.
        // But the same is not allowed in AVL. [duplicate values are not allowed].
        else
            return node;

        // Okay, we reach here, means, we have a unique value, no mater which is going to be inserted
        // in the current branch.

        // So the height of this node is going to increase. So increment current value with one.
        // Current value will be the max of the height of left node and right node.
        node->height = 1 + max(height(node->left), height(node->right));


        // Okay. we got the new height. Now, we have to check whether the tree is balanced or not.
        // for that , calculate the balance factor.
        // If the balace factor is in between -1 and 1, then our tree is balanced.
        int balance = getBalance(node);

        // four scenarios we need to take care.
        // A Left->Left insertion, a Right->Right insertion, a Left right insertion and right right insertion.

        // Case 1: Left followed by Left insertion.
        // Here, if the balance is greater than 1 & value to insert is less than the left node's value,
        // Then we need to right rotate the current node. if not, no issues.
        if (balance > 1 && data < node->left->data) {
            return rotateRight(node);
        }

        // Case 2: Right followed by a right insertion.
        // If the balance is less than -1 and the data in the current node is greater than the value in the 
        // right node, then we need to insert to the right side. It will result in RR insertion.
        // Then we have to rotate the node to the left. If not, no issues.
        if (balance < -1 && data > node->right->data) {
            return rotateLeft(node);
        }

        // case 3: Left followed by right insertion.
        // Here, the balance will be greater than 1. and the value to be inserted will be greater than
        // the value in the left of current node, then it is a LR insertion. If so, we have to rotate the 
        // left node to the left to bring the root value as the leaf and  righ of node as the root.
        // Simply means, Rotate Left. then rotate right.
        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // case 4: Here, the opposite thing of case 3 happens. 
        // Right followed by left insertion.
        // Here, we have to rotate the right node to the right and then rotate the node to the left. 
        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        // Reach here ??? =>> No issues. return this node.

        return node;
    }

    Node* MinValueNode(Node* node) {
        auto current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* RemoveNode(Node* root, T data) {
        if (root == nullptr)
            return nullptr;
        // On left side
        if (data < root->data)
            root->left = RemoveNode(root->left, data);
        // On right side
        else if (data > root->data)
            root->right = RemoveNode(root->right, data);
        else {
            // This is the one we need.
            // three cases to handle.
            // 1) leaf
            // 2) node with one child.
            // 3) node with two children.

            if (root->left == nullptr || root->right == nullptr) {
                // this will take first two cases mentioned above.
                // will be here, if it is a leaf or a node with one child.
                auto temp = root->left != nullptr ? root->left : root->right;
                if (temp == nullptr) {
                    // Means, this is a leaf case.
                    delete root;
                    root = nullptr;
                }
                else {
                    // Means, either left or right node is here in temp.
                    root->left = nullptr;
                    root->right = nullptr;
                    delete root;
                    root = temp;
                }
            }
            else {
                // here means, there are two child for the current node.
                // so need to replace the value with the minimum value in the right branch.
                auto minOnRight = MinValueNode(root->right);
                root->data = minOnRight->data;
                root->right = RemoveNode(root->right, minOnRight->data);
            }
        }

        if (root == nullptr)
            return nullptr;

        // Now we need to adjust the height of the tree.
        root->height = 1 + max(height(root->left), height(root->right));

        auto balance = getBalance(root);

        // Left-Left case
        if (balance > 1 && getBalance(root->left) > 0) {
            return rotateRight(root);
        }

        // Right right case
        if (balance < -1 && getBalance(root->right) < 0) {
            return rotateLeft(root);
        }

        // Left right case
        if (balance > 1 && getBalance(root->right) < 0) {
            root->right = rotateLeft(root->right);
            return rotateRight(root);
        }

        // Right Left case
        if (balance < -1 && getBalance(root->left) > 0) {
            root->left = rotateRight(root->left);
            return rotateLeft(root);
        }
        return root;
    }

    inline int max(int a, int b) { return a > b ? a : b; }
    
};


#endif
