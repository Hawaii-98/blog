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
}
