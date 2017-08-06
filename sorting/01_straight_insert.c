//直接排序
#include <stdio.h>

int main()
{
    const int count = 9;
    int L[count] = {0, 49, 38, 65, 97, 76, 13, 27, 49};
    int i, j;
    //对顺序表作直接插入排序。
    for (i = 2; i < count; i++)
    {
        if (L[i] < L[i - 1])
        {
            L[0] = L[i];
            int j = i - 1;
            do 
            {
                L[j + 1] = L[j];
                j--;
            } while (L[0] < L[j]);
            L[j + 1] = L[0];
        }
    }
    //打印排序结果。
    for (i = 0; i < count; ++ i)
    {
        printf("%d\t", L[i]);
    }
    printf("\n"); 
}

// 时间复杂度: O(n^2)
// 空间复杂度: O(n)
