#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    FILE *fp;
    int i;
    
    // Open the file in write mode
    fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Write headers
    // fprintf(fp, "x\ty\terr_x\terr_y\n");

    // Write 100 data points to the file
    for (i = 0; i < 100; i++) {
        // Generate random x, y, error_x, and error_y
        double x = i;
        double y = sin(x);

        // Write the data points to the file
        fprintf(fp, "%f %f\n", x, y);
    }

    // Close the file
    fclose(fp);

    printf("Data has been written to data.txt.\n");

    return 0;
}
