//
// Created by 谷煜奇 on 25-5-10.
//

#include <iostream>
#include <cstdlib>
#include <string>
#define MAXSIZE 100
typedef char ElemType;

typedef struct {
    ElemType *top;
    ElemType *base;
    int StackSize;
}SqStack;

int InitStack(SqStack *s) {
    s -> base = (ElemType *)malloc(sizeof(ElemType) * MAXSIZE);
    if (!s -> base)
        return 0;
    s -> top = s -> base;
    s -> StackSize = MAXSIZE;
    return 1;
}

int Push(SqStack *s, ElemType e) {
    if (s -> top - s -> base == s -> StackSize)
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

int In(char ch) {
    switch (ch) {
        case '+': case '-': case '*': case '/': case '(': case ')': case '#':
            return 1; break;
        default:
            return 0; break;
    }
}

char Precede(char a, char b) {
    switch (a) {
        case '+':
        case '-':
            if (b == '+' || b == '-' || b == ')' || b == '#')
                return '>';
            return '<';
        case '*':
        case '/':
            if (b == '(')
                return '<';
            return '>';
        case '(':
            if (b == ')')
                return '=';
            return '<';
        case ')':
            return '>';
        case '#':
            if (b == '#')
                return '=';
            return '<';
        default:
            return '<';
    }
}

char Operate(char a, char op, char b) {
    int num_a = a - '0';
    int num_b = b - '0';

    int result;
    switch (op) {
        case '+': result = num_a + num_b; break;
        case '-': result = num_a - num_b; break;
        case '/': result = num_a / num_b; break;
        case '*': result = num_a * num_b; break;
    }

    return result + '0';
}

ElemType GetTop(SqStack s) {
    if (s.top == s.base) {
        return '\0';
    }
    return *(s.top - 1);
}

char EvaluateExpression(char expr[]) {
    SqStack opnd, optr;
    InitStack(&opnd);
    InitStack(&optr);
    Push(&optr, '#');

    int i = 0;
    while (expr[i] != '#' || GetTop(optr) != '#') {
        char ch = expr[i];
        if (!In(ch)) {
            Push(&opnd, ch);
            i++;
        } else {
            char theta;
            switch (Precede(GetTop(optr), ch)) {
                case '<' :
                    Push(&optr, ch);
                    i++;
                    break;
                case '>' :
                    Pop(&optr, &theta);
                    char b, a;
                    Pop(&opnd, &b);
                    Pop(&opnd, &a);
                    Push(&opnd, Operate(a, theta, b));
                    break;
                case '=' :
                    Pop(&optr, &theta);
                    i++;
                    break;
            }
        }
    }
    return GetTop(opnd);
}