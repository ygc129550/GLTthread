#include <stddef.h>
#include "glqueue.h"

void glqueue_init(glqueue_t *q, unsigned int offset)
{
    q->head = NULL;
    q->tail = NULL;
    q->offset = offset;
    q->count = 0;
}

void glqueue_enqueue(glqueue_t *q, glthread_node_t *node)
{
    node->right = NULL;
    node->left = q->tail;
    if (q->tail)
        q->tail->right = node;
    else
        q->head = node;
    q->tail = node;
    q->count++;
}

glthread_node_t *glqueue_dequeue(glqueue_t *q)
{
    if (!q->head) return NULL;
    glthread_node_t *node = q->head;
    q->head = node->right;
    if (q->head)
        q->head->left = NULL;
    else
        q->tail = NULL;
    node->left = NULL;
    node->right = NULL;
    q->count--;
    return node;
}

glthread_node_t *glqueue_front(glqueue_t *q)
{
    return q->head;
}

int glqueue_empty(glqueue_t *q)
{
    return q->head == NULL;
}

unsigned int glqueue_size(glqueue_t *q)
{
    return q->count;
}
