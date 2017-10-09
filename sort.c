#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*****************函数声明**************/
void print(int *arr, int n)//打印数组
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void swap(int *a, int *b)//交换值
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void ChooseSort(int * arr, int n);//选择排序

void BubbleSort(int * arr, int n);//冒泡排序

void HeapAdjust(int* array, int parent, int length);  //堆排序
void HeapSort(int* list , int n);

void merge(int x[],int tmp[],int left,int leftend,int rightend);//二路归并排序
void mergeSort(int a[],int tmp[],int left,int right);

void quickSort(int* list, int left, int right);//快速排序

int sortcount = 0;//保存排序的比较次数

int main(int argc, char *argv[])
{

    int n = 0;
    int i;
    int flg = 0;

    int * arr = NULL;
    int * tmp = NULL;
    printf("请输入排序个数（不超过100）及排序方式（1~5）：");
    scanf("%d %d",&n,&flg);
    while (!(n>0 && n<=100) || !( flg>0 && flg<6))
    {
        printf("输入错误，请按照要求重新输入：");
        scanf("%d %d",&n,&flg);
    }

    arr = (int *) malloc (sizeof(int)*n);

    printf("待排序数组：");
    for (i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }

    switch (flg)
    {
    case 1:
        ChooseSort(arr,n);
        break;
    case 2:
        BubbleSort(arr,n);
        break;
    case 3:
        HeapSort(arr,n);
        break;
    case 4:
        tmp = (int *) malloc (sizeof(int)*n);//归并要用到相同大小数组作为临时存储
        mergeSort(arr,tmp,0,n-1);
        free(tmp);//释放临时数组的内存
        break;
    case 5:
        quickSort(arr, 0, n-1);
        break;
    }

    print(arr,n);
    printf("%d\n",sortcount);
    system("pause");
    return 0;
}

void merge(int a[],int tmp[],int leftPos,int rightPos,int rightEnd)
{
    int i;
    int leftEnd = rightPos-1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos+1;
    //主循环
    while(leftPos <= leftEnd && rightPos <= rightEnd)
    {
        sortcount++;//比较次数
        if(a[leftPos] <= a[rightPos])
        {
            tmp[tmpPos++] = a[leftPos++];
        }
        else
        {
            tmp[tmpPos++] = a[rightPos++];
        }
    }

    //将左边 剩余的 元素放进tmp[]里
    while(leftPos <= leftEnd)
    {
        tmp[tmpPos++] = a[leftPos++];
    }

    //将右边 剩余的 元素放进tmp[]里
    while(rightPos <= rightEnd)
    {
        tmp[tmpPos++] = a[rightPos++];
    }
    //将临时数组放进a[]里
    for(i=0;i<numElements;i++,rightEnd--)
    {

        a[rightEnd]=tmp[rightEnd];
    }
}
void mergeSort(int a[],int tmp[],int left,int right)
{
    if(left<right)
    {
        int center=(left+right)/2;
        mergeSort(a,tmp,left,center);
        mergeSort(a,tmp,center+1,right);
        merge(a,tmp,left,center+1,right);
    }
}

void ChooseSort(int * arr, int n)
{
    int i,j;
    for (i = 0; i < n-1; i++)
    {
        for (j = i+1; j < n; j++)
        {
            sortcount++;
            if (arr[i] > arr[j])
            {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void BubbleSort(int a[], int m)
{
    int i,j;
    int flag = 0;  //设定标志，如果第一次循环比较时没有发生交换，则说明数组是升序排序，不用排序，提前结束循环。
    for(i = 0; i < m; i++)  //外层循环控制循环次数
    {
        flag = 0;
        for(j = 0; j < m-1-i; j++)    //内层循环控制每次循环里比较的次数。
        {
            sortcount++;
            if(a[j] > a[j+1])
            {
                swap(&a[j], &a[j+1]);
                flag = 1;
            }
        }

        if(0 == flag)
        {
            break;
        }
     }
}

void HeapAdjust(int* array, int parent, int length)
{

    int temp = array[parent]; // temp保存当前父节
    int child = 2 * parent + 1; // 先获得左孩子
    while (child < length)
    {
        sortcount ++;//比较次数
        // 如果有右孩子结点，并且右孩子结点的值大于左孩子结点，则选取右孩子结点

        if (child + 1 < length && array[child] < array[child + 1])
        {
            child++;
        }
        // 如果父结点的值已经大于孩子结点的值，则直接结束

        if (temp >= array[child])
            break;

        // 把孩子结点的值赋给父结点
        array[parent] = array[child];

        // 选取孩子结点的左孩子结点,继续向下筛选
        parent = child;
        child = 2 * child + 1;
    }
    array[parent] = temp;
}
void HeapSort(int* list , int n)
{
    // 循环建立初始堆
    int i,j;
    sortcount++;//初始化堆的时候算一次比较
    for (i = n / 2; i >= 0; i--)
    {
        HeapAdjust(list, i, n - 1);
    }
    // 进行n-1次循环，完成排序

    for (j = n - 1; j > 0; j--)
    {
        // 最后一个元素和第一元素进行交换
        swap(&list[j], &list[0]);

        // 筛选 R[0] 结点，得到i-1个结点的堆
        HeapAdjust(list, 0, j);
    }
}

void quickSort(int *k,int left,int right)
{
    int i, last;
    if(left<right)
    {
        last=left;
        for(i=left+1;i<=right;i++)
        {
            sortcount++;
            if(k[i]<k[left])
                swap(&k[++last],&k[i]);
        }
        swap(&k[left],&k[last]);
        quickSort(k,left,last-1);
        quickSort(k,last+1,right);
    }
}


