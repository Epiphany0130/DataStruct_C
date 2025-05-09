#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char SELemType;

typedef struct Slode {
    SELemType data;
    struct Slode *next;
} Slode, *LinkStack;

void initS(LinkStack *s) {
    *s = NULL;
}

void Push(LinkStack *s, SELemType e) {
    LinkStack p = (LinkStack)malloc(sizeof(Slode));
    p->data = e;
    p->next = *s;
    *s = p;
}

SELemType Pop(LinkStack *s) {
    LinkStack p = *s;
    SELemType e = p->data;
    *s = p->next;
    free(p);
    return e;
}

void judge(char a[], int n) {
    LinkStack s;
    initS(&s);  // 传地址以修改 s
    
    for (int i = 0; i < n; i++) {
        Push(&s, a[i]);
    }

    char b[100];
    int i = 0;

    while (s != NULL) {
        b[i++] = Pop(&s);
    }
    b[i] = '\0';

    if (!strcmp(a, b)) {
        printf("是回文串");
    } else {
        printf("不是回文串");
    }
}

int main() {
    char a[100];
    scanf("%99s", a);

    int n = strlen(a);
    judge(a, n);

    return 0;
}
