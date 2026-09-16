#ifndef GLLIST_H
#define GLLIST_H

#include "glnode.h"

typedef struct gllist_t
{
    glue_node_t *head;
    unsigned int offset;
    unsigned int count;
} gllist_t;

void gllist_init(gllist_t *lst, unsigned int offset);
void gllist_add(gllist_t *lst, glue_node_t *new);
void gllist_del(gllist_t *lst, glue_node_t *glnode);
int gllist_empty(gllist_t *lst);
unsigned int gllist_size(gllist_t *lst);

#endif /* GLLIST_H */
