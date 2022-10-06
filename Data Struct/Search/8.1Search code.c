#include "stdio.h"
#include "stdlib.h"

#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

//定义一个待查找的数组
int arr[MAXSIZE] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};

//无哨兵顺序查找，a为数组，n为要查找的数组个数，key为要查找的关键字
int Sequential_Search(int *a, int n, int key)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (a[i] == key)
            return i;
    }
    return 0;
}

//有哨兵顺序查找
int Sequential_Search2(int *a, int n, int key)
{
    int i;
    a[0] = key;
    i = n;
    while (a[i] != key)
    {
        i--;
    }
    return i;
}

//折半查找
int Binary_Search(int *a, int n, int key)
{
    int low, mid, high;
    low = 1;
    high = n;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key < a[mid])
        {
            high = mid - 1;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
}

//插值查找
int Interpolation_Search(int *a, int n, int key)
{
    int low, mid, high;
    low = 1;
    high = n;
    while (low <= high)
    {
        mid = low + (high - low) * (key - a[low]) / (a[high] - a[low]);
        if (key < a[mid])
        {
            high = mid - 1;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
}

//斐波那契查找
int Fibonacci_Search(int *a, int n, int key)
{
    //建立斐波那契数列
    int F[100];
    F[0] = 0;
    F[1] = 1;
    int i;
    for (i = 2; i < 100; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }

    //斐波那契查找
    int low, high, mid, k = 0;
    low = 1;             /* 定义最低下标为记录首位 */
    high = n;            /* 定义最高下标为记录末位 */
    while (n > F[k] - 1) //计算n位斐波那契数列的位置
        k++;
    for (i = n; i < F[k] - 1; i++) //将原数组中不满的数据补全，以便使用斐波那契查找；
        a[i] = a[n];
    while (low <= high)
    {
        mid = low + F[k - 1] - 1;
        if (key < a[mid])
        {
            high = mid - 1;
            k = k - 1;
        }
        else if (key > a[mid])
        {
            low = mid + 1;
            k = k - 2;
        }
        else
        {
            if (mid <= n)
            {
                return mid;
            }
            else
            {
                return n;
            }
        }
    }
    return 0;
}

/****************主函数*************************/
int main()
{
    int result;

    result = Sequential_Search(arr, MAXSIZE, 16);
    printf("Sequential_Search:%d \n", result);

    result = Sequential_Search2(arr, MAXSIZE, 16);
    printf("Sequential_Search2:%d \n", result);

    result = Binary_Search(arr, 10, 62);
    printf("Binary_Search:%d \n", result);

    result = Interpolation_Search(arr, 10, 62);
    printf("Interpolation_Search:%d \n", result);

    result = Fibonacci_Search(arr, 10, 62);
    printf("Fibonacci_Search:%d \n", result);
}
