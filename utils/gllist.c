#include <stddef.h>
#include "gllist.h"

void gllist_init(gllist_t *lst, unsigned int offset)
{
    lst->head = NULL;
    lst->offset = offset;
    lst->count = 0;
}

void gllist_add(gllist_t *lst, glue_node_t *new)
{
    if (lst->head) lst->head->left = new;
    new->right = lst->head;
    lst->head = new;
    lst->count++;
}

void gllist_del(gllist_t *lst, glue_node_t *glnode)
{
    if (!glnode) return;
    if (glnode->left)
    {
        ((glue_node_t *)glnode->left)->right = glnode->right;
    }
    else
    {
        lst->head = glnode->right;
    }
    if (glnode->right)
    {
        ((glue_node_t *)glnode->right)->left = glnode->left;
    }
    glnode->left = NULL;
    glnode->right = NULL;
    lst->count--;
}

int gllist_empty(gllist_t *lst)
{
    return lst->head == NULL;
}

unsigned int gllist_size(gllist_t *lst)
{
    return lst->count;
}
