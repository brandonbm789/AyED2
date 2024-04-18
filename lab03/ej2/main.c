/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "weather_utils.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load climate data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "<year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>\n\n"
           "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
           "The dimensions of the array are given by the macro tclimate.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
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

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of tclimate */
    WeatherTable array;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, filepath);

    /* show the ordered array in the screen */

    

    int minima_temp = min_temp_min(array);
    printf("\nla temperatura minima registrada entre 1980 y 2016 es %d\n\n", minima_temp);

    int output[YEARS];
    may_temp_max(array, output);
    for(unsigned int year = 1980; year <= 2016; year++){
        printf("la temperatura maxima del %u fue de %d\n", year, output[year - 1980]);
    }
    printf("\n");

    month_t meses[YEARS];
    may_prec_men(array, meses);
    char *month;
    for(unsigned int year = 1980; year <= 2016; year++){
        if(meses[year] == 0) month = "january";
        else if(meses[year] == 1) month = "february";
        else if(meses[year] == 2) month = "march";
        else if(meses[year] == 3) month = "april";
        else if(meses[year] == 4) month = "may";
        else if(meses[year] == 5) month = "june";
        else if(meses[year] == 6) month = "july";
        else if(meses[year] == 7) month = "august";
        else if(meses[year] == 8) month = "september";
        else if(meses[year] == 9) month = "october";
        else if(meses[year] == 10) month = "november";
        else month = "december";
        printf("el mes con la mayor cantidad de precipitaciones mensuales de %u fue %s\n", year, month);
    }



    return (EXIT_SUCCESS);
}
