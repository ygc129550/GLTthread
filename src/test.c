#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "glthread.h"

typedef struct emp
{
    char name[30];
    unsigned int salary;
    char designation[30];
    unsigned int emp_id;
    glthread_node_t glnode;
} emp;

void print_emp_details(glthread_node_t *glnode)
{
    emp *addr = (emp*)((char*)glnode - offsetof(emp, glnode));
    printf("name: %s\n", addr->name);
    printf("salary: %d\n", addr->salary);
    printf("designation: %s\n", addr->designation);
    printf("emp_id: %d\n", addr->emp_id);
}

void print_all_list(glthread_node_t *head)
{
    glthread_node_t *cur = head;
    while (cur)
    {
        print_emp_details(cur);
        cur = cur->right;
    }
}
 
int main()
{
    emp arun;
    memset(&arun, 0, sizeof(arun));
    snprintf(arun.name, 30, "Arun");
    arun.salary = 31000;
    snprintf(arun.designation, 30, "Mgr");
    arun.emp_id = 61;

    emp bob;
    memset(&bob, 0, sizeof(bob));
    snprintf(bob.name, 30, "Bob");
    bob.salary = 15000;
    snprintf(bob.designation, 30, "slslsl");
    bob.emp_id = 53;

    glthread_t lst;
    memset(&lst, 0, sizeof(lst));
    glthread_add(&lst, &bob.glnode);
    glthread_add(&lst, &arun.glnode);

    print_all_list(lst.head);

    glthread_del(&lst, &arun.glnode);
    printf("------------------\n");
    print_all_list(lst.head);

    return 0;
}