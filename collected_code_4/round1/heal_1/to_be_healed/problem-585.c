#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int item;
    int price;
} Item;

void swap(Item *a, Item *b)
{
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Item arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left<n && arr[left].price>arr[largest].price)
        largest = left;

    if (right<n && arr[right].price>arr[largest].price)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(Item arr[], int n)
{
    int startIdx = (n / 2) - 1;

    for (int i = startIdx; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

Item *topNprices(Item dataset[], int n, int N)
{
    buildHeap(dataset, n);

    Item *topN = malloc(sizeof(Item) * N);

    for(int i=0; i<N; i++)
    {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'topN' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        topN[i] = dataset[0];
        dataset[0] = dataset[n - i - 1];
        heapify(dataset, n - i - 1, 0);
    }

    return topN;
}

void printTopN(Item *arr, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i].price);
    
    printf("\n");
}

int main()
{
    Item dataset[] = { {1, 10}, {2, 200}, {3, 300}, {4, 400}, {5, 500}};

    int n = sizeof(dataset) / sizeof(dataset[0]);

    int N = 3;

    Item *topN = topNprices(dataset, n, N);

    printTopN(topN, N);

    return 0;
}