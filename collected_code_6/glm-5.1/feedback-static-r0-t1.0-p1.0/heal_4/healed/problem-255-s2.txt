#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void generate_combinations(const char **colors, int num_colors, int choose, const char **current, int index) {
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

int main(int argc, char const * const argv[]) {
    int choose = 2;
    if (argc == 2) {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        choose = (int)val;
    }

    const char *colors[] = {"Red", "Green", "Blue"};
    int num_colors = 3;

    if ((size_t)choose > SIZE_MAX / sizeof(const char *)) {
        return EXIT_FAILURE;
    }

    const char **current = malloc((size_t)choose * sizeof(const char *));
    if (current == NULL) {
        return EXIT_FAILURE;
    }

    generate_combinations(colors, num_colors, choose, current, 0);

    free(current);

    return EXIT_SUCCESS;
}