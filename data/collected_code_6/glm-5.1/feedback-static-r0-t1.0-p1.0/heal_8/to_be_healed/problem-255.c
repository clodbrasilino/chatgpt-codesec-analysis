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

int main(int argc, char * const * const argv) {
    const char colors[] = {'R', 'G', 'B'};
    int num_colors = 3;
    int choose = 0;

    if (argc > 1) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            return EXIT_FAILURE;
        }
        choose = (int)val;
    } else {
        choose = 2;
    }

    if (choose < 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'choose==0' is not redundant
     */
    if (choose == 0) {
        return EXIT_SUCCESS;
    }

    /* Possible weaknesses found:
     *  Assignment 'buffer_size=(unsigned long)choose+1', assigned value is greater than 1
     */
    size_t buffer_size = (size_t)choose + 1;
    /* Possible weaknesses found:
     *  Condition 'buffer_size==1' is always false
     *  Condition 'buffer_size==1' is always false [knownConditionTrueFalse]
     */
    if (buffer_size == 1) {
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    generate_combinations(colors, num_colors, choose, buffer, 0);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}