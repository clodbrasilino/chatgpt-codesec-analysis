#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void generate_combinations(const char *colors, int num_colors, int choose, char *buffer, int index) {
    if (index == choose) {
        buffer[index] = '\0';
        printf("%s\n", buffer);
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
int main(int argc, char * const argv[]) {
    const char colors[] = {'R', 'G', 'B'};
    int num_colors = 3;
    int choose = 0;

    if (argc > 1) {
        char *endptr;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        choose = (int)val;
    } else {
        choose = 2;
    }

    if (choose <= 0) {
        return choose < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    char *buffer = malloc(choose + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    generate_combinations(colors, num_colors, choose, buffer, 0);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}