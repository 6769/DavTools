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

void usage(void) {
    puts(musage);
}

void argparse(Options *options, int argc, char *argv[]) {
    const char optstrings[] = "hl::c::s::i:q";

    int ch;
    int langcode;

    options->argc = argc;
    if(argc<=1){
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

void hexprint(char* buf, int cnt){

}

void decodebuffer(char *dest, char *src, int cnt);