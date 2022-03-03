#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sexpr.h"

#define BUFFER_MAX 512

int is_float(char *str) {
 // printf ("\n entering is_float function to check %s", str );
  char *ptr = NULL;
  strtod(str, &ptr);

  return !*ptr;
}

int is_integer(char *str) {
  //printf ("\n entering is_integer function to check %s", str );
  char *ptr = NULL;
  strtol(str, &ptr, 10);
  return !*ptr;
}

int is_lst_term(int c) {
  //printf ("\n entering is_lst function to check %c", c );
  return c == EOF || isspace(c) || c == '(' || c == ')';
}

int is_str_term(int c) {
  //printf ("\n entering is_str_term to check %d", c );
  return c == EOF || c == '"';          // it will return 1 if c == EOF || c == '"' else return 0
}

char *read_value(FILE *fp, int *c, int (*is_term)(int)) {
  int len = 0;
  char buffer[BUFFER_MAX + 1];

  while (!is_term(*c = fgetc(fp)) && len < BUFFER_MAX) {
    buffer[len] = *c;
    len++;
  }
  buffer[len] = '\0';
  //printf ("\n entering read_value function to check %s", buffer );
  
  char *str = (char*)malloc((len + 1) * sizeof(char));
  return strcpy(str, buffer);
}

// Recursively parse an s-expression from a file stream
struct SNode *snode_parse(FILE *fp) {
  // Using a linked list, nodes are appended to the list tail until we 
  // reach a list terminator at which point we return the list head.
  struct SNode *tail, *head = NULL;
  int c;

  while ((c = fgetc(fp)) != EOF) {
    struct SNode *node = NULL;
  //printf ("\n entered the while loop and c is %c",c);
    if (c == ')') {
      //printf ("\n the ) is found %c",c);
      // Terminate list recursion
      break;
    } else if (c == '(') {
      // Begin list recursion
        node = new SNode;
     // node = malloc(sizeof(struct SNode));
      node->type = LIST;
      node->list = snode_parse(fp);
    } else if (c == '"') {
      // Read a string
      node = new SNode;
      //node = malloc(sizeof(struct SNode));
      node->type = STRING;
      node->value = read_value(fp, &c, &is_str_term);
    } else if (!isspace(c)) {
      //printf ("\n before unget c : %c", c);
      // Read a float, integer, or symbol
      ungetc(c, fp);
      //printf ("\nafter unget c : %c", c);
      node = new SNode;
      //node = malloc(sizeof(struct SNode));
      node->value = read_value(fp, &c, &is_lst_term);
      //printf ("\n node->value : %s", node->value );
      // Put the terminator back
      ungetc(c, fp);

      if (is_integer(node->value)) {
        node->type = INTEGER;
        //printf ("\n int : %d", *node->value );
      } else if (is_float(node->value)) {
        node->type = FLOAT;
        // printf ("\n The float taken is  : %f", node->type );
      } else {
        node->type = SYMBOL;
      }
    }
     
    if (node != NULL) {
      // Terminate the node
      node->next = NULL;
      
      if (head == NULL) {
        // Initialize the list head
        head = tail = node;
      } else {
        // Append the node to the list tail
        tail = tail->next = node;
      }
    }
  }
 //LIST,
  //STRING,
  //SYMBOL,
  //INTEGER,
  //FLOAT
struct SNode *current= head;
while (current!=NULL)
  {
  if (current->type==0)
 { printf ("\n \n \n \n The list starts here");}
 if (current->type==1)
 { printf ("\n The string is  %s", current->value);}
 if (current->type==2)
 { printf ("\n The symbol is  %s", current->value);}
 if (current->type==3)
 { printf ("\n The integer is  %c", *current->value);}
  if (current->type==4)
 { printf ("\n The float is  %f", current->value);}
  current = current->next;
  }
  return head;
}

// Recursively free memory allocated by a node
void snode_free(struct SNode *node) {
  while (node != NULL) {
    struct SNode *tmp = node;

    if (node->type == LIST) {
      snode_free(node->list);
    } else {
      // Free current value
      free(node->value);
      node->value = NULL;
    }

    node = node->next;

    // Free current node
    free(tmp);
    tmp = NULL;
  }
}
