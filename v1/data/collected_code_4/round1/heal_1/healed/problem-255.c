#include <stdio.h>
#include <stdlib.h>

#define COLOR_COUNT 3

const char* colors[COLOR_COUNT] = {"Red", "Green", "Blue"};

void print_combinations(int level, char* combinations, int color_count) {
    int i;

    if(level == 0) {
        printf("%s\n", combinations);
        return;
    }

    for(i = 0; i < COLOR_COUNT; ++i) {
        combinations[color_count - level] = '0' + i;
        combinations[color_count - level + 1] = '\0';
        print_combinations(level - 1, combinations, color_count);
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s <number of colors to select>\n", argv[0]);
        return 1;
    }

    int selection_count = atoi(argv[1]);

    if(selection_count <= 0) {
        printf("You must select at least one color.\n");
        return 1;
    }

    char combinations[selection_count + 1];

    print_combinations(selection_count, combinations, selection_count);

    return 0;
}