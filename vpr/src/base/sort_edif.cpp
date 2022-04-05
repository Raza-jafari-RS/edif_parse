
















#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "read_edif.cpp"
#include "sort_edif.h"

class usefull_data 
{
  public:
  std::vector<std::pair<char* , char*>>ports_vec;
  //std::vector<std::tuple< int, char* , char*>>con_vec;
  std::vector<std::pair<char*, std::vector<char*>>>nets_vec;
  struct Cell* read_thelinklist(struct SNode *head)
  {
    int list_depth=0;
    std::vector<Cell>cells_vector;

    struct SNode *current= head;
     struct Cell *n_cell = NULL;
    n_cell = new Cell;
    while (current!=NULL)
    {

      if (current->type==0||current->type==5)
      {
        list_depth=current->list_counter;
      }
      else if (current->type==2)
      { 

        std::string cmp_string = "cell";
        std::string input_string =  current->value;
        if (input_string == cmp_string)
        // The cell starts here when we encounter the word "cell"
        {
          current = current->next;
          if (current->type==0||current->type==5)
      		{
             //list_depth=current->list_counter;
				    current = current->next;
        		cmp_string = "rename";
						input_string =  current->value;
						if (input_string == cmp_string)
						{
						current = current->next;
						n_cell->cell_name = current->value;
						printf ("\n   The cell is created with the name of %s", n_cell->cell_name);
						}
          }
          // A struct with the name cell is created
         else
         {
          n_cell->cell_name = current->value;
          printf ("\n   The cell is created with the name of %s", n_cell->cell_name);
         }

          // Now we will iterate in the cell untill we reach the end of the cell
          int cell_iteration = list_depth-1 ;
          //   Entering the cell it will iterate untill the cell ends
          while (list_depth>cell_iteration )
          {
            current = current->next;
            if (current->type==0||current->type==5)
            {
              list_depth=current->list_counter;
            }
            else if (current->type==2)
            { 
              // now getting the interface of the cell the method is similar to a cell
              input_string = current->value;
              cmp_string = "interface";
              if (input_string==cmp_string)
              {
                int interface_iteration= list_depth-1;
                while (list_depth>interface_iteration )
                {
                  current = current->next;
                  if (current->type==0||current->type==5)
                  {
                    list_depth=current->list_counter;
                  }
                  if (current->type==2)
                  {
                    
                    // creating my ports structure
                    cmp_string = "port";
                    input_string= current->value;
                    if (input_string == cmp_string)
                    {
                      current = current->next;
                      Port *n_port = NULL;
                      n_port = new Port;
                      printf("\n current type is %d",current->type);
                      printf("\n port value = %s",current->value);
                     if (current->type==0||current->type==5)
      		              {
                          list_depth=current->list_counter;
				                  current = current->next;
        		              cmp_string = "array";

						              input_string =  current->value;
						              if (input_string == cmp_string)
						              {
						                current = current->next;
                            n_cell->ports = n_port;
                            n_port->port_name = current->value;
                            printf ("The port is : %s",n_port->port_name);
                            current = current->next;
                            current = current->next;
                            current = current->next;
                            current = current->next;
                            current = current->next;
                            n_port->port_dirt = current->value;
						                printf ("\n   The port is renamed with the name of %s and its direction is %s ", n_port->port_name, n_port->port_dirt);
						              }
                        }
                      else
                      {
                        n_cell->ports = n_port;
                        n_port->port_name = current->value;
                        // printf ("The port is : %s",n_port->port_name);
                        current = current->next;
                        current = current->next;
                        current = current->next;
                        n_port->port_dirt = current->value;
                      }
                      ports_vec.push_back (std::make_pair (n_port->port_name,n_port->port_dirt));

                      printf ("\n The port is : %s \n Direction is : %s",n_port->port_name,n_port->port_dirt);
                    } 
                  } 
                }
              }

              //   second section of contents
              cmp_string = "contents";
              if (input_string == cmp_string)
              {
                printf("\n\n\n\n\nentering content   ");
                int content_iteration= list_depth-1;
                while (list_depth>content_iteration )
                {   
                  current = current->next;
                  if (current->type==0||current->type==5)
                  {
                    list_depth=current->list_counter;
                  }

                  if (current->type==2)
                  {
                    cmp_string = "instance";
                    input_string= current->value;
                     if (input_string == cmp_string)
                      {

                        Instan *n_instan = NULL;
                        n_instan = new Instan;
                        current = current->next;

                         if (current->type==0||current->type==5)
      		                {
                            //list_depth=current->list_counter;
                           //F printf("\nentering the main oop the list depth is %d",list_depth );
				                    current = current->next;
        		                cmp_string = "rename";
						                input_string =  current->value;
						                if (input_string == cmp_string)
						                {
						                  current = current->next;
						                  n_instan->inst_name = current->value;
						                  printf ("\n\n\n\n\n  The instance is renamed with the name of %s", n_instan->inst_name);
						                }
                          }
                        else
                            {
                              n_instan->inst_name = current->value;
                              printf ("\n\n\n\n\n  The instance is created with the name of %s", n_instan->inst_name);
                            }
                           int instance_iteration = list_depth-1 ;
                            //   Entering the cell it will iterate untill the cell ends
                           while (list_depth>instance_iteration )
                            {
                             //printf("\nentering the while loop the list depth is %d",list_depth );
                              current = current->next;
                            if (current->type==0||current->type==5)
                              {
                                list_depth=current->list_counter;
                              }

                               if (current->type==2)
                                {
                                  //printf("\nThe value is the list depth is %s",current->value );
                                  cmp_string = "cellRef";
                                  input_string= current->value;

                                  if (input_string == cmp_string)
						                      {
                                    printf ("\nfound a cell ref ");
                                    current = current->next;
                                    n_instan->inst_ref = current->value;
                                  }
                                  cmp_string = "property";
                                  input_string= current->value;
                                  if (input_string == cmp_string)
						                      {
                                    printf("\nentering the property");
                                    current = current->next;
                                    cmp_string = "LUT";
                                    input_string= current->value;
                                    if (input_string == cmp_string)
                                    {
                                      current = current->next;
                                      current = current->next;
                                      current = current->next;
                                      n_instan->property_lut = current->value;
                                      printf("The lut property is %s",n_instan->property_lut);
                                    }
                                    cmp_string = "WIDTH";
                                    if (input_string == cmp_string)
                                    {

                                      current = current->next;
                                      current = current->next;
                                      current = current->next;
                                      n_instan->property_width = current->value;
                                      printf("The width property is %s",n_instan->property_width);
                                    }
                                  }
                                }
                              }
                            }

                    // getting the instances present in a cell

                    // creating my ports structure
                    printf("\n\n\n\n\n\n\nexit the print instance" );
                    cmp_string = "net";
                    //input_string= current->value;
                    if (input_string == cmp_string)
                    {
                      struct Nets *n_net;
                      n_net = new Nets;
                      n_cell->nets = n_net;
                      current = current->next;
                      n_net->net_name = current->value;
                      printf ("\n The net is  :  %s",n_net->net_name);
                      int net_joining_iteration= list_depth-1;
                      while (list_depth>net_joining_iteration )
                      {
                        current = current->next;
                        if (current->type==0||current->type==5)
                        {
                          list_depth=current->list_counter;
                          printf("\n The updated iteration is %d",list_depth );
                        }
                        if (current->type==2)
                        {
                          cmp_string = "portRef";
                          input_string = current->value;
                          if (input_string == cmp_string)
                          {
                            current = current->next;
                            if (current->type==0||current->type==5)
                            {
                              current = current->next;
                              cmp_string = "member";
                              input_string = current->value;
                              if (input_string == cmp_string)
                              {
                                current = current->next;
                                n_net->start_net=current->value;
                                current = current->next;
                                n_net->member_num=current->value;
                              }

                            }
                            else
                            {
                              n_net->start_net=current->value;
                              //n_net->member_num=0;
                            }
                            int instance_ref_iteration= list_depth-1;


                            while (list_depth>instance_ref_iteration )
                            {
                              current = current->next;
                              if (current->type==0||current->type==5)
                              {
                                list_depth=current->list_counter;
                                printf("\n The updated iteration is %d",list_depth );
                              }
                              if (current->type==2)
                              {
                                cmp_string = "instanceRef";
                                input_string = current->value;
                                if (input_string == cmp_string)
                                {
                                  current = current->next;
                                  printf("\ninstance ref found %s",current->value );
                                }

                              }
                            }

                          }
                        }
                      }
                    }
                  }
                }
              }
            } 
          } 
        }
      }
      current = current->next;
    }
    return n_cell;
  }
};
 
