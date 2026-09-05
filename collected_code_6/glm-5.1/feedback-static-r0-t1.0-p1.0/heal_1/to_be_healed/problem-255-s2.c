#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_combinations(char **colors, int num_colors, int choose, char **current, int index) {
    if (index == choose) {
        for (int i = 0; i < choose; i++) {
            printf("%s ", current[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < num_colors; i++) {
        current[index] = colors[i];
        generate_combinations(colors, num_colors, choose, current, index + 1);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int choose = 2;
    if (argc == 2) {
        choose = atoi(argv[1]);
        if (choose <= 0) {
            return EXIT_FAILURE;
        }
    }

    char *colors[] = {"Red", "Green", "Blue"};
    int num_colors = 3;

    if ((size_t)choose > SIZE_MAX / sizeof(char *)) {
        return EXIT_FAILURE;
    }

    char **current = malloc((size_t)choose * sizeof(char *));
    if (current == NULL) {
        return EXIT_FAILURE;
    }

    generate_combinations(colors, num_colors, choose, current, 0);

    free(current);
    current = NULL;

    return EXIT_SUCCESS;
}