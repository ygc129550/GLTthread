#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "glstack.h"

typedef struct emp
{
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glue_node_t glnode;
} emp;

static void print_emp(glue_node_t *node)
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

    glstack_t stk;
    glstack_init(&stk, offsetof(emp, glnode));

    /* push all */
    printf("=== Push %d employees ===\n", n);
    for (int i = 0; i < n; i++)
    {
        memset(&employees[i].glnode, 0, sizeof(glue_node_t));
        glstack_push(&stk, &employees[i].glnode);
        printf("  pushed: %s\n", employees[i].name);
    }
    printf("stack size: %u, empty: %d\n", glstack_size(&stk), glstack_empty(&stk));

    /* peek top */
    printf("\n=== Top ===\n");
    glue_node_t *top = glstack_peek(&stk);
    if (top) print_emp(top);

    /* pop all */
    printf("\n=== Pop all ===\n");
    while (!glstack_empty(&stk))
    {
        glue_node_t *node = glstack_pop(&stk);
        printf("  popped: ");
        print_emp(node);
    }
    printf("stack size: %u, empty: %d\n", glstack_size(&stk), glstack_empty(&stk));

    /* pop from empty stack */
    printf("\n=== Pop from empty ===\n");
    glue_node_t *null_node = glstack_pop(&stk);
    printf("pop returned: %s\n", null_node ? "node" : "NULL");

    return 0;
}
