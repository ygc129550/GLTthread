#ifndef GLSTACK_H
#define GLSTACK_H

#include "glnode.h"

typedef struct glstack_t
{
    glue_node_t *top;
    unsigned int offset;
    unsigned int count;
} glstack_t;

void glstack_init(glstack_t *stk, unsigned int offset);
void glstack_push(glstack_t *stk, glue_node_t *node);
glue_node_t *glstack_pop(glstack_t *stk);
glue_node_t *glstack_peek(glstack_t *stk);
int glstack_empty(glstack_t *stk);
unsigned int glstack_size(glstack_t *stk);

#endif /* GLSTACK_H */
