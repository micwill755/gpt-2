#include <stdint.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
    float *weight; 
    int vocab_size;
    int emb_dim;
    
    void (* init)(struct Embedding *self, int vocab_size, int emb_dim);
    float* (* forward)(struct Embedding *self, long *input_ids);
} Embedding;

void embedding_init(Embedding *self, int vocab_size, int emb_dim) { 
    self->vocab_size = vocab_size;
    self->emb_dim = emb_dim;

    // Allocate weight matrix (vocab_size x emb_dim)
    self->weight = (float*)malloc(vocab_size * emb_dim * sizeof(float));

    // Initialize with random values 
    for (int i = 0; i < vocab_size * emb_dim; i++) {
        self->weight[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f; // Random [-1, 1]
    }
}

float* embedding_forward(Embedding *self, int *input_ids, int num_tokens) {
    float *output = (float*)malloc(num_tokens * self->emb_dim * sizeof(float));
    
    for (int i = 0; i < num_tokens; i++) {
        int token_id = input_ids[i];
        // Copy embedding for this token
        for (int j = 0; j < self->emb_dim; j++) {
            output[i * self->emb_dim + j] = self->weight[token_id * self->emb_dim + j];
        }
    }
    
    return output;
}
