#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

struct element {
    int value;
    int count;
};

struct element frequency[MAX];
int freq_index = 0;

void init_frequency() {
    for (int i = 0; i < MAX; i++) {
        frequency[i].value = 0;
        frequency[i].count = 0;
    }
}

void add_frequency(int value) {
    for (int i = 0; i < freq_index; i++) {
        if (frequency[i].value == value) {
            frequency[i].count++;
            return;
        }
    }
    frequency[freq_index].value = value;
    frequency[freq_index].count++;
    freq_index++;
}

void get_frequency(int **array, int row, int column) {
    init_frequency();
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            add_frequency(array[i][j]);
        }
    }
}

void print_frequency() {
    for(int i = 0; i < freq_index; i++) {
        printf("%d: %d \n", frequency[i].value, frequency[i].count);
    }
}

int main() {
    int row = 3, column = 3;
    int **array = (int **)malloc(row * sizeof(int *));
    for (int i=0; i<row; i++) {
         /* Possible weaknesses found:
          *  dereference of possibly-NULL 'array' [CWE-690] [-Wanalyzer-possible-null-dereference]
          */
         array[i] = (int *)malloc(column * sizeof(int));
    }

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) {
            scanf("%d", &array[i][j]);
        }
    }

    get_frequency(array, row, column);
    print_frequency();

    for (int i=0; i<row; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}