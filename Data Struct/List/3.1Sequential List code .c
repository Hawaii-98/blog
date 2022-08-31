#include <stdio.h>

#define MAX 20

//结构体定义
typedef struct
{
    int data[MAX];
    int length;
} sqList;

//初始化线性表
int InitList(sqList *L)
{
    L->length = 0;
    return 666;
}

//向线性表中插入元素（向第i个位置插入元素e）
int InsertList(sqList *L, int e, int i)
{
    int k;
    if (L->length == MAX)
        printf("线性表已满，无法插入元素!\n");
    if (i > L->length + 1 || i < 0)
        printf("插入元素的位置不对！\n");
    if (i <= L->length)
    {
        for (k = L->length - 1; k >= i - 1; k--) //如果插入位置不是最后一个，则所有元素向后移动一个
        {                                        //注意是从后向前遍历
            L->data[k + 1] = L->data[k];
        }
    }
    L->data[i - 1] = e; //赋值
    L->length++;        //线性表长度加一

    printf("元素已经插入!\n");
}

//逐个输出线性表中的元素
int PrintList(sqList L)
{
    int j;
    int x;
    printf("线性表中现有的元素为\n");
    for (j = 0; j < L.length; j++)
    {
        x = L.data[j];
        printf("%d\n", x);
    }
}

//询问并返回线性表中的第i个元素的值，赋给e，并进行了适当的交互。
int GetElem(sqList L)
{
    int e;
    int i;

    printf("你想查询线性表中的哪个位置的元素，请输入：\n");
    if (scanf("%d", &i) == 1) //如果输入格式正确，对输入的值进行判断
    {
        if (i < 1 || i > L.length) //如果位置不对，返回错误
            printf("线性表中没有第%d个元素！\n", i);
        else
        {
            e = L.data[i - 1];
            printf("你查询的线性表位置的元素为%d\n", L.data[i - 1]);
            return e;
        }
    }
    else
    {
        printf("你输入的不对哦！\n");
    }
}

//返回线性表中第一个和e值相等的数据元素的位置
int LocateElem(sqList L, int e)
{
    int i;
    if (L.length == 0)
        printf("震惊！线性表中根本没有元素！\n");
    for (i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
            printf("元素%d在循序表的第%d个位置\n", e, i + 1);
        break; //找到就退出循环
    }
    if (i == L.length)
        printf("你要找的元素不存在哦！\n");
}

//删除线性表中第i个数据元素，将这个元素的值赋给e
int DeleteLite(sqList *L, int i)
{
    int e;
    if (L->length == 0)
        printf("线性表为空！\n");
    if (i < 1 || i > L->length)
        printf("线性表中不存在这个位置的元素！\n");
    e = L->data[i - 1];
    if (i < L->length)
    {
        int k;

        for (k = i - 1; k <= L->length; k++)    //如果删除的元素不是最后一个，则后面的元素都向前挪一个
            L->data[k] = L->data[k + 1];
    }
    L->length--;                                 //线性表的长度减一

    return e;
}

//联合体函数--此处留白，学会了来继续写

int main()
{
    int flag;
    int i;
    sqList L;
    int e;
    int j;
int k;
    flag = InitList(&L);
    printf("初始化线性表之后的线性表长度是%d\n", L.length);
    printf("线性表初始化真的%d\n", flag);
    for (i = 1; i < 6; i++)
        InsertList(&L, i, 1);
    printf("在L的表头依次插入1～5后：L.data=");
    PrintList(L);

    printf("插入元素之后的线性表长度是%d\n", L.length);
    GetElem(L);        
    LocateElem(L, 5);

    for (j = 1; j <= 10; j++)
        InsertList(&L, j, j + 5);
    printf("在现有的线性表L的表尾依次插入1～10后：");
    PrintList(L);

    k=DeleteLite(&L, 6);
    printf("在现有的线性表L中删除第六个元素后：");
    PrintList(L);
// printf("删除的元素是：%d", DeleteLite(&L, 6));--不要用这个语句输出元素，因为实际上又调用了一遍DeleteLite函数！！
    printf("删除的元素是：%d", k);               //所以此处引入变量k，将函数的值传递给k!

}
