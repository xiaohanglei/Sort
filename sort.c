#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*****************��������**************/
void print(int *arr, int n)//��ӡ����
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void swap(int *a, int *b)//����ֵ
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void ChooseSort(int * arr, int n);//ѡ������

void BubbleSort(int * arr, int n);//ð������

void HeapAdjust(int* array, int parent, int length);  //������
void HeapSort(int* list , int n);

void merge(int x[],int tmp[],int left,int leftend,int rightend);//��·�鲢����
void mergeSort(int a[],int tmp[],int left,int right);

void quickSort(int* list, int left, int right);//��������

int sortcount = 0;//��������ıȽϴ���

int main(int argc, char *argv[])
{

    int n = 0;
    int i;
    int flg = 0;

    int * arr = NULL;
    int * tmp = NULL;
    printf("���������������������100��������ʽ��1~5����");
    scanf("%d %d",&n,&flg);
    while (!(n>0 && n<=100) || !( flg>0 && flg<6))
    {
        printf("��������밴��Ҫ���������룺");
        scanf("%d %d",&n,&flg);
    }

    arr = (int *) malloc (sizeof(int)*n);

    printf("���������飺");
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
        tmp = (int *) malloc (sizeof(int)*n);//�鲢Ҫ�õ���ͬ��С������Ϊ��ʱ�洢
        mergeSort(arr,tmp,0,n-1);
        free(tmp);//�ͷ���ʱ������ڴ�
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
    //��ѭ��
    while(leftPos <= leftEnd && rightPos <= rightEnd)
    {
        sortcount++;//�Ƚϴ���
        if(a[leftPos] <= a[rightPos])
        {
            tmp[tmpPos++] = a[leftPos++];
        }
        else
        {
            tmp[tmpPos++] = a[rightPos++];
        }
    }

    //����� ʣ��� Ԫ�طŽ�tmp[]��
    while(leftPos <= leftEnd)
    {
        tmp[tmpPos++] = a[leftPos++];
    }

    //���ұ� ʣ��� Ԫ�طŽ�tmp[]��
    while(rightPos <= rightEnd)
    {
        tmp[tmpPos++] = a[rightPos++];
    }
    //����ʱ����Ž�a[]��
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
    int flag = 0;  //�趨��־�������һ��ѭ���Ƚ�ʱû�з�����������˵���������������򣬲���������ǰ����ѭ����
    for(i = 0; i < m; i++)  //���ѭ������ѭ������
    {
        flag = 0;
        for(j = 0; j < m-1-i; j++)    //�ڲ�ѭ������ÿ��ѭ����ȽϵĴ�����
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

    int temp = array[parent]; // temp���浱ǰ����
    int child = 2 * parent + 1; // �Ȼ������
    while (child < length)
    {
        sortcount ++;//�Ƚϴ���
        // ������Һ��ӽ�㣬�����Һ��ӽ���ֵ�������ӽ�㣬��ѡȡ�Һ��ӽ��

        if (child + 1 < length && array[child] < array[child + 1])
        {
            child++;
        }
        // ���������ֵ�Ѿ����ں��ӽ���ֵ����ֱ�ӽ���

        if (temp >= array[child])
            break;

        // �Ѻ��ӽ���ֵ���������
        array[parent] = array[child];

        // ѡȡ���ӽ������ӽ��,��������ɸѡ
        parent = child;
        child = 2 * child + 1;
    }
    array[parent] = temp;
}
void HeapSort(int* list , int n)
{
    // ѭ��������ʼ��
    int i,j;
    sortcount++;//��ʼ���ѵ�ʱ����һ�αȽ�
    for (i = n / 2; i >= 0; i--)
    {
        HeapAdjust(list, i, n - 1);
    }
    // ����n-1��ѭ�����������

    for (j = n - 1; j > 0; j--)
    {
        // ���һ��Ԫ�غ͵�һԪ�ؽ��н���
        swap(&list[j], &list[0]);

        // ɸѡ R[0] ��㣬�õ�i-1�����Ķ�
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


