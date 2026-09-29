#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int heap[], int size, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != index)
    {
        swap(&heap[index], &heap[smallest]);
        min_heapify(heap, size, smallest);
    }
}

void max_heapify(int heap[], int size, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;

    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != index)
    {
        swap(&heap[index], &heap[largest]);
        max_heapify(heap, size, largest);
    }
}

void build_min_heap(int heap[], int size)
{
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
        min_heapify(heap, size, i);
}

void build_max_heap(int heap[], int size)
{
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
        max_heapify(heap, size, i);
}

int extract_min(int heap[], int *size)
{
    int min_val;
    
    if (*size <= 0)
        return INT_MIN;
    
    min_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    min_heapify(heap, *size, 0);
    
    return min_val;
}

int extract_max(int heap[], int *size)
{
    int max_val;
    
    if (*size <= 0)
        return INT_MAX;
    
    max_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    max_heapify(heap, *size, 0);
    
    return max_val;
}

void insert_min_heap(int heap[], int *size, int capacity, int value)
{
    int i;
    
    if (*size >= capacity)
        return;
    
    (*size)++;
    i = *size - 1;
    heap[i] = value;
    
    while (i > 0 && heap[(i - 1) / 2] > heap[i])
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insert_max_heap(int heap[], int *size, int capacity, int value)
{
    int i;
    
    if (*size >= capacity)
        return;
    
    (*size)++;
    i = *size - 1;
    heap[i] = value;
    
    while (i > 0 && heap[(i - 1) / 2] < heap[i])
    {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
long long maximum_product_three(int arr[], int n)
{
    int *max_heap;
    int *min_heap;
    int max_heap_size = 0;
    int min_heap_size = 0;
    int i;
    long long max1, max2, max3;
    long long min1, min2;
    long long product1, product2;
    
    if (arr == NULL || n < 3)
        return 0;
    
    max_heap = (int *)malloc(3 * sizeof(int));
    min_heap = (int *)malloc(2 * sizeof(int));
    
    if (max_heap == NULL || min_heap == NULL)
    {
        free(max_heap);
        free(min_heap);
        return 0;
    }
    
    for (i = 0; i < n; i++)
    {
        if (max_heap_size < 3)
        {
            insert_min_heap(max_heap, &max_heap_size, 3, arr[i]);
        }
        else if (arr[i] > max_heap[0])
        {
            extract_min(max_heap, &max_heap_size);
            insert_min_heap(max_heap, &max_heap_size, 3, arr[i]);
        }
        
        if (min_heap_size < 2)
        {
            insert_max_heap(min_heap, &min_heap_size, 2, arr[i]);
        }
        else if (arr[i] < min_heap[0])
        {
            extract_max(min_heap, &min_heap_size);
            insert_max_heap(min_heap, &min_heap_size, 2, arr[i]);
        }
    }
    
    max1 = extract_min(max_heap, &max_heap_size);
    max2 = extract_min(max_heap, &max_heap_size);
    max3 = extract_min(max_heap, &max_heap_size);
    
    min1 = extract_max(min_heap, &min_heap_size);
    min2 = extract_max(min_heap, &min_heap_size);
    
    product1 = max1 * max2 * max3;
    product2 = min1 * min2 * max3;
    
    free(max_heap);
    free(min_heap);
    
    return (product1 > product2) ? product1 : product2;
}

int main(void)
{
    int arr1[] = {1, 10, 2, 6, 5, 3};
    int arr2[] = {-10, -10, 5, 2};
    int arr3[] = {-5, -4, -3, -2, -1};
    int n1, n2, n3;
    long long result;
    
    n1 = sizeof(arr1) / sizeof(arr1[0]);
    n2 = sizeof(arr2) / sizeof(arr2[0]);
    n3 = sizeof(arr3) / sizeof(arr3[0]);
    
    result = maximum_product_three(arr1, n1);
    printf("Array 1: Maximum product of three numbers = %lld\n", result);
    
    result = maximum_product_three(arr2, n2);
    printf("Array 2: Maximum product of three numbers = %lld\n", result);
    
    result = maximum_product_three(arr3, n3);
    printf("Array 3: Maximum product of three numbers = %lld\n", result);
    
    return 0;
}