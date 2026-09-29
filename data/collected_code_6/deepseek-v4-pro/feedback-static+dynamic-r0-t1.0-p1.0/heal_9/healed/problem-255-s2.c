#include <stdio.h>
#include <stdlib.h>

void generate_combinations(char **colours, int colour_count, int choose_count, char **current, int current_size, int start) {
    if (current_size == choose_count) {
        for (int i = 0; i < choose_count; i++) {
            printf("%s", current[i]);
            if (i < choose_count - 1) printf(" ");
        }
        printf("\n");
        return;
    }

    for (int i = start; i < colour_count; i++) {
        current[current_size] = colours[i];
        generate_combinations(colours, colour_count, choose_count, current, current_size + 1, i);
    }
}

int main(void) {
    char *colours[] = {"Red", "Green", "Blue"};
    int choose_count = 2;
    int colour_count = (int)(sizeof(colours) / sizeof(colours[0]));

    if (choose_count <= 0 || colour_count <= 0 || choose_count > colour_count) {
        fprintf(stderr, "Invalid parameters\n");
        return EXIT_FAILURE;
    }

    char **current = malloc((size_t)choose_count * sizeof(char *));
    if (current == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    generate_combinations(colours, colour_count, choose_count, current, 0, 0);

    free(current);
    return EXIT_SUCCESS;
}