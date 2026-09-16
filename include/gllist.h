#ifndef GLLIST_H
#define GLLIST_H

#include "glnode.h"

typedef struct glthread_t
{
    glthread_node_t *head;
    unsigned int offset;
    unsigned int count;
} glthread_t;

void glthread_init(glthread_t *lst, unsigned int offset);
void glthread_add(glthread_t *lst, glthread_node_t *new);
void glthread_del(glthread_t *lst, glthread_node_t *glnode);
int glthread_empty(glthread_t *lst);
unsigned int glthread_size(glthread_t *lst);

#endif /* GLLIST_H */
