//
// Created by Rafael Bardisa Rodes on 30/1/23.
//


#ifndef COMPILERS_COMMENTS_H
#define COMPILERS_COMMENTS_H

#include "common.h"

#define TRUE 1
#define FALSE 0

/**
 * Given a file, return the length of the file in characters.
 * Resets the file position indicator back to the start of the file!
 * @param infile pointer to the file to calculate the length of
 * @return the length of the file in characters
 * TODO error checking
 */
int fileSize(FILE* infile);

/**
 * Removes all comments from infile and stores the result in outfile. Closes infile upon completion
 * Assumes file pointers are valid.
 * Helper function for removeComments
 * @param infile pointer to the file to delete comments from. Assumes file position indicator is at the start of the file
 * @param buffer a char* buffer of at least size(infile) + 1 to store the uncommented version of the file, taking '\0' into account
 */
char* removeCommentsFile(FILE* infile, char* buffer);

/**
 * Removes all comments found in infilePath and stores the result in outfilePath.
 * @param infilePath the file to open and remove comments from.
 * @param outfilePath the path to save the contents of infile path minus the comments to
 */
int removeComments(char* infilePath, char*outfilePath);
#endif //COMPILERS_COMMENTS_H

