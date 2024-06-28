/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    
    unsigned int op;
    unsigned int selec;
    while(1){
        printf("elija una operacion\n");
        scanf("%u", &op);
        if(op > 7u || op < 1u){
            printf("operacion invalida\n");
        }else{
            if(op == 1u){
                
                printf("elegir:\n 1 para pintar el arbol en pre-order\n 2 para hacerlo en in-order \n 3 para hacerlo en post-order\n");
                scanf("%u", &selec);
                if(selec >= 1u && selec <=3){
                    if(selec == 1u){
                        abb_dump(tree, ABB_PRE_ORDER);
                        printf("\n");
                    }else if(selec == 2u){
                        abb_dump(tree, ABB_IN_ORDER);
                        printf("\n");
                    }else{
                        abb_dump(tree, ABB_POST_ORDER);
                        printf("\n");
                    }
                }else{
                    printf("orden invalido\n");
                }
                
            }else if(op == 2u){
                abb_elem e;
                printf("ingresar el elemento a agregar\n");
                scanf("%d", &e);
                tree = abb_add(tree, e);
            }else if(op == 3u){
                abb_elem kill;
                printf("indicar el elemento a eliminar\n");
                scanf("%d", &kill);
                abb_remove(tree, kill);
            }else if(op == 4u){
                abb_elem check;
                printf("indicar el elemento para ver si se encuentra en el arbol\n");
                scanf("%d", &check);
                if(abb_exists(tree, check)){
                    printf("el elemento %d si existe en el arbol\n", check);
                }else{
                    printf("el elemento %d no existe en el arbol\n", check);
                }
            }else if(op == 5u){
                printf("el arbol tiene longitud %u\n", abb_length(tree));
            }else if(op == 6u){
                if (!abb_is_empty(tree)) {
                    printf("\n");
                    printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                                   abb_min(tree),
                                                                   abb_max(tree));
                } else {
                    printf("\nÁrbol vacío\n");
                }
            }else{
                break;
            }
        }
    }
    tree = abb_destroy(tree);
    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
