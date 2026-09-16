#include <stddef.h>
#include "gllist.h"

void glthread_init(glthread_t *lst, unsigned int offset)
{
    lst->head = NULL;
    lst->offset = offset;
    lst->count = 0;
}

void glthread_add(glthread_t *lst, glthread_node_t *new)
{
    if (lst->head) lst->head->left = new;
    new->right = lst->head;
    lst->head = new;
    lst->count++;
}

void glthread_del(glthread_t *lst, glthread_node_t *glnode)
{
    if (!glnode) return;
    if (glnode->left)
    {
        ((glthread_node_t *)glnode->left)->right = glnode->right;
    }
    else
    {
        lst->head = glnode->right;
    }
    if (glnode->right)
    {
        ((glthread_node_t *)glnode->right)->left = glnode->left;
    }
    glnode->left = NULL;
    glnode->right = NULL;
    lst->count--;
}

int glthread_empty(glthread_t *lst)
{
    return lst->head == NULL;
}

unsigned int glthread_size(glthread_t *lst)
{
    return lst->count;
}
