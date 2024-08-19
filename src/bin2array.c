#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>

#define NUMBERS_PER_LINE    20

void usage(char **argv) {
    fprintf(stderr, "Usage: %s INPUT OUTPUT\n\
Prints the content of INPUT to stdout as a C array of 8 bits values.\n", basename(argv[0]));
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage(argv);
    }

    char *input = argv[1];
    struct stat st;

    if (stat(input, &st) != 0) {
        fprintf(stderr, "Failed stat'ing \"%s\"!\n", input);
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen(input, "r");
    if (!f) {
        fprintf(stderr, "Failed opening \"%s\"!\n", input);
        exit(EXIT_FAILURE);
    }

    uint8_t buf[1024];
    int bytes_read;
    int total_bytes = 0;

    printf("uint8_t t[%ld] = {\n    ", st.st_size);

    do {
        bytes_read = fread(buf, 1, sizeof(buf), f);
        for (int i = 0; i < bytes_read; i++) {
            printf("0x%2.2x,", buf[i]);
            total_bytes++;
            if (total_bytes % NUMBERS_PER_LINE == 0) {
                printf("\n    ");
            }
        }
    } while (bytes_read > 0);
    printf("\n};\n");

    fclose(f);

    return EXIT_SUCCESS;
}
