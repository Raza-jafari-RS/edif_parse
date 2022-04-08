#include "vtr_assert.h"
#include "vtr_util.h"
#include "vtr_log.h"
#include "vtr_logic.h"
#include "vtr_time.h"
#include "vtr_digest.h"

#include "vpr_types.h"
#include "vpr_error.h"
#include "globals.h"
#include "read_blif.h"
#include "arch_types.h"
#include "echo_files.h"
#include "edif_to_atomnetlist.h"
#include "netlist.h"
#include "vtr_logic.h"

#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "sort_edif.cpp"


AtomNetlist names(std::vector<std::string> nets) {

	 AtomNetlist atom_nl("my_netlist");
	 t_model* blk_model; //Initialize the block model appropriately
	 blk_model = new t_model;
	 std::vector<AtomBlockId> blkvect;
	 const t_model* inpad_model_;
	 const t_model* outpad_model_;
	 AtomNetId net_id;
	 printf ("Open the file stream");
	 FILE *fp = fopen("/home/users/raza.jafari/netlists/edif/adder_output_edif.edn", "r");
	 //FILE *fp = fopen("/home/users/raza.jafari/test_cases/vtr-verilog-to-routing/libs/EXTERNAL/libedifparse/test_cases/edif_files/test1.edif", "r");
	   // Read the file into a tree
	 struct SNode *node = snode_parse(fp);

	 usefull_data u1;
	 char* top_cell = (u1.find_top_(node));

	 struct Cell *cell_ = (u1.read_thelinklist (node, top_cell));
	 int i=0;
	 for (i=0; i<u1.ports_vec.size(); i++)
	 {
	 printf ("\nport is %s & Direction is %s ",u1.ports_vec[i].first, u1.ports_vec[i].second );
	 }


	 for ( i=0; i<u1.nets_vec.size(); i++)
	 {
	   printf (" \n the net is %s",u1.nets_vec[i].first);
	 }

	 for(int k =0; k<u1.con_vec.size(); k++)
	   {
	     printf("\n\n\n NET NAME IS : %s \n PORT NAME IS : %s \n PIN NUMBER IS : %s \n INSTANCE NAME IS %s",std::get<0>(u1.con_vec[k]), std::get<1>(u1.con_vec[k]), std::get<2>(u1.con_vec[k]), std::get<3>(u1.con_vec[k]) );
	     }
	 int i=0;


	 for (i=0; i<u1.ports_vec.size(); i++)
	 {
	 printf ("\nport is %s & Direction is %s and iteration number is %d",u1.ports_vec[i].first, u1.ports_vec[i].second,i );
	 std::string in_out_string = u1.ports_vec[i].second;
	 std::string cmp_string = "INPUT";

	 if (in_out_string==cmp_string)
	 {
		 char* out_port = u1.ports_vec[i].first;
		 t_model_ports* outputs;
		 outputs = new t_model_ports;
		 outputs->name = out_port;
		 outputs->dir = OUT_PORT;
		 outputs->size = 1;
	     outputs->min_size = 0;
		 blk_model->outputs = outputs;
		inpad_model_ = blk_model;
		blkvect.emplace_back(atom_nl.create_block(out_port, blk_model));
		AtomPortId port_id = atom_nl.create_port(blkvect.back(), blk_model->outputs);
		const std::string& out_blk = atom_nl.block_name(blkvect.back());
		const std::string& output_port = atom_nl.port_name(port_id);
		net_id = atom_nl.create_net(u1.nets_vec[i].first);
		const std::string& net_out = atom_nl.net_name(net_id);
		const std::string& netlistname = atom_nl.netlist_name();
		printf(" block created is given as::%s\n", out_blk.c_str());
		printf(" port created is given as::%s\n", output_port.c_str());
		printf("NET is given as::%s\n", net_out.c_str());
		printf("NETLIST name is given as::%s\n", netlistname.c_str());
		atom_nl.create_pin(port_id, 0, net_id, PinType::DRIVER);
	 }
	 cmp_string = "OUTPUT";
	 if (in_out_string==cmp_string)
	 {
		 printf ("\n\n\n\n\n\n\n A block is created for the output");

		 t_model_ports* inputs;
		inputs = new t_model_ports;
		char* in_port = u1.ports_vec[i].first;
	     inputs->name = in_port;
		inputs->dir = IN_PORT;
		 inputs->size = 1;
		inputs->min_size = 0;

		blk_model->inputs = inputs;
		outpad_model_ = blk_model;

		blkvect.emplace_back(atom_nl.create_block(in_port, blk_model));
		AtomPortId port_id = atom_nl.create_port(blkvect.back(), blk_model->inputs);
		 const std::string& in_blk = atom_nl.block_name(blkvect.back());
		 const std::string& input_port = atom_nl.port_name(port_id);
		 const std::string& net_in = atom_nl.net_name(net_id);
		 const std::string& netlistname = atom_nl.netlist_name();

		 printf(" block created is given as::%s\n", in_blk.c_str());
		 printf(" port created is given as::%s\n", input_port.c_str());
		 printf("NET is given as::%s\n", net_in.c_str());
		printf("NETLIST name is given as::%s\n", netlistname.c_str());
		atom_nl.create_pin(port_id, 0, net_id, PinType::SINK);

	 }
	 atom_nl.set_block_types(inpad_model_, outpad_model_);
	 }

	 for(AtomBlockId blk_id : atom_nl.blocks()){
	 		const std::string& block_name = atom_nl.block_name(blk_id);
	 		printf("BLOCK : %s \n", block_name.c_str());
	 		for(AtomPortId port_id_ : atom_nl.block_input_ports(blk_id)){
	 			for(AtomPinId pin_id_ : atom_nl.port_pins(port_id_)) {
	 				AtomNetId net_id_ = atom_nl.pin_net(pin_id_);
	 				const std::string& net_name = atom_nl.net_name(net_id_);
	 				printf("ASSOCIATED input NET : %s \n", net_name.c_str());

	 			}
	 		}


	 		for(AtomPortId port_id_ : atom_nl.block_output_ports(blk_id)){
	 					for(AtomPinId pin_id_ : atom_nl.port_pins(port_id_)) {
	 						AtomNetId net_id_ = atom_nl.pin_net(pin_id_);
	 						const std::string& net_name = atom_nl.net_name(net_id_);
	 						printf("ASSOCIATED output NET : %s \n", net_name.c_str());
	 					}
	 				}
	 	}

	 AtomNetlist::TruthTable truth_table(2);

	 truth_table[0].push_back(vtr::LogicValue::TRUE);
	 truth_table[1].push_back(vtr::LogicValue::FALSE);
	 atom_nl.verify();
	   fclose(fp);


	   // Deallocate the memory used by the tree
	   snode_free(node);

	   return atom_nl;
	 }

