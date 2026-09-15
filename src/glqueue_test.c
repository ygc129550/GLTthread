#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "glqueue.h"

typedef struct emp
{
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glthread_node_t glnode;
} emp;

static void print_emp(glthread_node_t *node)
{
    emp *e = (emp *)((char *)node - offsetof(emp, glnode));
    printf("  [%u] %-10s salary=%-6u %s\n", e->emp_id, e->name, e->salary, e->designation);
}

int main(void)
{
    emp employees[] = {
        {"Arun",  31000, "Mgr",       61},
        {"Bob",   15000, "Developer", 53},
        {"Carol", 22000, "Designer",  47},
        {"Dave",  18000, "Tester",    39},
    };
    int n = sizeof(employees) / sizeof(employees[0]);

    glqueue_t q;
    glqueue_init(&q, offsetof(emp, glnode));

    /* enqueue all */
    printf("=== Enqueue %d employees ===\n", n);
    for (int i = 0; i < n; i++)
    {
        memset(&employees[i].glnode, 0, sizeof(glthread_node_t));
        glqueue_enqueue(&q, &employees[i].glnode);
        printf("  enqueued: %s\n", employees[i].name);
    }
    printf("queue size: %u, empty: %d\n", glqueue_size(&q), glqueue_empty(&q));

    /* peek front */
    printf("\n=== Front ===\n");
    glthread_node_t *front = glqueue_front(&q);
    if (front) print_emp(front);

    /* dequeue all */
    printf("\n=== Dequeue all ===\n");
    while (!glqueue_empty(&q))
    {
        glthread_node_t *node = glqueue_dequeue(&q);
        printf("  dequeued: ");
        print_emp(node);
    }
    printf("queue size: %u, empty: %d\n", glqueue_size(&q), glqueue_empty(&q));

    /* dequeue from empty queue */
    printf("\n=== Dequeue from empty ===\n");
    glthread_node_t *null_node = glqueue_dequeue(&q);
    printf("dequeue returned: %s\n", null_node ? "node" : "NULL");

    return 0;
}
