#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

void process_pairs(Pair *input, Pair *output, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (input[i].second == input[j].first) {
                output[i].first = input[i].first;
                output[i].second = input[j].second;
            }
        }
    }
}

int main() {
    int size = 5;
    Pair input[] = {{1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}};
    Pair output[size];

    process_pairs(input, output, size);

    for (int i = 0; i < size; ++i) {
        printf("%d %d\n", output[i].first, output[i].second);
    }

    return 0;
}