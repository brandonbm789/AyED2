#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"

struct _position {
        unsigned int row;
        unsigned int column;
        unsigned int dimension;
};


position_t position_initial(unsigned int dimension)
{
        position_t pos = NULL;
        pos = malloc(sizeof(struct _position));
        pos->column = 0u;
        pos->row = 0u;
        pos->dimension = dimension;
        return pos;
}

position_t position_absolute(unsigned int row, unsigned int column,
                             unsigned int dimension)
{
        assert(row < dimension && column < dimension);
        position_t pos = NULL;
        pos = malloc(sizeof(struct _position));
        pos->column = column;
        pos->row = row;
        pos->dimension = dimension;
        return pos;
}

position_t position_left(position_t pos)
{
        if(pos->column > 0u){
                pos->column--;
        }else{
                pos->column = pos->dimension - 1;
        }
        return pos;
}

position_t position_right(position_t pos)
{
        if(pos->column < pos->dimension - 1){
                pos->column++;
        }else{
                pos->column = 0u;
        }
        return pos;
}

position_t position_down(position_t pos)
{
        if(pos->row < pos->dimension - 1){
                pos->row++;
        }else{
                pos->row = 0u;
        }
        return pos;
}

position_t position_up(position_t pos)
{
        if(pos->row > 0u){
                pos->row--;
        }else{
                pos->row = pos->dimension - 1;
        }
        return pos;
}

unsigned int position_row(position_t pos)
{
        return pos->row;
}

unsigned int position_column(position_t pos)
{
        return pos->column;
}

unsigned int **position_board(position_t pos)
{
        unsigned int **array = calloc(pos->dimension, sizeof(*array));
        for(unsigned int i = 0u; i < pos->dimension; i++){
                array[i] = calloc(pos->dimension, sizeof(unsigned int));
        }
        for(unsigned int i = 0u; i < pos->dimension; i++){
                for(unsigned int j = 0u; j < pos->dimension; j++){
                        array[i][j] = 0u;
                }
        }
        array[pos->row][pos->column] = 1u;
        return array;
}

list_t position_movements(position_t pos)
{
        list_t list = list_empty();
        if(pos->row > 0u || pos->column > 0u){
                if(pos->column > 0u){
                        for(unsigned int i = 0u; i < pos->column; i++){
                                list = list_append(list, RIGHT);
                        }
                        if(pos->row > 0u){
                                for(unsigned int j = 0u; j < pos->row; j++){
                                        list = list_append(list, DOWN);
                                }
                        }
                }else{
                        for(unsigned int j = 0u; j < pos->row; j++){
                                list = list_append(list, DOWN);
                        } 
                }
        }
        return list;
}

position_t position_destroy(position_t pos)
{
        free(pos);
        pos = NULL;
        return pos;
}
