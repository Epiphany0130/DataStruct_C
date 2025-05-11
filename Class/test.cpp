#include <iostream>
#include <stdlib.h>
using namespace std;
#define MAXSIZE 100
typedef int ElemType;

typedef struct {
    ElemType *top;
    ElemType *base;
    int stackSize;
}SqStack;

int InitStack(SqStack *s) {
    s -> base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    if (!s -> base)
        return 0;
    s -> top = s -> base;
    s -> stackSize = MAXSIZE;
    return 1;
}

int Push(SqStack *s, ElemType e) {
    if (s -> top - s -> base == s -> stackSize)
        return 0;
    *(s -> top) = e;
    s -> top ++;
    return 1;
}

int Pop(SqStack *s, ElemType *e) {
    if (s -> top == s -> base)
        return 0;
    s -> top --;
    *e = *(s -> top);
    return 1;
}

int StackEmpty(SqStack s) {
    return (s.top == s.base);
}

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
        if (e < 10)
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
}