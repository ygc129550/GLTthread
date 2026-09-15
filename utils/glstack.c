#include <stddef.h>
#include "glstack.h"

void glstack_init(glstack_t *stk, unsigned int offset)
{
    stk->top = NULL;
    stk->offset = offset;
    stk->count = 0;
}

void glstack_push(glstack_t *stk, glthread_node_t *node)
{
    node->left = NULL;
    node->right = stk->top;
    if (stk->top)
        stk->top->left = node;
    stk->top = node;
    stk->count++;
}

glthread_node_t *glstack_pop(glstack_t *stk)
{
    if (!stk->top) return NULL;
    glthread_node_t *node = stk->top;
    stk->top = node->right;
    if (stk->top)
        stk->top->left = NULL;
    node->left = NULL;
    node->right = NULL;
    stk->count--;
    return node;
}

glthread_node_t *glstack_peek(glstack_t *stk)
{
    return stk->top;
}

int glstack_empty(glstack_t *stk)
{
    return stk->top == NULL;
}

unsigned int glstack_size(glstack_t *stk)
{
    return stk->count;
}
