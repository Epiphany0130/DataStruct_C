#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
typedef char SElemType;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

// 初始化栈
int InitStack(SqStack *s) {
    s->base = (SElemType*)malloc(sizeof(SElemType) * MAXSIZE);
    if (!s->base) return 0;
    s->top = s->base;
    s->stacksize = MAXSIZE;
    return 1;
}

// 入栈
int Push(SqStack *s, SElemType n) {
    if (s->top - s->base == s->stacksize) return 0;
    *(s->top) = n;
    s->top++;
    return 1;
}

// 出栈
int Pop(SqStack *s, SElemType *n) {
    if (s->base == s->top) return 0;
    s->top--;
    *n = *(s->top);
    return 1;
}

// 获取栈顶元素
SElemType GetTop(SqStack s) {
    if (s.base == s.top) return 0;
    return *(s.top - 1);
}

// 判断是否是运算符
int In(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#') {
        return 1;
    } else {
        return 0;
    }
}

// 比较运算符优先级
char Precede(char a, char b) {
    switch (a) {
        case '+':
        case '-':
            if (b == '+' || b == '-' || b == ')' || b == '#') return '>';
            else return '<';
        case '*':
        case '/':
            if (b == '(') return '<';
            else return '>';
        case '(':
            if (b == ')') return '=';
            else return '<';
        case ')':
            return '>';
        case '#':
            if (b == '#') return '=';
            else return '<';
        default:
            return '<';
    }
}

// 运算函数（用字符表示的数字）
char Operate(char a, char op, char b) {
    int x = a - '0';
    int y = b - '0';
    int res = 0;
    switch (op) {
        case '+': res = x + y; break;
        case '-': res = x - y; break;
        case '*': res = x * y; break;
        case '/': res = x / y; break;
    }
    return res + '0'; // 转回字符存入栈中
}

// 表达式求值
char EvaluateExpression(char ch[], int n) {
    SqStack OPTR, OPND;
    char theta, a, b, x;
    InitStack(&OPTR);
    Push(&OPTR, '#');
    InitStack(&OPND);
    int i = 0;

    while ((ch[i] != '#' || GetTop(OPTR) != '#') && i < n) {
        if (!In(ch[i])) {
            Push(&OPND, ch[i]);
            i++;
        } else {
            switch (Precede(GetTop(OPTR), ch[i])) {
                case '<':
                    Push(&OPTR, ch[i]);
                    i++;
                    break;
                case '>':
                    Pop(&OPTR, &theta);
                    Pop(&OPND, &b);
                    Pop(&OPND, &a);
                    Push(&OPND, Operate(a, theta, b));
                    break;
                case '=':
                    Pop(&OPTR, &x);
                    i++;
                    break;
            }
        }
    }
    return GetTop(OPND);
}

// 主函数
int main() {
    char a[20];
    printf("请输入表达式(以#结束): ");
    scanf("%s", a);
    int n = strlen(a);
    char result = EvaluateExpression(a, n);
    printf("计算结果: %d\n", result - '0');
    return 0;
}
