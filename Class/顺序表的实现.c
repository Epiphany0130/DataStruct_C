#include <stdio.h>
#include <stdlib.h> // 标准库头文件，宏和通用工具函数
#define MAXSIZE 1000 // 线性表存储空间的初始分配量，n 的值
#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef int elemType;// 元素类型
typedef struct
{
    elemType *elem;// 线性表首地址
    int length;// 当前的长度
} SqList;

// 初始化一个空的线性表
int InitList_Sq(SqList *L)
{
    L->elem=(elemType*)malloc(sizeof(elemType)*MAXSIZE);
    if(!L->elem)exit(OVERFLOW);//overflow
    L->length=0;// 初始表为空表
    return OK;
}

// 读取第i个位置的数据元素
int GetElem(SqList *L, int i)
{
    if(i<1||i>L->length)
    return ERROR;
    return L->elem[i-1];
}

//查找元素值e，获得元素值e的位置
int LocateElem(SqList *L, elemType e)
{
    int i;
    for(i=0;i<=L->length;i++)
    {
    if(L->elem[i]==e)
    return i+1;
    }
    return 0;
}

//向表中位置:插入元素
int ListInsert(SqList *L,int i,int e)
{
//在顺序表_中第i个位置插入新的元素e
    int j;
    if((i<1)||(i>L->length+1))
    return ERROR;
    if(L->length==MAXSIZE)
    return ERROR;
    for(j=L->length-1;j>=i-1;j--)
    L->elem[j+1]=L->elem[j];
    L->elem[i-1]=e;
    L->length++;
    return OK;
}

//删除第i个元素
int ListDelete(SqList *L, int i)
{//在顺序表L中删除第i个元素
    int j;
    if((i<1)||(i>L->length))
    return ERROR;
    for(j=i;j<=L->length-1;j++)
    L->elem[j-1]=L->elem[j];
    --L->length;
    return OK;
}

//遍历顺序表
void TraverseList(SqList *L)
{
    int i;
    for(i=0; i<L->length; i++)
    {
    printf("%d ",L->elem[i]);
    }
    printf("\n");
    return;
}

//向表尾插入元素
int InsertLast(SqList *L,int e)
{
    if(L->length>=MAXSIZE)
    return ERROR;
    L->elem[L->length]=e;
    L->length++;
    return OK;
}

int main()
{
    SqList list1;
    int n;
    int i=0;
    elemType temp1;
    int j;
    elemType temp2;
    elemType temp3;
    int l;
    int e;
    InitList_Sq(&list1);
    printf("请输入顺序表长度：");
    scanf("%d",&n);
    printf("请输入顺序表各个元素：");
    for(i=0; i<n; i++) //插入数据元素
    {
    scanf("%d",&temp1);
    InsertLast(&list1,temp1);
    }
    printf("顺序表中各个元素的值为：");
    TraverseList(&list1);//遍历顺序表，获得顺序表的元素
    printf("请输入想要获取的值的位置：");
    scanf("%d",&j);
    temp2=GetElem(&list1, j);//取值，取第j个位置的数据元素
    printf("所获取的数据元素数值为：%d\n",temp2);
    printf("请输入想要查找的数据元素：");
    scanf("%d",&temp3);
    l = LocateElem(&list1, temp3);//查找，查找数据元素temp3，得到数据元素的位置
    printf("想要查找的数据元素位置为：%d\n",l);
    printf("输入想要插入的值e：");
    scanf("%d",&e);
    printf("向第%d个位置插入值e：%d\n", l, e);
    printf("插入后顺序表的数据元素为：");
    ListInsert(&list1, l, e);
    TraverseList(&list1);
    printf("删除顺序表中的第%d个元素\n",l);
    ListDelete(&list1, l);
    printf("删除后顺序表的数据元素为：");
    TraverseList(&list1);
    return 0;
}