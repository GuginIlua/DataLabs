#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int status;
    Node* next;
    Node(int stat) : status(stat), next(nullptr) {}
};

struct List {
    Node* head;

    List() : head(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }
    void push_back(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            head->next = head;
        }
        else {
            Node* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            tail->next = newNode;
            newNode->next = head;
        }
    }

    int getDataAtPosition(int position) {
        Node* current = head;
        int count = 0;
        do {
            if (count == position) {
                return current->status;
            }
            current = current->next;
            count++;
        } while (current != head);
    }
    void printList() {
        Node* current = head;
        do {
            cout << current->status << " ";
            current = current->next;
        } while (current != head);

        std::cout << std::endl;
    }
    int sizeOf() {
        Node* current = head;
        int count = 0;
        do {
            current = current->next;
            count++;
        } while (current != head);
        return count;
    }
};

int main() {
    List A, newA;
    List column, columnNew;
    List numbOfElem, numbOfELemNEw;
    int count = 0;
    int matrSize;
    int a, b = 0, c = 0, f, d;
    int count2 = 0;
    int count3 = 0;
    ifstream fin("text.txt");
    while (fin>>a) {
        count++;
    }
    fin.close();
    matrSize = sqrt(count);
    if ((matrSize * matrSize) != count) {
        cout << "Input error" << endl;
        return 0;
    }
    cout << "Before turn:" << endl;
    ifstream in("text.txt");
    numbOfElem.push_back(0);
    for (int i = 0;i < count; i++) {
        count2++;
        in >> a;
        cout << a << " ";
        if (a != 0) {
            A.push_back(a);
            column.push_back(count2);
            count3++;
        }
        if (count2 == matrSize) {
            cout << endl;
            count2 = 0;
            numbOfElem.push_back(count3);
        }
    }
    in.close();
    for (int i = (column.sizeOf() - 1);i > -1;i--) {
        columnNew.push_back(matrSize - column.getDataAtPosition(i));
    };
    for (int i = (numbOfElem.sizeOf()-1);i > -1;i--) {
        numbOfELemNEw.push_back(numbOfElem.getDataAtPosition(numbOfElem.sizeOf()-1)- numbOfElem.getDataAtPosition(i));
    }
    for (int i = (A.sizeOf()-1);i > -1;i--) {
        newA.push_back(A.getDataAtPosition(i));
    }
    cout << "After turn:" << endl;
    for (int i = 0;i < matrSize;i++) {
        a = numbOfELemNEw.getDataAtPosition(i + 1) - numbOfELemNEw.getDataAtPosition(i);
        cout << "0 ";
        for (int j = 0;j < (matrSize-1);j++) {
            d = columnNew.getDataAtPosition(c);
            f = (columnNew.getDataAtPosition(c) - 1);
            if (j == f && a>0) {
                cout << newA.getDataAtPosition(b) << " ";
                c++;
                b++;
                a--;
            }
            else cout << "0 ";
        }
        cout << endl;
    }
    return 0;
}