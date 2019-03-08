//
// Created by 6769 on 2018/11/29.
//

#ifndef CLIONTOOLS_UTILS_H
#define CLIONTOOLS_UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define LINECNT 16
typedef char* pchar;
typedef struct _globalopt {
    int argc,lang;
    pchar outputdir, inputfile, outputsrcdir;
    bool quiet, split, create;

} Options;

void argparse(Options* options ,int argc, char *argv[]);
void decodebuffer(char *dest, char *src, int cnt);
void hexprint(const char* buf, int cnt,FILE* output);

#endif //CLIONTOOLS_UTILS_H
