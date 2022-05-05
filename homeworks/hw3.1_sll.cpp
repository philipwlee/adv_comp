#include <iostream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

class SinglyLinkedListNode {
public:
    int data;
    SinglyLinkedListNode *next;

    SinglyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
    }
};

class SinglyLinkedList {
public:
    SinglyLinkedListNode *head;
    SinglyLinkedListNode *tail;

    SinglyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void insert_node(int node_data) {
        SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

        if (!this->head) {
            this->head = node;
        } else {
            this->tail->next = node;
        }

        this->tail = node;
    }
};

//void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
//    while (node) {
//        fout << node->data;
//
//        node = node->next;
//
//        if (node) {
//            fout << sep;
//        }
//    }
//}


/*
 * Complete the 'removeNodes' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST listHead
 *  2. INTEGER x
 */

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */

SinglyLinkedListNode* removeNodes(SinglyLinkedListNode* listHead, int x) {
    if (listHead==nullptr) return nullptr;
    else if ( listHead->data > x ) {
        SinglyLinkedListNode* temp {listHead->next};
        delete listHead;
        return removeNodes(temp, x);
    }
    else {
        listHead->next = removeNodes(listHead->next, x);
        return listHead;
    }
}