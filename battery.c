#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PATH "/sys/class/power_supply/BAT0/"

bool newline = true;
bool colour = true;

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
    if(colour == true)
    {
        printf("%s%i%%\x1b[0m",
            percentage >= 70
                ? "\x1b[0;32m"
                : percentage >= 40
                    ? "\x1b[0;35m"
                    : "\x1b[5;31m",
            percentage
        );
    }
    else
    {
        printf("%i%%", percentage);
    }

    if(newline == true)
    {
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    float curr;
    float full;

    for(int i = 0; i < argc; i++)
    {/* Arguments passed to the
    program will be parsed here. */
        if(strcmp(argv[i], "-n") == 0)
        {/* Set the newline boolean. */
            newline = false;
            continue;
        }
        if(strcmp(argv[i], "-b") == 0)
        {/* Set the colour boolean. */
            colour = false;
            continue;
        }
    }

    read_float(PATH "charge_now", &curr);
    read_float(PATH "charge_full", &full);

    print_percentage(
        calculate_percentage(curr, full));

    return EXIT_SUCCESS;
}
