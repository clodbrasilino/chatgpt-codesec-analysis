#include <stdio.h>
#include <stdlib.h>

void generate_combinations_recursive(char *colours, int num_colours, int choose, char *current, int index, int start) {
    if (index == choose) {
        for (int i = 0; i < choose; i++) {
            printf("%c ", current[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i < num_colours; i++) {
        current[index] = colours[i];
        generate_combinations_recursive(colours, num_colours, choose, current, index, i);
    }
}

void generate_combinations(char *colours, int num_colours, int choose) {
    if (choose <= 0 || num_colours <= 0 || colours == NULL) {
        return;
    }

    char *current = (char *)malloc(choose * sizeof(char));
    if (current == NULL) {
        return;
    }

    generate_combinations_recursive(colours, num_colours, choose, current, 0, 0);

    free(current);
}

int main(void) {
    char colours[] = {'R', 'G', 'B'};
    int num_colours = sizeof(colours) / sizeof(colours[0]);
    int choose = 2;

    generate_combinations(colours, num_colours, choose);

    return 0;
}