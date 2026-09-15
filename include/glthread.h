typedef struct glthread_node_t
{
    void *left;
    void *right;
} glthread_node_t;

typedef struct glthread_t
{
    glthread_node_t *head;
    unsigned int offset;
} glthread_t;

void glthread_add(glthread_t *lst, glthread_node_t *new);
void glthread_del(glthread_t *lst, glthread_node_t *glnode);
void glthread_init(glthread_t *lst, unsigned int offset);
