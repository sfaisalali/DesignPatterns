#include "SingleLinkedList.h"
#include "DoubleLinkedList.h"
#include "DynamicArray.h"
#include "Stack.h"
#include "Queue.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "IIterator.h"

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "MinHeap.h"
#include "MaxHeap.h"


#include <iostream>
using namespace std;

class TestClass {
    int nIdx;

public:
    TestClass() {
        static int p = 0;
        nIdx = p++;
    }
    TestClass(int val) { nIdx = val; }

    operator string() {
        return std::to_string(nIdx);
    }
    //std::string toString()
    //{
    //    return std::to_string(nIdx);
    //}

    friend ostream & operator << (ostream &out, const TestClass &c)
    {
        out << c.nIdx;
        return out;
    }

    bool operator == (const TestClass& obj)
    {
        return obj.nIdx == nIdx;
    }

    bool operator > (const TestClass& obj) {
        return this->nIdx > obj.nIdx;
    }

    bool operator < (const TestClass& obj) {
        return this->nIdx < obj.nIdx;
    }

    bool operator >= (const TestClass& obj) {
        return this->nIdx >= obj.nIdx;
    }

    bool operator <= (const TestClass& obj) {
        return this->nIdx <= obj.nIdx;
    }

    TestClass operator + (const TestClass& obj) {
        this->nIdx += obj.nIdx;
        return *this;
    }

    TestClass operator - (const TestClass& obj) {
        this->nIdx -= obj.nIdx;
        return *this;
    }


};



void testLists() {

    DynamicArray<TestClass> arr;
    ///-----------------------------------------------///
    
    TestClass a, b, c, d, e, f, g;
    arr.Add(a);
    arr.Add(b);
    arr.Add(c);
    arr.Add(d);
    arr.Add(e);
    if (arr.toString() == string("01234")) {  }
    else { cout << "TC 01: Add() \t\t- FAILED"; }

    
    arr.Reverse();
    if (arr.toString() == string("43210")) {  }
    else { cout << "\nTC 01: Reverse() \t- FAILED"; }

    arr.Reverse();

    ///-----------------------------------------------///
    
    if (!arr.Contains(f)) {  }
    else { cout << "\nTC 02: Contains() \t- FAILED"; }
    arr.Add(f);
    if (arr.Contains(f)) {  }
    else { cout << "FAILED"; }

    ///-----------------------------------------------///
    
    if (arr.getAt(2) == c) {  }
    else { cout << "\nTC 04: getAt() \t\t- FAILED"; }

    ///-----------------------------------------------///
    
    if (arr.indexOf(c) == 2) {  }
    else { cout << "\nTC 05: indexOf() \t- FAILED"; }

    ///-----------------------------------------------///
    
    if (!arr.isEmpty()) {  }
    else { cout << "\nTC 06: isEmpty() \t- FAILED"; }

    ///-----------------------------------------------///
    arr.remove(c);
    if (arr.toString() == "01345") {  }
    else { cout << "\nTC 07: remove() \t- FAILED"; }

    ///-----------------------------------------------///
    arr.removeAt(2);
    arr.removeAt(0);
    arr.removeAt(0);
    arr.removeAt(0);
    arr.removeAt(0);
    if (arr.toString() == "") {  }
    else { cout << "\nTC 08: removeAt() \t- FAILED"; }

    ///-----------------------------------------------///
    auto Itr = arr.iterator();
    std::string str = "";
    while (Itr->HasNext())
        str += Itr->Next();
    if (str == "") {  }
    else { cout << "\nTC 09: iterator() \t- FAILED"; }

    ///-----------------------------------------------///
    arr.clear();
    arr.Add(b);
    arr.Add(e);
    arr.Add(f);
    arr.InsertAt(1, g);

    if (arr.toString() == "1645") {  }
    else { cout << "\nTC 10: InsertAt() \t- FAILED"; }

    ///-----------------------------------------------///
    arr.clear();
    if (arr.toString() == "") {  }
    else { cout << "\nTC 11: clear() \t\t- FAILED"; }

    // Rotation test cases.
    {
        DoubleLinkedList<TestClass> ar;
        for (int i = 0; i < 5; i++) {
            ar.Add(TestClass(i));
        }
        ar.RotateLeft(2);
        if (ar.toString() == "23401") {}
        else { cout << "\nTC 11: RotateLeft() \t\t- FAILED"; }

        if(-1 != ar.FindIndex(TestClass(6))){ cout << "\nTC 11: FindIndex() after rotate\t- FAILED"; }
        if(1 != ar.FindIndex(TestClass(3))){ cout << "\nTC 11: FindIndex() after rotate\t- FAILED"; }
        if(2 != ar.NoOfPirsWithSum(5)){ cout << "\nTC 11: NoOfPirsWithSum() after rotate\t- FAILED"; }
        if(0 != ar.NoOfPirsWithSum(10)){ cout << "\nTC 11: NoOfPirsWithSum() after rotate\t- FAILED"; }
    }

}

