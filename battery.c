#include <stdlib.h>
#include <stdio.h>

#define PATH "/sys/class/power_supply/BAT0/"

void read_float(char path[], float *result)
{ /* Attempt to open the file (path) for reading. */
    FILE *file = fopen(path, "r");

    if(file == NULL)
    { /* If file failed to open, print error and exit. */
        fprintf(stderr, "Failed to open file: %s", path);
        exit(EXIT_FAILURE);
    }

    if(fscanf(file, "%f", result) < 1)
    { /* If read failed, print error and exit. */
        fprintf(stderr, "Failed to scan file: %s", path);
        exit(EXIT_FAILURE);
    }

    fclose(file); /* Close file. */
}

int calculate_percentage(float curr, float full)
{ /* Calculate the (rounded) battery percentage. */
    return (int)(curr / full * 100.0f + 0.5f);
}

void print_percentage(int percentage)
{
    printf("%s%i%%\x1b[0m\n",
        percentage >= 70
            ? "\x1b[0;32m"
            : percentage >= 40
                ? "\x1b[0;35m"
                : "\x1b[5;31m",
        percentage
    );
}

int main(int argc, char *argv[])
{
    float curr;
    float full;

    read_float(PATH "charge_now", &curr);
    read_float(PATH "charge_full", &full);

    print_percentage(
        calculate_percentage(curr, full));

    return EXIT_SUCCESS;
}
