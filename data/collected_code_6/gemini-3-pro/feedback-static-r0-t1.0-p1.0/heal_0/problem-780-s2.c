#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

void find_combinations(Tuple* tuples, int num_tuples, int target_sum) {
    if (tuples == NULL || num_tuples <= 0) {
        return;
    }

    for (int i = 0; i < num_tuples; i++) {
        for (int j = i + 1; j < num_tuples; j++) {
            int current_sum = tuples[i].x + tuples[i].y + tuples[j].x + tuples[j].y;
            if (current_sum == target_sum) {
                printf("Combination found: (%d, %d) and (%d, %d)\n", tuples[i].x, tuples[i].y, tuples[j].x, tuples[j].y);
            }
        }
    }
}

int main() {
    int num_tuples = 4;
    Tuple* tuples = (Tuple*)malloc(num_tuples * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    tuples[0].x = 1; tuples[0].y = 2;
    tuples[1].x = 3; tuples[1].y = 4;
    tuples[2].x = 5; tuples[2].y = -2;
    tuples[3].x = 0; tuples[3].y = 7;

    int target_sum = 10;

    find_combinations(tuples, num_tuples, target_sum);

    free(tuples);
    tuples = NULL;

    return 0;
}