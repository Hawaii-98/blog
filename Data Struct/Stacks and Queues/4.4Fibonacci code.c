#include <stdio.h>

//迭代打印斐波那契数列
int Fibonacci1()
{
    int i, j;

    int a[40]; //缺点在于用数组只能输出固定长度的斐波那契数列
    a[0] = 0;
    a[1] = 1;
    for (i = 2; i < 40; i++)
    {
        a[i] = a[i - 1] + a[i - 2];
    }
    printf("迭代显示斐波那契数列：\n");
    for (j = 0; j < 40; j++)
    {
        printf("%d\n", a[j]);
    }
}

//递归打印斐波那契数列
int Fibonacci2(int i)
{

    if (i < 2)
        return (i == 0 ? 0 : 1);
    return (Fibonacci2(i - 1) + Fibonacci2(i - 2));
}

/**************主函数**************/
int main()
{
    Fibonacci1(); //迭代显示斐波那契数列

    printf("递归显示斐波那契数列：\n"); //递归显示斐波那契数列
    int i;
    for (i = 0; i < 40; i++)
    {
        printf("%d\n", Fibonacci2(i));
    }
}
