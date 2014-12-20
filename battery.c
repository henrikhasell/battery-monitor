#include <stdlib.h>
#include <stdio.h>

#define DIRECTORY "/sys/class/power_supply/"
#define DEVICE "BAT0/"

int main(int argc, char *argv[])
{
    FILE *file = NULL;

    float full;
    float curr;

    /* Fetch full capacity from the system. */
    file = fopen(DIRECTORY DEVICE "charge_full", "r");
    fscanf(file, "%f", &full); fclose(file);

	/* Fetch curr capacity from the system. */
    file = fopen(DIRECTORY DEVICE "charge_now", "r");
    fscanf(file, "%f", &curr); fclose(file);
    
    return EXIT_SUCCESS;
}