void testStack() {
    TestClass a, b, c, d, e, f;
    SingleLinkedList<TestClass> list;
    Stack<TestClass> bb(&list);
    bb.Push(a);
    cout << "\n" << bb.toString();
    bb.Push(b);
    cout << "\n" << bb.toString();
    bb.Pop();
    cout << "\n" << bb.toString();
    bb.Push(c);
    cout << "\n" << bb.toString();
    bb.Pop();
    cout << "\n" << bb.toString();
    bb.Pop();
    cout << "\n" << bb.toString();
    bb.Push(d);
    cout << "\n" << bb.toString();
}


void testQueue() {
    TestClass a, b, c, d, e, f;
    DynamicArray<TestClass> list;
    Queue<TestClass> bb(&list);
    bb.Enqueue(a);
    cout << "\n" << bb.toString();
    bb.Enqueue(b);
    cout << "\n" << bb.toString();
    bb.Dequeue();
    cout << "\n" << bb.toString();
    bb.Enqueue(c);
    cout << "\n" << bb.toString();
    bb.Dequeue();
    cout << "\n" << bb.toString();
    bb.Dequeue();
    cout << "\n" << bb.toString();
    bb.Enqueue(d);
    cout << "\n" << bb.toString();
}

void BubbleSortTest() {

    TestClass a, b, c, d, e, f;
    SingleLinkedList<TestClass> list;
    list.Add(a);
    list.Add(b);
    list.Add(c);
    list.Add(d);
    list.Add(e);
    BubbleSort<TestClass> sort(&list);
    sort.AscentingSort();
    cout << sort.toString();

    sort.DescentingSort();

    cout << "\n\n" << sort.toString();

}

void InsertionSortTest() {

    TestClass a, b, c, d, e, f;
    SingleLinkedList<TestClass> list;
    list.Add(a);
    list.Add(b);
    list.Add(c);
    list.Add(d);
    list.Add(e);
    InsertionSort<TestClass> sort(&list);
    sort.AscentingSort();
    cout << sort.toString();

    sort.DescentingSort();

    cout << "\n\n" << sort.toString();

}

void SelectionSortTest() {

    TestClass a, b, c, d, e, f;
    DoubleLinkedList<TestClass> list;
    list.Add(b);
    list.Add(c);
    list.Add(a);
    list.Add(d);
    list.Add(e);
    SelectionSort<TestClass> sort(&list);
    sort.AscentingSort();
    cout << sort.toString();

    sort.DescentingSort();

    cout << "\n\n" << sort.toString();

}

void QuickSortTest() {
    TestClass a, b, c, d, e, f;
    DoubleLinkedList<TestClass> list;
    list.Add(b);
    list.Add(c);
    list.Add(d);
    list.Add(e);
    list.Add(a);
    QuickSort<TestClass> sort(&list);
    try {
        sort.AscentingSort();
    }
    catch (std::exception e) {
        throw e;
    }
    cout << sort.toString();

    try {
        sort.DescentingSort();
    }
    catch (std::exception e) {
        throw e;
    }

    cout << "\n\n" << sort.toString();
}

void MergeSortTest() {
    TestClass a, b, c, d, e, f;
    DoubleLinkedList<TestClass> list;
    list.Add(b);
    list.Add(c);
    list.Add(d);
    list.Add(e);
    list.Add(a);
    MergeSort<TestClass> sort(&list);
    try {
        sort.AscentingSort();
    }
    catch (std::exception e) {
        throw e;
    }
    cout << sort.toString();

    try {
        sort.DescentingSort();
    }
    catch (std::exception e) {
        throw e;
    }

    cout << "\n\n" << sort.toString();
}

