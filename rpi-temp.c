/**
 * Small utility to get the internal temperature on a RaspberryPi
 *
 * The tool is compatible and tested on RaspberryPi models:
 *     - RaspberryPi B
 *     - RaspberryPi 2 B
 *     - RaspberryPi 3 B
 *
 *
 * Author: Martin Albrecht
 *
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 Martin Albrecht <martin.albrecht@javacoffee.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/* Path to the file to read the temperature from */
#define RPI_TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"


/* Global option flags */
unsigned char opt_raw = 0;


/* Usage function*/
void usage(char **argv) {
    printf("usage: %s <option>\n\n", argv[0]);
    printf("Options:\n\t-r Get raw temperature\n\n");
}


/* Handle command line options */
void get_options(int argc, char **argv) {
    int c;

    while( (c=getopt(argc, argv, "rh")) != -1 ) {
        switch(c) {
            case 'r':
                opt_raw = 1;
                break;

            case 'h':
                usage(argv);
                exit(0);

            case '?':
                exit(1);

            default:
                break;        
        }
    }
} 


/* Fetch the temperature */
float get_temperature() {
    FILE *fd;
    float temp;

    fd = fopen(RPI_TEMP_PATH, "r");
    if( fd == NULL ) {
        fprintf(stderr, "Error: Could not open temperature file.\n");
        exit(1);
    }

    if( fscanf(fd, "%f", &temp) <= 0 ) {
        fprintf(stderr, "Warning: Could not read temperature file.\n");
    }
    fclose(fd);

    return (temp / 1000);
}



int main(int argc, char **argv) {
    get_options(argc, argv);

    if( opt_raw == 1 ) {
        printf("%.2f", get_temperature());
    
    } else {
        printf("Internal temperature: %.2f°C\n", get_temperature());
    }

    return 0;
}

