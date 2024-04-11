#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tuple[100];
    int frequency;
} Tuple;

int find_tuple(Tuple *tuples, int count, char *tuple) {
    for (int i = 0; i < count; i++) {
        if (strcmp(tuples[i].tuple, tuple) == 0) {
            return i;
        }
    }
    return -1;
}

void assign_frequency(Tuple *tuples, char **tuple_list, int list_size) {
    int count = 0;
    for (int i = 0; i < list_size; i++) {
        int index = find_tuple(tuples, count, tuple_list[i]);
        if (index == -1) {
            strcpy(tuples[count].tuple, tuple_list[i]);
            tuples[count].frequency = 1;
            count++;
        } else {
            tuples[index].frequency++;
        }
    }
}

int main() {
    char *tuple_list[] = {"tuple1", "tuple2", "tuple1", "tuple3", "tuple2", "tuple2"};
    int list_size = sizeof(tuple_list) / sizeof(tuple_list[0]);

    Tuple *tuples = (Tuple *)malloc(list_size * sizeof(Tuple));
    assign_frequency(tuples, tuple_list, list_size);

    for (int i = 0; i < list_size; i++) {
        if (tuples[i].frequency != 0) {
            printf("%s: %d\n", tuples[i].tuple, tuples[i].frequency);
        }
    }

    free(tuples);
    return 0;
}