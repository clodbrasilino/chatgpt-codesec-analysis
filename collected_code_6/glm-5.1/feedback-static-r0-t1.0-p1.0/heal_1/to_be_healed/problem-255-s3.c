#include <stdio.h>
#include <stdlib.h>

void generate_combinations(char *colors, int num_colors, int choose, char *buffer, int index) {
    if (index == choose) {
        for (int i = 0; i < choose; i++) {
            printf("%c ", buffer[i]);
        }
        printf("\n");
        return;
    }
    for (int i = 0; i < num_colors; i++) {
        buffer[index] = colors[i];
        generate_combinations(colors, num_colors, choose, buffer, index + 1);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_to_choose>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long choose_long = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || choose_long <= 0 || choose_long > 100) {
        fprintf(stderr, "Error: Invalid number of colors to choose. Must be a positive integer <= 100.\n");
        return EXIT_FAILURE;
    }
    int choose = (int)choose_long;
    char colors[] = {'R', 'G', 'B'};
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    char *buffer = (char *)malloc(choose * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    generate_combinations(colors, num_colors, choose, buffer, 0);
    free(buffer);
    return EXIT_SUCCESS;
}