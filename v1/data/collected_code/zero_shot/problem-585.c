#include <stdio.h>
#include <stdlib.h>

// Structure to represent item
typedef struct {
    int index;
    int price;
} Item;

// Function to swap two items
void swap(Item* a, Item* b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// Custom heapify function
void heapify(Item arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left].price > arr[largest].price)
        largest = left;

    if (right < size && arr[right].price > arr[largest].price)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, size, largest);
    }
}

// Function to find n expensive price items
void findExpensiveItems(Item arr[], int n, int size) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i >= size - n; i--) {
        printf("Item index: %d, Price: %d\n", arr[i].index, arr[i].price);
    }
}

// Test the function
int main() {
    int n, size;

    printf("Enter the number of items: ");
    scanf("%d", &size);

    printf("Enter the number of expensive items needed: ");
    scanf("%d", &n);

    Item* arr = (Item*)malloc(size * sizeof(Item));

    for (int i = 0; i < size; i++) {
        printf("Enter price for item %d: ", i + 1);
        scanf("%d", &arr[i].price);
        arr[i].index = i + 1;
    }

    findExpensiveItems(arr, n, size);

    free(arr);

    return 0;
}