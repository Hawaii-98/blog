#include <stdio.h>

#define MAX 20

typedef char String[MAX + 1];

//生成一个其值等于chars的串T
void ProduceString(String S, char *chars) //利用指针变量指向字符串！
{
    if (strlen(chars) > MAX)
        printf("字符串生成错误！\n");
    else
    {
        int i;
        S[0] = strlen(chars);
        for (i = 1; i <= S[0]; i++)
        {
            S[i] = *(chars + i - 1);
        }
        printf("字符串生成完毕。\n");
    }
}

//输出字符串T
void PrintString(String S)
{
    if (S[0] == 0)
        printf("待输出的字符串为空！\n");
    else
    {
        int i;
        printf("字符串中的字符有：\n");
        for (i = 1; i <= S[0]; i++)
        {
            printf("%c\n", S[i]);
        }
    }
}

//输出next数组
void PrintNext(int next[], int length)
{
    int i;
    printf("next数组为：\n");
    for (i = 0; i < length; i++)
    {
        printf("%d", next[i]);
    }
    printf("\n");
}

//朴素的模式匹配法---返回子串在主串中pos之后第一次出现的位置
void Index(String S, String T, int pos)
{
    int i = pos;
    int j = 1;
    while (i <= S[0] && j <= T[0]) //因为要遍历，所以用到了循环，此处可以取到等号
    {
        if (S[i] == T[j]) //两字母相等，指针后移
        {
            i++;
            j++;
        }
        else //两字母不相等，指针回溯，重新开始匹配。
        {
            i = i - j + 2; // i退回到主串上次匹配首位的下一位
            j = 1;         // j退回到子串T的首位
        }
    }
    if (j > T[0]) //如果退出循环的原因是子串已经循环完毕
    {
        printf("该子串在主串中的位置为：%d\n", i - T[0]);
    }
    else
    {
        printf("该子串在主串中不存在！\n");
    }
}

//通过计算返回子串T的next数组。
void get_next(String T, int *next) 
{
	int i,k;
  	i=1;
  	k=0;
  	next[1]=0;
  	while (i<T[0])  /* 此处T[0]表示串T的长度 */
 	{
    	if(k==0 || T[i]== T[k]) 
		{
      		++i;  
			++k;  
			next[i] = k;
    	} 
		else 
			k= next[k];	/* 若字符不相同，则k值回溯 */
  	}
}






/*************************主函数*********************************/
void main()
{
    String S, T;
    ProduceString(S, "asdfgashetas");
    ProduceString(T, "as");
    Index(S, T, 2);
}
