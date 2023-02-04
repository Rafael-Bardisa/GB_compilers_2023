//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#include "automata.h"

Automata create_automata(int num_states, char* accepted_chars){
    //know length of automata accepted characters for malloc
    int num_chars = strlen(accepted_chars);

    //initialize state matrix to 0 (i.e, all states point to not accepting state)
    int** states = calloc(num_states, sizeof (int*));
    for (int i = 0; i < num_states; i++){
        states[i] = calloc(num_chars, sizeof(int));
    }

    //local alphabet for automata allows it to reference cells independently of outside alphabet
    char* alphabet = calloc(num_chars, sizeof(char));
    strcpy(alphabet, accepted_chars);

    //create and return an automata
    Automata automata = {
            .state_matrix = states,
            .num_states = num_states,

            //TODO black magic
            .at = NULL,

            .current_state = 0,
            .alphabet = alphabet,
    };

    return automata;
}

void free_automata(Automata automata){
    //reverse process as create_automata, much faster because only need to free calloced memory
    free(automata.alphabet);
    for (int i = 0; i < automata.num_states; i++){
        free(automata.state_matrix[i]);
    }
    free(automata.state_matrix);
}


int save_automata(Automata automata, char* file_path){
    FILE *save_file = fopen(file_path, "w+");

    if (!save_file){
        dprintf(1, "%sERROR SAVING AUTOMATA: %snull file pointer\n", FMT(BOLD, RED), FMT(UNDERLINE_L));
        return -1;
    }

    int file_ref = fileno(save_file);

    int num_chars = strlen(automata.alphabet);

    dprintf(file_ref, "%i %s\n", automata.num_states, automata.alphabet);
    for(int i = 0; i < automata.num_states; i++){
        int first_char = TRUE;
        for(int j = 0; j < num_chars; j++){
            if (!first_char) dprintf(file_ref, " ");
            dprintf(file_ref, "%i", automata.state_matrix[i][j]);
            first_char = FALSE;
        }
        dprintf(file_ref, "\n");
    }

    fclose(save_file);
}

Automata load_automata(char* file_path){
    FILE *save_file = fopen(file_path, "r");

    if (!save_file){
        dprintf(1, "%sERROR LOADING AUTOMATA: %snull file pointer\n", FMT(BOLD, RED), FMT(UNDERLINE_L));
        // this should be null
        return (Automata){0};
    }

    int num_states;
    //preemptively allocate enough space for reading the buffer
    char alphabet[1024];
    fscanf(save_file, "%i %s", &num_states, alphabet);

    int num_chars = strlen(alphabet);
    Automata automata = create_automata(num_states, alphabet);

    for (int i = 0; i < num_states; i++){
        for (int j = 0; j < num_chars; j++){
            fscanf(save_file, "%i", &automata.state_matrix[i][j]);
        }
    }

    return automata;
}