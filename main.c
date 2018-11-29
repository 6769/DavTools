#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"





static Options moption;



int main(int argc, char *argv[]) {

    argparse(&moption,argc, argv);
    return 0;
}