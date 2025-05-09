#include <stdio.h>
#include <stdlib.h>

//定义单链表结点
typedef struct Node
{
    int coef;    //coef表示系数
    int expn;    //expn表示指数
    struct Node *next;
} Node;

// 算法2.18 多项式的创建
// 借助一个数组，来存放用户输入的多项式的系数和指数。
Node *CreatePolyn(int a[], int n){
    Node *p, *s, *pre, *q;
    int i;

    p = (Node *)malloc(sizeof(Node));
    p->next = NULL;

    for(i=0; i<n; i=i+2){
        s = (Node *)malloc(sizeof(Node));
        s->coef = a[i];
        s->expn = a[i+1];
        pre = p;
        q = p->next;
        while(q && q->expn<s->expn){
            pre = q;
            q = q->next;
        }
        s->next = q;
        pre->next = s;
    }

    return p;
}

Node *AddPolyn(Node *Pa, Node *Pb){
    Node *p1, *p2, *p3;
    Node *r;
    int sum;

    p1 = Pa->next;
    p2 = Pb->next;
    p3 = Pa;

    while(p1 && p2){
        if(p1->expn == p2->expn){
            sum = p1->coef + p2->coef;
            if(sum != 0){
                p1->coef = sum;
                p3->next = p1;
                p3 = p1;
                p1 = p1->next;
                r = p2;
                p2 = p2->next;
                free(r);
            }
            else{
                r = p1;
                p1 = p1->next;
                free(r);
                r = p2;
                p2 = p2->next;
                free(r);
            }
        }
        else if(p1->expn < p2->expn){
            p3->next = p1;
            p3 = p1;
            p1 = p1->next;
        }
        else{
            p3->next = p2;
            p3 = p2;
            p2 = p2->next;
        }
    }

    if (p1 != NULL) p3->next = p1;
    else p3->next = p2;

    free(Pb);
    return Pa;
}

//算法：遍历输出多项式
//遍历输出单链表各数据元素值，且要符合输出格式
void TraversePoln(Node *first){
    Node *p = first->next;
    if (p != NULL)    //输出第一项
        printf("%dx^%d", p->coef, p->expn);
    p = p->next;
    while (p != NULL)
    {
        if (p->coef > 0)    //输出系数的正号或负号
            printf("+%dx^%d", p->coef, p->expn);
        else
            printf("%dx^%d", p->coef, p->expn);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    Node *A, *B;
    int m,n,w,v,i,k;
    int a[2000];
    int b[2000];

    //1) 输入第一个多项式的项数n，并以此输入该多项式的系数和指数。
    //  遍历输出第一个多项式的所有数据元素。
    printf("你想要输入的第一个多项式为多少项的多项式：");
    scanf("%d", &m);
    n = 2*m;

    printf("请依次输入多项式的系数和指数：\n");
    for(i=0; i<n; i++) {
        if(i%2==0)
        {
            printf("系数为：");
            scanf("%d",&a[i]);
        }
        else
        {
            printf("指数为：");
            scanf("%d",&a[i]);
        }
    }

    A = CreatePolyn(a,n);
    printf("第一个多项式为：");
    TraversePoln(A);

    //2) 输入第二个多项式的项数n，并以此输入该多项式的系数和指数。
    //  遍历输出第二个多项式的所有数据元素。
    printf("你想要输入的第二个多项式为多少项的多项式：");
    scanf("%d", &w);
    v = 2*w;

    printf("请依次输入多项式的系数和指数：\n");
    for(k=0; k<v; k++) {
        if(k%2==0)
        {
            printf("系数为：");
            scanf("%d", &b[k]);
        }
        else
        {
            printf("指数为：");
            scanf("%d", &b[k]);
        }
    }

    B = CreatePolyn(b,v);
    printf("第二个多项式为：");
    TraversePoln(B);

    //3) 进行两个多项式的计算，并将相加结果放于第一个多项式A指示的单链表中。
    //  遍历输出第一个多项式的所有数据元素，也就是两个多项式相加的结果。
    A = AddPolyn(A, B);
    printf("两个多项式相加的结果是：");
    TraversePoln(A);

    return 0;
}