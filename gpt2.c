#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

int main(int argc, char *argv[]) {
    FILE *file = fopen("the-verdict.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char *vocab[1000];
    int vocab_size = 0;
    char line[1000];
    
    // Build vocab from file
    while (fgets(line, sizeof(line), file)) {
        char *word = strtok(line, " \n\t");
        while (word && vocab_size < 1000) {
            // Check if word already exists
            int exists = 0;
            for (int i = 0; i < vocab_size; i++) {
                if (strcmp(vocab[i], word) == 0) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                vocab[vocab_size] = malloc(strlen(word) + 1);
                strcpy(vocab[vocab_size], word);
                vocab_size++;
            }
            word = strtok(NULL, " \n\t");
        }
    }
    
    printf("Vocab size: %d\n", vocab_size);
    fclose(file);

    Tokenizer tokenizer;
    init_tokenizer(&tokenizer, vocab, vocab_size);
}