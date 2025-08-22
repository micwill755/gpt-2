
#include "embedding.h"

typedef struct {
    int vocab_size;
    int context_length;
    int emb_dim;
    int n_heads;
    int n_layers;
    float drop_rate;
    bool qkv_bias;
} GPTConfig;

typedef struct {
    int emb_dim;
    Embedding tok_embeds;
    
    // Method pointers
    void (*init)(struct GPTModel *self);
    int (*forward)(struct GPTModel *self, char *text, int *tokens, int in_idx);
} GPTModel;

void GPTModel_init(GPTModel *self, GPTConfig *config) {
    self->tok_embeds.vocab_size = config->vocab_size;
}