#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10000

typedef struct heapnode {
    int val;
    int count;
    int first_idx;
} heapnode;

typedef struct maxHeap {
    int size;
    heapnode array[MAX_SIZE];
} maxHeap;

heapnode newHeapNode(int val, int count, int idx) {
    heapnode hn={(val), (count), (idx)};
    return hn;
}

maxHeap createMaxHeap(int capacity) {
    maxHeap maxHeap;
    maxHeap.size = 0;
    return maxHeap;
}

void swap(heapnode *a, heapnode *b) {
    heapnode temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(maxHeap heap, int idx){
    int left, right, largest;
    left = (idx << 1) + 1;
    right = (idx + 1) << 1;

    if(left < heap.size &&
        heap.array[left].count > heap.array[idx].count)
        largest = left;
    else
        largest = idx;
    if(right < heap.size &&
        heap.array[right].count > heap.array[largest].count)
        largest = right;

    if(largest != idx) {
        swap(&heap.array[largest], &heap.array[idx]);
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(maxHeap heap) {
    int i, lastElement = heap.size - 1;
    for (i = (lastElement - 1 ) / 2; i >= 0; --i)
        maxHeapify(heap, i);
}

void printTopK(int **arr, int *n, int k, int numArrays) {
    maxHeap hp = createMaxHeap(numArrays);
    int i;
    for(i = 0; i < numArrays; i++) {
        if(n[i] != 0) {
            hp.array[hp.size] = newHeapNode(arr[i][0], 0, i);
            ++hp.size;
        }
    }

    buildMaxHeap(hp);

    int count = 0;
    while(count < k) {
        heapnode root = hp.array[0];
        printf("%d ", root.val);

        int l = root.first_idx;
        int i = root.count + 1;

        if(i < n[l])
            hp.array[0] = newHeapNode(arr[l][i], i, l);
        else {
            swap(&hp.array[0], &hp.array[hp.size - 1]);
            --hp.size;
            --hp.array[0];
        }

        maxHeapify(hp, 0);

        ++count;
    }
}

int main(){
    int arr[][5]={ {1,2,3,4,5}, 
                   {2,4,5}, 
                   {1,2,3,4,5}, 
                   {2,3,4,5} };

    int n[]={5,3,5,4};

    int k = 3;   
    int numArrays = sizeof(arr)/sizeof(arr[0]);

    printTopK(arr, n, k, numArrays);

    return 0;
}