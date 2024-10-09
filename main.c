#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

int eval_expression(int * numbers, int size) {
    int sum = 0;
    for (int i = 0; i < size ; i++) {
        sum += numbers[i];
    }
    return sum;
}

int build_number(char * str, bool negative) {
    int num = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        num = num * 10 + (str[i] - '0');
    }

    if (negative) {
        // printf("Current: %d Negative: %d\n", numbers[number_count], 0 - numbers[number_count]);
        num = 0 - num;
    }

    return num;
}

int main(void) {
    char scanned;
    char * separated_num = (char *) malloc(1 * sizeof(char));
    int num_cipher = 0;
    int number_count = 0;
    int * numbers = malloc(1 * sizeof(int));
    bool negative = false;

    while(scanned != '\n') {
        scanf("%c", &scanned);

        if ((int)scanned >= 48 && (int)scanned <= 57) {
            // printf("Number scanned: %d\n", (int)scanned - '0');
            char * temp_chars = realloc(separated_num, (num_cipher + 1) * sizeof(char));

            if (temp_chars == NULL) {
                printf("Memory reallocation failed\n");
                free(separated_num);
                exit(1);
            }

            separated_num = temp_chars;
            separated_num[num_cipher] = scanned;
            num_cipher++;

        } else {
            // Build number
            separated_num[num_cipher] = '\0';

            numbers[number_count] = build_number(separated_num, negative);

            num_cipher = 0;
            negative = false;
            number_count++;

            int * temp_nums = realloc(numbers, (number_count + 1) * sizeof(int));

            if (temp_nums == NULL) {
                printf("Memory reallocation failed\n");
                free(numbers);
                free(separated_num);
                exit(1);
            }

            numbers = temp_nums;

            free(separated_num);
            separated_num = (char *) malloc(1 * sizeof(char));

            if ((int) scanned == 45) {
                // -
                //printf("- found\n");
                negative = true;
            }
        }
    }

    printf("Result: %d\n", eval_expression(numbers, number_count));


    free(separated_num);
    free(numbers);
    return 0;
}
