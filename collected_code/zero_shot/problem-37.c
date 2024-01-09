#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortMixedList(void* list[], int size) {
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (list[j] && list[j+1]) {
                if (strcmp((char*) list[j], (char*) list[j+1]) > 0) {
                    void* temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] = temp;
                }
            } else if (!list[j]) {
                void* temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

int main() {
    void* mixedList[] = { "10", "3", "Hello", NULL, "29", NULL, "20", "A", "B", NULL };
    int size = sizeof(mixedList)/sizeof(mixedList[0]);

    sortMixedList(mixedList, size);

    printf("Sorted Mixed List:\n");
    for (int i = 0; i < size; i++) {
        if (mixedList[i])
            printf("%s\n", (char*) mixedList[i]);
        else
            printf("NULL\n");
    }

    return 0;
}
