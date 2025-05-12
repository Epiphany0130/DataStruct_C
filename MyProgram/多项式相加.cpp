//
// Created by 谷煜奇 on 25-5-11.
//

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

typedef struct Node {
    int coef;
    int expn;
    struct Node *next;
} Node;

Node *CreateList(vector<pair<int, int> > &poly) {
    Node *head = new Node();
    if (!head)
        exit(666); // throw "咖啡洒键盘上了！";
    head->next = nullptr;
    for (auto &term: poly) {
        Node *new_node = new Node();
        new_node->coef = term.first;
        new_node->expn = term.second;
        new_node->next = nullptr;

        Node *p = head;
        while (p->next && p->next->expn > new_node->expn)
            p = p->next;
        new_node->next = p->next;
        p->next = new_node;
    }
    return head;
}

void DestroyList(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

void PrintList(Node *head) {
    Node *p = head -> next;
    bool firstTerm = true;

    while (p && p -> expn != 0) {
        if (!firstTerm && p -> coef > 0)
            cout << "+";

        if (p -> coef == -1)
            cout << "-x^" << p -> expn;
        else if (p->coef == 1)
            cout << "x^" << p -> expn;
        else
            cout << p -> coef << "x^" << p -> expn;

        firstTerm = false;
        p = p -> next;
    }

    if (p && p -> expn == 0) {
        if (!firstTerm && p -> coef > 0)
            cout << "+";

        cout << p -> coef;
    }
    cout << endl;
}

vector<pair<int, int>> InputPoly() {
    vector<pair<int, int> > poly;
    int terms;
    cout << "请输入多项式的项数：";
    cin >> terms;

    while (terms <= 0) {
        cout << "项数必须>0，请重新输入：";
        cin >> terms;
    }

    for (int i = 0; i < terms; i++) {
        int coef, expn;
        cout << "第" << i + 1 << "项（系数 指数）：";
        cin >> coef >> expn;
        poly.push_back({coef, expn});
    }
    return poly;
}

int main() {
    cout << "===== 多项式A =====" << endl;
    auto poly1 = InputPoly();
    cout << "===== 多项式B =====" << endl;
    auto poly2 = InputPoly();

    Node *A = CreateList(poly1);
    Node *B = CreateList(poly2);

    cout << "多项式A：";
    PrintList(A);
    cout << "多项式B：";
    PrintList(B);

    DestroyList(A);
    DestroyList(B);
    return 0;
}
