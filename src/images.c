/*
 * Copyright (c) 2019-2020 Jakub Kozłowicz
 * All rights reserved.
 */

#include "images.h"

int readImage(FILE *inputFile, t_image *image) {
    char buffer[BUFFER_SIZE]; // Auxiliary buffer for reading header and comments
    int character; // Auxiliary variable for reading comments
    int end = 0; // Variable needed to check if the end of data in the file has been encountered

    /* Check if the file is passed correctly */
    if (inputFile == NULL) {
        return (E_PASSING_FILE);
    }

    /* Check if first line of data is incorrect */
    if (fgets(buffer, BUFFER_SIZE, inputFile) == NULL) {
        end = 1;
    }

    /* Check if is there magic number - should be "P2"/"P3" */
    if ((buffer[0] != 'P') || (buffer[1] != '2' && buffer[1] != '3') || end) {
        return (E_INCORRECT_FILE);
    }

    /* Remember image type */
    image->magicNumber = buffer[1];

    /* Skip comments */
    do {
        if ((character = fgetc(inputFile)) == '#') {
            if (fgets(buffer, BUFFER_SIZE, inputFile) == NULL)
                end = 1;
        } else {
            ungetc(character, inputFile);
        }
    } while (character == '#' && !end);

    /* Load image size and number of grey colors */
    if (fscanf(inputFile, "%d %d %d", &image->xSize, &image->ySize, &image->colorScale) != 3) {
        return (E_INCORRECT_DIMENSIONS);
    }

    /* If it is PGM image */
    if (image->magicNumber == '2') {
        /* Allocate memory for pixels and check if it is correct */
        image->pixels = malloc(image->xSize * image->ySize * sizeof(int));
        if (image->pixels == NULL) {
            return (E_ALLOCATE_MEMORY);
        }

        /* Table of pixels */
        int (*pgmImage)[image->xSize];
        pgmImage = (int (*)[image->xSize]) image->pixels;

        /* Save all pixels */
        for (int i = 0; i < image->ySize; i++) {
            for (int j = 0; j < image->xSize; j++) {
                if (fscanf(inputFile, "%d", &(pgmImage[i][j])) != 1) {
                    return (E_LOADING_PIXELS);
                }
            }
        }
    }

    /* If it is PPM image */
    if (image->magicNumber == '3') {
        /* Allocate memory for red color and check if it is correct */
        image->r = malloc(image->xSize * image->ySize * sizeof(int));
        if (image->r == NULL) {
            return (E_ALLOCATE_MEMORY);
        }

        /* Table for red color */
        int (*r)[image->xSize];
        r = (int (*)[image->xSize]) image->r;

        /* Allocate memory for green color and check if it is correct */
        image->g = malloc(image->xSize * image->ySize * sizeof(int));
        if (image->g == NULL) {
            return (E_ALLOCATE_MEMORY);
        }

        /* Table for green color */
        int (*g)[image->xSize];
        g = (int (*)[image->xSize]) image->g;

        /* Allocate memory for blue color and check if it is correct */
        image->b = malloc(image->xSize * image->ySize * sizeof(int));
        if (image->b == NULL) {
            return (E_ALLOCATE_MEMORY);
        }

        /* Table for blue color */
        int (*b)[image->xSize];
        b = (int (*)[image->xSize]) image->b;

        /* Save all pixels */
        for (int i = 0; i < image->ySize; i++) {
            for (int j = 0; j < image->xSize; j++) {
                if (fscanf(inputFile, "%d %d %d", &(r[i][j]), &(g[i][j]), &(b[i][j])) != 3) {
                    return (E_LOADING_PIXELS);
                }
            }
        }
    }

    /* Loading successful, return number of pixels */
    return (image->ySize * image->xSize);
}

int saveImage(FILE *outputFile, t_image *image) {
    /* Check if the file is passed correctly */
    if (outputFile == NULL) {
        return (E_PASSING_FILE);
    }

    /* If it is PGM image */
    if (image->magicNumber == '2') {
        /* Table of pixels */
        int (*pgmImage)[image->xSize];
        pgmImage = (int (*)[image->xSize]) image->pixels;

        /* Save magic number, image dimensions and number of shades of grey */
        fprintf(outputFile, "P2\n");
        fprintf(outputFile, "%d %d\r%d\n", image->xSize, image->ySize, image->colorScale);

        /* Save all pixels to result file */
        for (int i = 0; i < image->ySize; i++) {
            for (int j = 0; j < image->xSize; j++) {
                fprintf(outputFile, "%d ", pgmImage[i][j]);
            }
            fprintf(outputFile, "\n");
        }
    }

    /* If it is PPM image */
    if (image->magicNumber == '3') {
        /* Table of red color */
        int (*r)[image->xSize];
        r = (int (*)[image->xSize]) image->r;

        /* Table of green color */
        int (*g)[image->xSize];
        g = (int (*)[image->xSize]) image->g;

        /* Table of blue color */
        int (*b)[image->xSize];
        b = (int (*)[image->xSize]) image->b;

        /* Save magic number, image dimensions and number of color scale */
        fprintf(outputFile, "P3\n");
        fprintf(outputFile, "%d %d\r%d\n", image->xSize, image->ySize, image->colorScale);

        /* Save all pixels to result file */
        for (int i = 0; i < image->ySize; i++) {
            for (int j = 0; j < image->xSize; j++) {
                fprintf(outputFile, "%d %d %d ", r[i][j], g[i][j], b[i][j]);
            }
            fprintf(outputFile, "\n");
        }
    }

    /* Saving successful, return number of pixels */
    return (image->ySize * image->xSize);
}

void display(char *filename) {
    char command[BUFFER_SIZE]; // Auxiliary buffer to construct command

    /* Construct system command */
    strcpy(command, "display ");
    strcat(command, filename);
    strcat(command, " &");

    /* Display this command */
    printf("%s\n", command);

    /* Execute the command */
    system(command);
}

int deallocatePGM(t_image *pgm) {
    /* Check if it is possible to free memory */
    if (pgm->pixels != NULL) {
        free(pgm->pixels);
        return (ALL_OK);
    } else {
        return (E_DEALLOCATE_MEMORY);
    }
}

int deallocatePPM(t_image *ppm) {
    /* Check if it is possible to free memory */
    if (ppm->r != NULL && ppm->g != NULL && ppm->b != NULL) {
        free(ppm->r);
        free(ppm->g);
        free(ppm->b);
        return (ALL_OK);
    } else {
        return (E_DEALLOCATE_MEMORY);
    }
}