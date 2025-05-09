#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100
typedef char SElemType;

typedef struct {
    SElemType *base;
    SElemType *top;  // 指向栈顶元素的后继单元
    int stacksize;   // 栈容量
} SqStack;

// 初始化栈
int InitStack(SqStack *s) {
    s->base = (SElemType*)malloc(sizeof(SElemType)*MAXSIZE);
    if(!s->base) return 0;
    s->top = s->base;
    s->stacksize = MAXSIZE;
    return 1;
}

// 入栈
int Push(SqStack *s, SElemType n) {
    if(s->top - s->base == s->stacksize) return 0;
    *(s->top) = n;
    s->top++;
    return 1;
}

// 出栈
SElemType Pop(SqStack *s) {
    if(s->base == s->top) return 0;
    s->top--;
    return *(s->top);
}

// 判断栈是否为空
int StackEmpty(SqStack s) {
    if(s.top == s.base) {
        return 1;
    } else {
        return 0;
    }
}

// 检查括号匹配
int check_bracket(char a[], int n) {
    SqStack S;
    InitStack(&S);

    for (int i = 0; i < n; i++) {
        if(a[i] == '[' || a[i] == '(') {
            Push(&S, a[i]);
        }
        if(a[i] == ']' || a[i] == ')') {
            switch (a[i]) {
                case ']':
                    if(Pop(&S) != '[') {
                        printf("括号不匹配\n");
                        return 0;
                    }
                    break;
                case ')':
                    if(Pop(&S) != '(') {
                        printf("括号不匹配\n");
                        return 0;
                    }
                    break;
            }
        }
    }

    if(!StackEmpty(S)) {
        printf("括号不匹配\n");
        return 0;
    }
    printf("该表达式括号正确\n");
    return 1;
}

int main() {
    char a[20];
    printf("请输入表达式: ");
    scanf("%s", a);
    int n = strlen(a);

    check_bracket(a, n);
    return 0;
}