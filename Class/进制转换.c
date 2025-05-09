#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int SElemType;

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
int Pop(SqStack *s, SElemType *n) {
    if(s->base == s->top) return 0;
    s->top--;
    *n = *(s->top);
    return 1;
}

// 判断栈是否为空
int StackEmpty(SqStack s) {
    if(s.top == s.base) {
        return 1;
    } else {
        return 0;
    }
}

// 进制转换函数
void conversion(int N, int k) {
    SqStack S;
    int e;
    InitStack(&S);    // 初始化空栈S
    while(N) {        // 当N非零时循环
        Push(&S, N%k); // 把N与x的余数压入栈S
        N = N/k;      // N更新为N除以x的商
    }
    while(!StackEmpty(S)) { // 当栈S非空时循环
        Pop(&S, &e);        // 弹出栈顶元素e
        printf("%d", e);    // 输出e
    }
}

int main() {
    int n, k;
    printf("请输入要转换的十进制数: ");
    scanf("%d", &n);
    printf("请输入要转换的进制: ");
    scanf("%d", &k);
    conversion(n, k);
    return 0;
}