#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

typedef struct Node {
    int xiangshu;
    int xishu;
    Node* next;
}Node;

Node* CreateList(vector<pair<int, int>> &poly) {
    Node* head = new Node();
    if (!head)
        exit(666);
    head -> next = nullptr;

    for (auto &term: poly) {
        Node* newNode = new Node();
        newNode -> xiangshu = term.first;
        newNode -> xishu = term.second;
        newNode -> next = nullptr;

        Node* p = head;
        while (p -> next && p -> next -> xishu > newNode -> xishu)
            p = p -> next;
        newNode -> next = p -> next;
        p -> next = newNode;
    }
    return head;
}

void DestoryList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head -> next;
        delete temp;
    }
}

void PrintList(Node* head) {
    Node* p = head -> next;
    bool firstTerm = true;
    while (p && p -> xishu != 0) {
        if (!firstTerm && p -> xiangshu > 0)
            cout << "+";

        if (p -> xiangshu == 1)
            cout << "x^" << p -> xishu;
        else if (p -> xiangshu == -1)
            cout << "-x^" << p -> xishu;
        else
            cout << p -> xiangshu << "x^" << p -> xishu;

        firstTerm = false;
        p = p -> next;
    }
    if (p && p -> xishu == 0) {
        if (!firstTerm && p -> xiangshu)
            cout << "+";
        cout << p -> xiangshu;
    }
    cout << endl;
}

vector<pair<int, int>> InputPoly() {
    vector<pair<int, int>> poly;
    int terms;
    cout << "请输入多项式的项数：";
    cin >> terms;
    while (terms <= 0) {
        cout << "项数必须 > 0，请重新输入：";
        cin >> terms;
    }
    for (int i = 0; i < terms; i++) {
        int xiangshu,xishu;
        cout << "第" << i + 1 << "项（系数 指数）：";
        cin >> xishu, xiangshu;
        poly.push_back({xiangshu,xishu});
    }
    return poly;
}

int main() {
    cout << "多项式 A" << endl;
    auto poly1 = InputPoly();
    cout << "多项式 B" << endl;
    auto poly2 = InputPoly();
    Node* A = CreateList(poly1);
    Node* B = CreateList(poly2);
    cout << "多项式 A：";
    PrintList(A);
    cout << "多项式 B：";
    PrintList(B);
    DestoryList(A);
    DestoryList(B);
    return 0;
}