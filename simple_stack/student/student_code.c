#include "student_code.h"
#include <stdlib.h>
#include<stdio.h>

/*int pop(struct node *head, char **result){
  if (!head)
    return 1;

  struct node* tmp = head;
  head = head->next;

  *result = tmp->value;
  free(tmp);

  return 0;
}*/

int push(struct node **head, const char *value){
  if (!head)
    return 1;

  struct node *node = (struct node*) malloc(sizeof(struct node));
  if (!node)
    return 1;

  int len = strlen(value);
  node->name = (char*) malloc(len);
  strncpy(node->name, value, len);

  node->next = *head;
  *head = node;

  //char* test = (char*) value;
  //printf("%p\n", &test);
  //printf("%p\n", test);
  //*(test) = 'u';

  //*value = 'u';

  return 0;
}
