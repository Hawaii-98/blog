#include<stdio.h>

#define MAX 20

//结构体定义
typedef struct 
{
    int data[MAX];
    int length;
}sqList;

//初始化线性表
int InitList (sqList *L)
{
    L->length=0;
    return 666;
}

int main()
{
   int flag;
   sqList L;

   flag=InitList(&L);
   printf("初始化线性表之后的线性表长度是%d\n",L.length);
   printf("线性表初始化真的%d\n",flag);
}
