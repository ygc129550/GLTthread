#include <stddef.h>
#include <stdio.h>
#include "glthread.h"

void glthread_add(glthread_t *lst, glthread_node_t *new)
{
    if (lst->head) lst->head->left = new;
    new->right = lst->head;
    lst->head = new;
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
}
void glthread_init(glthread_t *lst, unsigned int offset)
{
    lst->head = NULL;
    lst->offset = offset;
}
