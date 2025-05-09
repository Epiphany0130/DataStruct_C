//
// Created by 谷煜奇 on 25-5-9.
//


#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAXSIZE 100
typedef int ElemType;

typedef struct {
    ElemType *base;
    ElemType *top;
    int stackSize;
}SqStack;

// init
int InitStack(SqStack *s) {
    s -> base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    if (!s -> base)
        return 0;
    s -> top = s -> base;
    s -> stackSize = MAXSIZE;
    return 1;
}

// push
int Push(SqStack *s, ElemType e) {
    if (s -> top - s -> base == s -> stackSize)
        return 0;
    *(s -> top) = e;
    s -> top ++;
    return 1;
}

// pop
int Pop(SqStack *s, ElemType *e) {
    if (s -> top == s -> base)
        return 0;
    s -> top --;
    *e = *(s -> top);
    return 1;
}

// empty
int StackEmpty(SqStack s) {
    return (s.top == s.base);
}

//  转换
void tenToK(int n, int k) {

    SqStack s;
    int e;

    InitStack(&s);

    while (n) {
        e = n % k;
        Push(&s, e);
        n /= k;
    }

    while (!StackEmpty(s)) {
        Pop(&s, &e);
        if(e < 10)
            cout << e;
        else
            cout << char('A' + e - 10);
    }
    cout << endl;
}

int main() {
    int n, k;
    cout << "cin n:";
    cin >> n;
    cout << "cin k:";
    cin >> k;
    tenToK(n, k);
    return 0;
}