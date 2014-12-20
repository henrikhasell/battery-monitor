#include <stdlib.h>
#include <stdio.h>

#define DIRECTORY "/sys/class/power_supply/"
#define DEVICE "BAT0/"

float read_file_as_float(char file[])
{
    float result;

    FILE *file = fopen(directory, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Failed to open file: %s", file);
        exit(EXIT_FAILURE);
    }

    if(fscanf(file, "%f", &result) < 1)
    {
        fprintf(stderr, "Failed to scan file: %s", file);
        exit(EXIT_FAILURE);
    }

    fclose(file);

    return result;
}

int calculate_percentage(float curr, float full)
{
    return (int)(curr / full * 100.0f + 0.5f);
}

int main(int argc, char *argv[])
{
    float full = read_file_as_float(DIRECTORY DEVICE "charge_full");
    float curr = read_file_as_float(DIRECTORY DEVICE "charge_now");
    printf("%i%%\n", calculate_percentage(curr, full));
    return EXIT_SUCCESS;
}
