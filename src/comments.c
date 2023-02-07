#include "comments.h"
#include "common.h"

int fileSize(FILE* infile){

    fseek(infile, 0L, SEEK_END);

    //narrowing conversion, may not be a problem
    int size = ftell(infile);
    rewind(infile);

    return size;
}

char* removeCommentsFile(FILE *infile, char* buffer){
    // keep track of whether we are looking at a comment or not
    int lineComment = FALSE;
    int multilineComment = FALSE;
    int delayMultiline = FALSE;

    // keep track of special characters
    int backslash = FALSE;
    int star = FALSE;

    //int size = fileSize(infile);
    //char buffer[size + 1];

    // buffer index to rewrite file contents into. Will desync with file index for obvious reasons
    int bufferIdx = 0;

    // used for getline function
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, infile)) != -1) {
        // line comments are not preserved across lines
        lineComment = FALSE;

        // crawl over the line and update comment flags accordingly
        for (int lineIdx = 0; lineIdx < read; lineIdx++){
            char character = line[lineIdx];

            // backslash and star keep track of PREVIOUS character, set to false
            switch (character){
                case '*':
                    // first type of comment takes priority, therefore "// comment /* more comment\n" is not a multiline comment
                    // only need to set multiline and change buffer idx if not already in a multiline comment
                    if (backslash && !multilineComment && !lineComment) {
                        multilineComment = TRUE;

                        bufferIdx--;
                    }

                    backslash = FALSE;
                    star = TRUE;
                    break;

                case '/':
                    // if backslash and not already a comment, start a comment
                    if (backslash && !multilineComment && !lineComment){
                        lineComment = TRUE;

                        bufferIdx--;
                    }

                    //reordered to guard for closing multiline comments
                    // "*//" should only detect closing multiline comment, second backslash does not start line comment
                    backslash = TRUE;

                    if (star){
                        delayMultiline = TRUE;
                        backslash = FALSE;
                    }

                    star = FALSE;
                    break;

                default:
                    backslash = FALSE;
                    star = FALSE;
                    break;

            }

            //store character if not in a comment section
            if (!(lineComment || multilineComment)){
                buffer[bufferIdx] = character;
                bufferIdx++;
            }

            // deactivating multiline flag must be done after storing character to avoid writing an extra '/'
            if (delayMultiline){
                multilineComment = FALSE;
                delayMultiline = FALSE;
            }

        }
        // last line character must be \n. If line ends with a comment, forcefully add to buffer
        if(lineComment || multilineComment){
            buffer[bufferIdx] = '\n';
            bufferIdx++;
        }
        /*
        printf("\033[94mRetrieved line of length %zu:\033[0m\n", read);
        printf("%s", buffer);
         */
    }
    // terminate buffer with null char
    buffer[bufferIdx] = '\0';
    //printf("\n\033[94m%s\033[0m", buffer);

    fclose(infile);

    return (buffer);
}

int removeComments(char* infilePath, char* outfilePath) {
    FILE *infile = fopen(infilePath, "r");

    if (!infile){
        fprintf(stdout, "%s%s%s%s", FMT(BOLD, ITALICS, RED_BG, REVERSE), "ERROR: ", FMT(BLUE, DASH, WHITE_BG), "null file pointer\n");
        return -1;
    }
    // create a buffer to store infile without comments
    int size = fileSize(infile);
    // +1 for '\0'
    char buffer[size + 1];

    // if infile is NULL print/return an error, if not remove all comments from infile and put into buffer
    char* fileNoComments = removeCommentsFile(infile, buffer);
    FILE *outfile = fopen(outfilePath, "w+");
    fprintf(outfile, "%s", fileNoComments);
    fclose(outfile);
    return 0;
}