void TestBST() {
    BST<TestClass> tree;
    TestClass a, b, c, d, e, f, g, h, i, j, k;
    tree.Add(c);
    cout << tree.toString();
    tree.Add(a);
    cout << tree.toString();
    tree.Add(b);
    cout << tree.toString();
    tree.Add(i);
    cout << tree.toString();
    tree.Add(j);
    cout << tree.toString();
    tree.Add(e);
    cout << tree.toString();
    tree.Add(k);
    cout << tree.toString();
    tree.Add(f);
    cout << tree.toString();
    tree.Add(g);
    cout << tree.toString();
    tree.Add(h);
    cout << tree.toString();
    tree.Add(d);
    cout << tree.toString();

    tree.Remove(h);
    cout << tree.toString();
    tree.Remove(c);
    cout << tree.toString();
    tree.Remove(j);
    cout << tree.toString();
    tree.Remove(a);
    cout << tree.toString();
    tree.Remove(f);
    cout << tree.toString();
    tree.Remove(g);
    cout << tree.toString();
    tree.Remove(d);
    cout << tree.toString();
    tree.Remove(i);
    cout << tree.toString();
    tree.Remove(b);
    cout << tree.toString();
    tree.Remove(e);
    cout << tree.toString();
    tree.Remove(k);
    cout << tree.toString();
}

void TestAVL() {
    AVL<TestClass> tree;
    TestClass a, b, c, d, e, f, g, h, i, j, k;
    tree.Add(c);
    cout << tree.toString();
    tree.Add(a);
    cout << tree.toString();
    tree.Add(b);
    cout << tree.toString();
    tree.Add(i);
    cout << tree.toString();
    tree.Add(j);
    cout << tree.toString();
    tree.Add(e);
    cout << tree.toString();
    tree.Add(k);
    cout << tree.toString();
    tree.Add(f);
    cout << tree.toString();
    tree.Add(g);
    cout << tree.toString();
    tree.Add(h);
    cout << tree.toString();
    tree.Add(d);
    cout << tree.toString();


    tree.Remove(h);
    cout << tree.toString();
    tree.Remove(c);
    cout << tree.toString();
    tree.Remove(j);
    cout << tree.toString();
    tree.Remove(a);
    cout << tree.toString();
    tree.Remove(f);
    cout << tree.toString();
    tree.Remove(g);
    cout << tree.toString();
    tree.Remove(d);
    cout << tree.toString();
    tree.Remove(i);
    cout << tree.toString();
    tree.Remove(b);
    cout << tree.toString();
    tree.Remove(e);
    cout << tree.toString();
    tree.Remove(k);
    cout << tree.toString();
}

void testMinHeap() {

    MinHeap<TestClass> heap(100);
    heap.insert(TestClass(3));
    heap.insert(TestClass(2));
    heap.insert(TestClass(1));
    heap.insert(TestClass(15));
    heap.insert(TestClass(5));
    heap.insert(TestClass(4));
    heap.insert(TestClass(45));

    cout << heap.extractMin() << " ";
    cout << heap.getMin() << " ";


    MaxHeap<TestClass> heap2(100);
    heap2.insert(TestClass(3));
    heap2.insert(TestClass(2));
    heap2.insert(TestClass(1));
    heap2.insert(TestClass(15));
    heap2.insert(TestClass(5));
    heap2.insert(TestClass(4));
    heap2.insert(TestClass(45));

    cout << heap2.extractMax()<< " ";
    cout << heap2.getMax() << " ";
}

int main()
{
    try {
        // test basic lists. sinle and double.
         testLists();

        // test a stack using single or double linked list.
        // testStack();

        // Test a queue using single linked list / double linked list.
        // testQueue();

        // Bubble sort technique testing.
        // BubbleSortTest();

        // Insertion sort technique testing.
        // InsertionSortTest();

        // Selection sort technique testing.
        // SelectionSortTest();

        // Tests quick sort
        // QuickSortTest();

        // Merge sort test
        // MergeSortTest();

        // Testing binary search tree
        // TestBST();

        // Testing avl tree
        // TestAVL();

        // Heap test. Min heap
        // testMinHeap();

         cout << "\nCOMPLETED";
    }
    catch (std::exception e) {
        cout << e.what();
    }
    getchar();
    return 0;
}