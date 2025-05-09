/*顺序表实现有序表的合并*/

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR -1
#define OVERFLOW -2
#define MAXSIZE 100

//定义顺序表
typedef struct
{
    int *elem;
    int length;
} Sqlist;
int num_a = 0, num_b = 0;
char st = 'A';

//创建顺序表
int InitList_Sq(Sqlist *L)
{
    L->elem=(int*)malloc(sizeof(int)*MAXSIZE);
    if(!L->elem) exit(OVERFLOW);//overflow
    L->length=0;//初始表为空表
    return OK;
}

//向表尾插入元素
int InsertLast(Sqlist *L,int e)
{
    if(L->length>=MAXSIZE)
    return ERROR;
    L->elem[L->length]=e;
    L->length++;
    return OK;
}

//依次输出顺序表里的每个元素
void Traverselist(Sqlist *L)
{
    int i;
    for(i=0; i<L->length; i++)
    {
        if(i==L->length-1)
        {
            printf("%d",L->elem[i]);
        }
        else
            printf("%d ",L->elem[i]);
    }
    printf("\n");
    return;
}

// 算法2.16 顺序有序表的合并
void Mergelist_Sq(Sqlist *LA, Sqlist *LB, Sqlist *LC)
{
    // 已知顺序有序表LA和LB的元素按值非递减排列
    // 归并LA和LB得到新的顺序有序表LC，LC的元素也按值非递减排列

    int *pa, *pb, *pc, *pa_last, *pb_last;
    LC->length = LA->length + LB->length; // 新表长度为待合并两表的长度之和
    LC->elem = (int*)malloc(sizeof(int)*(LC->length)); // 为合并后的新表分配一个数组空间
    pc = LC->elem; // 指针pc指向新表内的第一个元素
    pa = LA->elem;
    pb = LB->elem; // 指针pa和pb的初值分别指向两个表的一次元素

    pa_last = LA->elem + LA->length - 1; // 指针pa_last指向LA表的最后一个元素
    pb_last = LB->elem + LB->length - 1; // 指针pb_last指向LB表的最后一个元素

    while (pa <= pa_last && pb <= pb_last) //两个表都非空
    {
        if (*pa <= *pb) //依次"摘取"两表中值较小的结点插入到LC表的最后
            *pc++ = *pa++;
        else
            *pc++ = *pb++;
    }

    while (pa <= pa_last) //LB已到达表尾，依次将LA的剩余元素插入LC表的最后
        *pc++ = *pa++;
    while (pb <= pb_last) //LA已到达表尾，依次将LB的剩余元素插入LC表的最后
        *pc++ = *pb++;
} //MergeList_List

int main() {
    Sqlist La, Lb, Lc;
    int i, k, m, n, temp1, temp2;

    InitList_Sq(&La); //La表的创建
    printf("请输入顺序表A的长度: ");
    scanf("%d",&m);
    printf("请输入顺序表A的各个元素: ");
    for(i=0; i<m; i++) //插入数据元素
    {
        scanf("%d",&temp1);
        InsertLast(&La,temp1);
    }

    InitList_Sq(&Lb); //Lb表的创建
    printf("请输入顺序表B的长度：");
    scanf("%d",&n);
    printf("请输入顺序表B的各个元素：");
    for(k=0; k<n; k++) //插入数据元素
    {
        scanf("%d",&temp2);
        InsertLast(&Lb,temp2);
    }

    Mergelist_Sq(&La, &Lb, &Lc); //将顺序表La和Lb进行合并

    printf("非递减线性表A，B合并后的非递减线性表C为：\n"); //输出合并后的有序顺序表Lc
    Traverselist(&Lc);

    return 0;
}