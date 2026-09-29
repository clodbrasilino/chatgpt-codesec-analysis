#include <stdio.h>
#include <stdlib.h>

void generate_combinations(char *colors, int num_colors, int choose, char *buffer, int index) {
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

int main(int argc, char *argv[]) {
    char colors[] = {'R', 'G', 'B'};
    int num_colors = 3;
    /* Possible weaknesses found:
     *  Assignment 'choose=2', assigned value is 2
     */
    int choose = 2;

    /* Possible weaknesses found:
     *  Condition 'choose<=0' is always false
     *  Condition 'choose<=0' is always false [knownConditionTrueFalse]
     */
    if (choose <= 0) {
        if (choose == 0) {
            printf("\n");
        }
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