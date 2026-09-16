#ifndef GLQUEUE_H
#define GLQUEUE_H

#include "glnode.h"

typedef struct glqueue_t
{
    glthread_node_t *head;
    glthread_node_t *tail;
    unsigned int offset;
    unsigned int count;
} glqueue_t;

void glqueue_init(glqueue_t *q, unsigned int offset);
void glqueue_enqueue(glqueue_t *q, glthread_node_t *node);
glthread_node_t *glqueue_dequeue(glqueue_t *q);
glthread_node_t *glqueue_front(glqueue_t *q);
int glqueue_empty(glqueue_t *q);
unsigned int glqueue_size(glqueue_t *q);

#endif /* GLQUEUE_H */
