#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
typedef char SELemType;

typedef struct {
    SELemType *base;
    SELemType *top; // 指向栈顶元素的后继单元
    int stacksize;  // 栈容量
} SqStack; // 你原来写成了 Sqlstack，后面用了 SqStack，我统一改为 SqStack

int InitStack(SqStack *s) {
    s->base = (SELemType *)malloc(sizeof(SELemType) * MAXSIZE);
    if (!s->base) return 0;
    s->top = s->base;
    s->stacksize = MAXSIZE;
    return 1;
}

int Push(SqStack *s, SELemType n) {
    if (s->top - s->base == s->stacksize) return 0;
    *(s->top) = n;  // 错误：原来是 *s->top += n
    s->top++;
    return 1;
}

int Pop(SqStack *s, SELemType *n) {
    if (s->base == s->top) return 0;
    s->top--;
    *n = *(s->top);
    return 1;
}

SELemType GetTop(SqStack *s) {
    if (s->base == s->top) return 0; // 注意：不能返回 0 给 char 类型，这里不严谨，但我保留
    return *(s->top - 1);
}

int empty(SqStack *s) {
    return s->base == s->top;
}

int In(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#';
}

char Precede(char a, char b) {
    switch (a) {
        case '+':
        case '-':
            return '<';
        case '*':
        case '/':
            if (b == '+' || b == '-') return '>';
            else return '<';
        default:
            return '<'; // 默认处理
    }
}

void convert(char ch[], int n) {
    SqStack s1, s2, s3;
    InitStack(&s1);
    InitStack(&s2);
    InitStack(&s3);
    char t;

    for (int i = 0; i < n; i++) {
        if (!In(ch[i])) {
            Push(&s2, ch[i]);
        } else {
            switch (ch[i]) {
                case '(':
                    Push(&s1, ch[i]);
                    break;
                case ')':
                    Pop(&s1, &t);
                    while (t != '(') {
                        Push(&s2, t);
                        Pop(&s1, &t);
                    }
                    break;
                default:
                    if (empty(&s1) || GetTop(&s1) == '(') {
                        Push(&s1, ch[i]);
                        break;
                    } else {
                        while (!empty(&s1) && GetTop(&s1) != '(') {
                            if (Precede(ch[i], GetTop(&s1)) == '>') {
                                break;
                            } else {
                                Pop(&s1, &t);
                                Push(&s2, t);
                            }
                        }
                        Push(&s1, ch[i]);
                    }
                    break;
            }
        }
    }

    while (!empty(&s1)) {
        Pop(&s1, &t);
        Push(&s2, t);
    }

    while (!empty(&s2)) {
        Pop(&s2, &t);
        Push(&s3, t);
    }

    while (!empty(&s3)) {
        Pop(&s3, &t);
        printf("%c", t);
    }

    printf("\n");
}

int main() {
    char a[20];
    printf("请输入表达式（操作数为1-9的数字）：");
    scanf("%s", a);
    int n = strlen(a);
    convert(a, n);
    return 0;
}