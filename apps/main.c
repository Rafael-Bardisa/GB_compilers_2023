//
// Created by Rafael Bardisa Rodes on 31/1/23.
//

#include "main.h"


#define FOR(i, a, b) for (int (i) = (int)(a); (i) < (int)(b); ++(i))


int main(){
    Token b = {.lexeme = "hola", .category = CAT_LITERAL};
    Token a[5];
    a[0] = b;

    //printf and dprintf have different priority (how)
/*
    foreach(Token* item in a){
        *item = b;
        TKPRINT(item);
    }*/

    //printf("format 0:%s", FMT(RED, BLUE));

/*
    foreach(Token* item in a){
        *item = b;
        TKPRINT(item);
    }
    */


    //dprintf(1, "%shello\n", FMT(RED, BOLD, STRIKETHROUGH, UNDERLINE_L));
    //printf("%sHello!\n", FMT(RED, BOLD, UNDERLINE_H, STRIKETHROUGH, REVERSE));
    //dprintf(1, "%sHello, %sWorld!\n", FMT(RED, BOLD), FMT(YELLOW));
    //dprintf(1, "%sHello there", FMT(BLUE, BOLD, DASH));
    //removeComments("/resources/tokens.c", "resources/tokens.c");
    //printf("%s\n%s\n\n%s\n", FMT(RED_BG), FMT(YELLOW_BG_B), FMT(RED_BG));
    /*
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           FMT(YELLOW_BG_B),
           FMT(RED_BG),
           FMT(YELLOW_BG_B),
           FMT(RED_BG),
           FMT(YELLOW_BG_B),
           FMT(RED_BG),
           FMT(YELLOW_BG_B),
           FMT(RED_BG),
           FMT(YELLOW_BG_B));
           */

    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(YELLOW_BG_B));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(RED_BG));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(YELLOW_BG_B));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(RED_BG));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(YELLOW_BG_B));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(RED_BG));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(YELLOW_BG_B));
    printf("%s\t\t\t\t%s\n", FMT(BLUE_BG), FMT(RED_BG));
    printf("%s\t\t\t\t%s\n\n", FMT(BLUE_BG), FMT(YELLOW_BG_B));


    //printf("%sHello, %sWorld!\n", FMT(WHITE), FMT(BLUE, UNDERLINE_L));
    //printf("\n");


}