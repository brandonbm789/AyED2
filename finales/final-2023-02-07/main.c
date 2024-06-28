#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "position.h"

int main()
{
    position_t pos = NULL;
    pos = position_absolute(3, 4, 6);
    unsigned int **array = position_board(pos);
    for(unsigned int i = 0u; i < 6; i++){
        for(unsigned int j = 0u; j < 6; j++){
            printf("[%u] ", array[i][j]);
        }
        printf("\n");
        free(array[i]);
    }
    printf("\n");
    free(array);
    list_t list = position_movements(pos);
    list_show(list);
    list = list_destroy(list);
    free(pos);


    return 0;
}