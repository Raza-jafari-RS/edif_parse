#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "read_edif.h"

//int argc, char *argv[]

int read_edif() {

  
  // Open the file stream
  FILE *fp = fopen("/home/users/SHARE/raza/full_adder.edn", "r");

  // Read the file into a tree
struct SNode *node = snode_parse(fp);
    
  
  // Close the file stream
  fclose(fp);

  // Run tests
  //run_tests(node);

  // Deallocate the memory used by the tree
  snode_free(node);

  return 0;
}
