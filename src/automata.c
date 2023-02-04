//
// Created by Rafael Bardisa Rodes on 3/2/23.
//

#include "automata.h"

Automata create_automata(int num_states, char* accepted_chars){
    //know length of automata accepted characters for malloc
    int num_chars = strlen(accepted_chars) + 1;

    //initialize state matrix to 0 (i.e, all states point to not accepting state)
    int** states = calloc(num_states, sizeof (int*));
    for (int i = 0; i < num_states; i++){
        // extra column to specify wildcard characters (any character not specified as accepted)
        // can be used for literal matching
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

            .alphabet = alphabet,
            .num_chars = num_chars,

            .current_state = 0,
    };

    return automata;
}

void free_automata(Automata* automata){
    //reverse process as create_automata, much faster because only need to free calloced memory
    free(automata->alphabet);
    for (int i = 0; i < automata->num_states; i++){
        free(automata->state_matrix[i]);
    }
    free(automata->state_matrix);
}


int save_automata(Automata* automata, char* file_path){
    FILE *save_file = fopen(file_path, "w+");

    if (!save_file){
        dprintf(1, "%sERROR SAVING AUTOMATA: %snull file pointer\n", FMT(BOLD, RED), FMT(UNDERLINE_L));
        return -1;
    }

    int file_ref = fileno(save_file);

    dprintf(file_ref, "%i %s\n", automata->num_states, automata->alphabet);
    for(int i = 0; i < automata->num_states; i++){
        int first_char = TRUE;
        for(int j = 0; j < automata->num_chars; j++){
            if (!first_char) dprintf(file_ref, " ");
            dprintf(file_ref, "%i", automata->state_matrix[i][j]);
            first_char = FALSE;
        }
        dprintf(file_ref, "\n");
    }

    fclose(save_file);
    return 0;
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

    Automata automata = create_automata(num_states, alphabet);

    for (int i = 0; i < automata.num_states; i++){
        for (int j = 0; j < automata.num_chars; j++){
            fscanf(save_file, "%i", &automata.state_matrix[i][j]);
        }
    }

    return automata;
}

void start_automata(Automata* automata){
    automata->current_state = 1;
}

int index_of(Automata* automata, char letter){
    // crawl over the automata alphabet and return the index if letter matches
    for(int i = 0; i < automata->num_chars - 1; i++){
        if(automata->alphabet[i] == letter) return i;
    }
    // letter is not in the alphabet, return wildcard column
    return automata->num_chars - 1;
}

int advance(Automata* automata, char letter){
    int letter_idx = index_of(automata, letter);
    automata->current_state = automata->state_matrix[automata->current_state][letter_idx];

    return automata->current_state;
}