//
// Created by 6769 on 2018/11/29.
//

#include "utils.h"

static const char musage[] = "H-I-K Firmware header converter 0.51R\n\nUsage:\n"
                             "Position Arg: -i <input file>\n\n"
                             "Optional Arg: -q             :quiet on stdout\n"
                             "              -s<outputdirs> :extract files from firmware to destdir\n"
                             "              -l<1/2>        :set fimware language to X, where 1 - english or multi, 2 - chinese\n"
                             "              -c<outputdirs> :create new firmware with rootfs that included all files in sourcedir and  device properties copied from davfile\n\n"
                             "Example:\n> tools -i firmware.dav -l1 -ctestdir -ssplitdir\n"
                             "Compiled: "__TIMESTAMP__", GCC version: "__VERSION__;
static const unsigned char ida_chars[] =
        {
                0xBA, 0xCD, 0xBC, 0xFE, 0xD6, 0xCA, 0xDD, 0xD3, 0xBA, 0xB9,
                0xA3, 0xAB, 0xBF, 0xCB, 0xB5, 0xBE, 0xFF, 0xFF, 0xFF, 0xFF
        };

void usage(void) {
    puts(musage);
}

void argparse(Options *options, int argc, char *argv[]) {
    const char optstrings[] = "hl::c::s::i:q";

    int ch;
    int langcode;

    options->argc = argc;
    if (argc <= 1) {
        usage();
        exit(1);
    }
    while ((ch = getopt(argc, argv, optstrings)) != -1) {
        switch (ch) {
            case 'q':
                //stdout quite;
                options->quiet = true;
                break;
            case 's':
                //split files;
                options->split = true;
                options->outputdir = optarg;
                break;
            case 'c':
                //split files;
                options->create = true;
                options->outputsrcdir = optarg;
                break;

            case 'i':
                options->inputfile = optarg;
                break;

            case 'l':
                langcode = atoi(optarg);
                if (langcode != 1 && langcode != 2) {
                    printf("Unkown Langs: [%d]\n\n", langcode);
                    usage();
                    exit(1);
                } else {
                    options->lang = langcode;
                }
                break;
            case '?':
                printf("Unknown option: %c\n", (char) optopt);
                usage();
                exit(1);
            case 'h':
                usage();
                exit(1);
            default:
                break;
        }
    }

}

void hexprint(const char *buf, int cnt, FILE *output) {

    if (cnt < 1) {
        return;
    }
    int line = cnt / LINECNT + 1;


    putc('\n', output);
    for (int linei = 0; linei < line; linei++) {
        int currentchars = linei == line - 1 ? cnt % LINECNT : LINECNT;
        fprintf(output, "[%08X]: ", linei);
        for (int pos = 0; pos < currentchars; ++pos) {
            unsigned char curc = buf[pos + LINECNT * linei];
            fprintf(output, "%02X ", curc);
        }
        for (int pos = 0; pos < LINECNT - currentchars; ++pos) {
            fprintf(output, "   ");
        }
        fprintf(output, " | ");
        for (int pos = 0; pos < currentchars; ++pos) {
            unsigned char curc = buf[pos + LINECNT * linei];
            if (curc >= 32 && curc <= 127)
                fprintf(output, "%c", curc);
            else
                fprintf(output, ".");
        }
        for (int pos = 0; pos < LINECNT - currentchars; ++pos) {
            fprintf(output, " ");
        }
        fprintf(output, "|\n");
        if (linei + 2 == line && cnt % LINECNT == 0) {
            break;
        }
    }
}

void decodebuffer(char *dest, char *src, int cnt) {
    unsigned char i = 0;
    char key[32];

    memcpy(key, ida_chars, 16u);
    if (cnt > 0) {
        do {
            dest[i] = src[i] ^ key[(i + (i >> 4)) & 0xF];
            ++i;
        } while (i != cnt);
    }
}

int argcheck(const Options *options){
    char* targetfile=options->inputfile;
    if(!fopen(targetfile,"rb")){
        return false;
    }
    return true;


}

int split_files(const char* file){

    return true;
}