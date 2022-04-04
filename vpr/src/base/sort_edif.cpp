
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
  std::vector<char*>con_vec;
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
         }
          printf ("\n   The cell is created with the name of %s", n_cell->cell_name);
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

                     if (current->type==0||current->type==5)
      		              {
				                    current = current->next;
        		                cmp_string = "rename";
						                input_string =  current->value;
						                if (input_string == cmp_string)
						                {
						                  current = current->next;

                              n_cell->ports = n_port;
                              n_port->port_name = current->value;
                     // printf ("The port is : %s",n_port->port_name);
                              current = current->next;
                              current = current->next;
                              current = current->next;
                              current = current->next;
                              current = current->next;
                              n_port->port_dirt = current->value;
						                 // printf ("\n   The port is renamed with the name of %s and its direction is %s ", n_port->port_name, n_port->port_dirt);
						                }
                        }

                      //printf ("\nThe Port is  %s ", current->value);
                      else {

                      n_cell->ports = n_port;
                      n_port->port_name = current->value;
                     // printf ("The port is : %s",n_port->port_name);
                      current = current->next;
                      current = current->next;
                      current = current->next;
                      n_port->port_dirt = current->value;
                      }
                     // ports_vec.push_back (n_port->port_dirt);
                      //printf ("\n %d", (ports_vec.size()));
                       //ports_vec.push_back (n_port->port_dirt);
                      // printf ("\n %d",(ports_vec.size()));
                      ports_vec.push_back (std::make_pair (n_port->port_name,n_port->port_dirt));
                    //printf ("\nport is %s & Direction is %s ",ports_vec[0].first, ports_vec[0].second );
                      printf ("\n The port is : %s \n Direction is : %s",n_port->port_name,n_port->port_dirt);
                    } 
                  } 
                }
              }
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
                        current = current->next;
                        Instan *n_ins = NULL;
                        n_ins = new Instan;
                        if (current->type==0||current->type==5)
      		              {

				                  current = current->next;
        		              cmp_string = "rename";
						              input_string =  current->value;
						              if (input_string == cmp_string)
						              {
						                current = current->next;
						                n_ins->inst_name = current->value;
						                printf ("\n   The cell is created with the name of %s", n_ins->inst_name);
						              }
                        }
                        // A struct with the name cell is created
                       else
                       {
                         n_ins->inst_name = current->value;

                       }

                       int instance_iteration = list_depth-1 ;
                            //   Entering the cell it will iterate untill the cell ends
                           while (list_depth>instance_iteration )
                            {
                             printf("\nentering the while loop the list depth is %d    %d",list_depth ,instance_iteration);
                             printf ("\ncurrent value %s",current->value);
                              current = current->next;
                            if (current->type==0||current->type==5)
                              {
                                list_depth=current->list_counter;
                              }
                             if (current->type==2)
                                {
                                 printf ("\n %s",current->value);
                                  cmp_string = "cellRef";
                                  input_string= current->value;

                                  if (input_string == cmp_string)
						                      {
                                    printf ("\nfound a cell ref ");
                                    current = current->next;
                                    n_ins->inst_ref = current->value;
                                  }
                                  cmp_string = "property";

                                  if (input_string == cmp_string)
						                      {
                                    printf("\n entering the property");
                                    current = current->next;
                                    cmp_string = "LUT";
                                    input_string= current->value;
                                    if (input_string == cmp_string)
                                    {
                                      current = current->next;
                                      current = current->next;
                                      current = current->next;
                                      n_ins->property_lut = current->value;
                                      printf("\nThe lut property is %s",n_ins->property_lut);
                                    }
                                    cmp_string = "WIDTH";
                                    if (input_string == cmp_string)
                                    {

                                      current = current->next;
                                      current = current->next;
                                      current = current->next;
                                      n_ins->property_width = current->value;
                                      printf("\nThe lut property is %s",n_ins->property_width);
                                    }
                                  }
                                }
                              }
                      }



                    // getting the instances present in a cell

                    // creating my ports structure
                    cmp_string = "net";
                    //input_string= current->value;
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
                      }
                      if (current->type==2)
                      {
                        cmp_string = "portRef";
                        input_string = current->value;
                        if (input_string == cmp_string)
                        {
                          current = current->next;
                          n_net->start_net=current->value;
                          con_vec.push_back (n_net->start_net);
                          printf ("\nThe net is starting from: %s",current->value );
                          current = current->next;
                          current = current->next;
                          current = current->next;
                          current = current->next;
                          n_net->end_net=current->value;
                          con_vec.push_back (n_net->end_net);
                          nets_vec.push_back (std::make_pair (n_net->net_name,con_vec));
                          printf ("\nThe net ends at reference is: %s",current->value );
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
 
