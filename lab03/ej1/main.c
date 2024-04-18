#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc, char *argv[]) {
    char *result = NULL;
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    FILE *file = fopen(path, "r");

    if(file == NULL){
        printf("El archivo no existe\n");
        exit(EXIT_FAILURE);
    }

    unsigned int length = 0u;
    while(length < max_size && !feof(file)){
        int res fscanf(file, "%u -> *%c*\n", &indexes[length], &letters[length]);
        if(res != 2 ){
        printf("Error el formato no se cumple\n");
            exit(EXIT_FAILURE);
        }
        if (indexes[length] > max_size){
            printf("el indice de un caracter supera el max_size\n");
            exit(EXIT_FAILURE);
        }
            
        }
        
        length++;

    }
    fclose(file);
    return length;
    }

    void sort_letters(unsigned int indexes[], char letters[], unsigned int length, char sorted[]){
        for(unsigned int i = 0u; i < length; i++){
            if (indexes[i] >= length){
                printf("uno de los indices de los caracteres es mayor que la cantidad de caracteres\n");
                exit (EXIT_FAILURE);
            }
            sorted[indexes[i]] = letters[i];
        }
    }

int main(int argc, char *argv[]) {
    
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0u;

    char *path;
    path = parse_filepath(argc, argv);

    length = data_from_file(path, indexes, letters, MAX_SIZE);
    
    if(length == 0u){
        return EXIT_FAILURE;
    }

    sort_letters(indexes, letters, length, sorted);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

