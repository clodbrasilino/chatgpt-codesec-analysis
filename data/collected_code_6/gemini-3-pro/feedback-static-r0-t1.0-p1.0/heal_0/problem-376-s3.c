#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int id;
    int value;
};

void replace_duplicates(struct Tuple* tuples, size_t size, int custom_value) {
    if (tuples == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuples[i].value == custom_value) {
            continue;
        }

        int is_duplicate = 0;
        for (size_t j = i + 1; j < size; j++) {
            if (tuples[i].value == tuples[j].value) {
                tuples[j].value = custom_value;
                is_duplicate = 1;
            }
        }

        if (is_duplicate) {
            tuples[i].value = custom_value;
        }
    }
}

int main(void) {
    size_t num_tuples = 6;
    struct Tuple* my_tuples = (struct Tuple*)malloc(num_tuples * sizeof(struct Tuple));
    
    if (my_tuples == NULL) {
        return 1;
    }

    my_tuples[0].id = 1; my_tuples[0].value = 10;
    my_tuples[1].id = 2; my_tuples[1].value = 20;
    my_tuples[2].id = 3; my_tuples[2].value = 10;
    my_tuples[3].id = 4; my_tuples[3].value = 30;
    my_tuples[4].id = 5; my_tuples[4].value = 20;
    my_tuples[5].id = 6; my_tuples[5].value = 40;

    int replacement_value = -1;

    replace_duplicates(my_tuples, num_tuples, replacement_value);

    for (size_t i = 0; i < num_tuples; i++) {
        printf("Tuple %d: %d\n", my_tuples[i].id, my_tuples[i].value);
    }

    free(my_tuples);
    my_tuples = NULL;

    return 0;
}