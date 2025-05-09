#include <stdio.h>
#include <stdlib.h> //标准库头文件，宏和通用工具函数

#define OK 1
#define ERROR -1
#define OVERFLOW -2

typedef int ElemType;//元素类型
typedef struct node{
    ElemType data;
    struct node *next;
}LNode;

// 算法2.7 单链表的取值
int GetElem(LNode *L, int i)
{//在带头节点的单链表中根据序号i获取元素的值
    LNode *p;
    int j;

    p=L->next;
    j=1;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i) return ERROR;
    return p->data;
}

//算法2.8变型 单链表的按值查找（查位置序号，不是地址）
int LocateElem(LNode *L, ElemType e)
{//在带头节点的单链表L中查找值为e的元素
    int j;
    LNode *p;

    p=L->next;
    j=1;
    while(p && p->data != e)
    {
        p=p->next;
        j++;
    }
    if(p) return j;
    else return 0;
}

// 算法2.9 单链表的插入
int ListInsert(LNode *L, int i, ElemType e)
{//在带头节点的单链表L中第i个位置插入值为e的新节点
    int j;
    LNode *p, *s;

    p=L;
    j=0;
    while(p && (j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i-1) return ERROR;
    s=(LNode*)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}

//算法2.10 单链表的删除
int ListDelete(LNode *L, int i)
{//在带头节点的单链表L中，删除第i个元素
    LNode *p, *q;
    int j;

    p=L;
    j=0;
    while((p->next)&&(j<i-1))
    {
        p=p->next;
        ++j;
    }
    if(!(p->next)||(j>i-1))
        return ERROR;
    q=p->next;
    p->next=q->next;
    free(q);
    return OK;
}

// 算法2.12 后插法创建单链表
LNode *CreateList_R(ElemType *array, int n)
{// 正序输入n个元素的值，建立带表头节点的单链表L
    LNode *L;
    LNode *r, *p;
    int i;

    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
    r=L;
    for(i=0; i<n; ++i)
    {
        p=(LNode*)malloc(sizeof(LNode));
        p->data=*(array++);
        p->next=NULL;
        r->next=p;
        r=p;
    }
    return L;
}

//遍历输出单链表
void TraverseList(LNode *L)
{
    LNode *p;
    p=L->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}

int main()
{
    LNode *list;
    int n;
    ElemType a[1000];
    int k=0;
    int j;
    ElemType temp1;
    ElemType temp2;
    int l;
    int e;
    int m;
    int w;

    //1)输出表的长度n，并依次输入单链表初始存放的n个元素值。
    //遍历输出单链表的所有数据元素。
    printf("请输入单链表长度：");
    scanf("%d",&n);

    printf("请正位序输入单链表各个元素：");
    for(k=0;k<n;k++) {
        scanf("%d",&a[k]);
    }
    list=CreateList_R(a, n);
    printf("单链表中各个元素的值为：");
    TraverseList(list);//遍历单链表，获得单链表的元素

    //2)输入想要获取的数据元素位置序号。
    //输出该位置的数据元素值。
    printf("请输入想要获取的值的位置：");
    scanf("%d",&j);
    temp1=GetElem(list, j);//取值，取第j个位置的数据元素
    printf("所获取的数据元素值为：%d\n", temp1);

    //3)输入想要获取位置的数据元素值。
    //输出该数据元素的位置序号。
    printf("请输入想要查找的数据元素：");
    scanf("%d", &temp2);
    l = LocateElem(list, temp2);//查找，查找数据元素temp2，得到数据元素的位置
    printf("想要查找的数据元素位置为：%d\n", l);

    //4)输入想要插入数据元素的位置以及想要插入的数据元素。
    //输出在该位置插入数据元素后单链表中所有的数据元素。
    printf("输入想要插入的值：");
    scanf("%d",&e);
    printf("向第几个位置插入该值：");
    scanf("%d",&m);
    ListInsert(list, m, e);
    printf("向第%d个位置插入值%d后，插入后单链表的数据元素为：",m,e);
    TraverseList(list);

    //5)输入想要删除数据元素的位置。
    //输出在该位置删除数据元素后单链表中的所有数据元素。
    printf("输入想要删除单链表中的第几个元素：");
    scanf("%d",&w);
    ListDelete(list, w);
    printf("删除第%d个元素后，单链表的数据元素为：", w);
    TraverseList(list);
    
    return 0;
}