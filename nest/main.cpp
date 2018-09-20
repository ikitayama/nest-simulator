/*
 *  main.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Generated includes:
//#include "config.h"

// Includes from nest:
#include "neststartup.h"
#include "nest.h"
#include <iostream>
#include "dictutils.h"
#include "dictdatum.h"
#include "kernel_manager.h"
#include "doubledatum.h"
#include "integerdatum.h"
#include "nest_datums.h"
#include "nest_names.h"
#include "nest_types.h"
#include "logging.h"
#include "subnet.h"

using namespace nest;

int
main( int argc, char* argv[] )
{
  nest::init_nest( &argc, &argv );
  
  // before we begin; reset
  nest::reset_kernel();


  DictionaryDatum brunel_params(new Dictionary);
  brunel_params->insert("NE", 9000);
  brunel_params->insert("NI", 2250);
  brunel_params->insert("Nrec", 1000);
  DictionaryDatum model_params(new Dictionary);
  model_params->insert("E_L", 0.0); // mV
  
  DictionaryDatum stdp_params(new Dictionary);  
  stdp_params->insert(names::delay, 1.5); // ms
  stdp_params->insert(names::alpha, 0.0513);
  stdp_params->insert(names::lambda, 0.1); // STDP step size
  stdp_params->insert(names::mu, 0.4); // STDP weight dependence exponent (potentiation)
  stdp_params->insert(names::tau_plus, 15.0); // time constant for potentiation
  


  brunel_params->info(std::cout);
  // BuildNetwork
  // create node 0
  DictionaryDatum dict(new Dictionary);
  dict->insert(names::resolution, 0.1); // ms
  dict->insert(names::overwrite_files, false);
  //bool new_value = false; // do not write to logs
  //updateValue< bool >( dict, names::overwrite_files, new_value );
  nest::set_kernel_status(dict); 
  //dict->info(std::cout);
  std::cout << dict->lookup2(names::resolution) << std::endl;
  std::cout << dict->lookup2(names::overwrite_files) << std::endl;
  std::cout << nest::current_subnet() << std::endl;
  

  double scale = 1.0;
  int NE = 70;
  int CE = std::round(1. * NE / scale); 

  //dict = nest::get_kernel_status();
  //std::cout << dict << std::endl;
  nest::register_iaf_psc_alpha();
  DictionaryDatum params(new Dictionary);
  nest::set_model_defaults("iaf_psc_alpha", params);
  
  nest::index current_net = current_subnet();
  std::cout << "current net gid " << current_net << std::endl;
  nest::index base_net_gid = nest::create( "subnet", 1 ); 
  std::cout << "base net gid " << base_net_gid << std::endl;
  
  DictionaryDatum tmp(new Dictionary);
  nest::set_node_status(1, tmp);
  std::cout << "set_node_status done" << std::endl;
  nest::change_subnet(1); // to the excititely neurons subnet
  std::cout << "current subnet gid " << nest::current_subnet() << std::endl;
  const nest::index last_node_gid = nest::create( "iaf_psc_alpha", 70 );
  std::cout << "last node gid " << last_node_gid << std::endl;
  nest::change_subnet(nest::current_subnet());

  nest::index base_net_gid2 = nest::create( "subnet", 1 );
  nest::change_subnet(base_net_gid2);
  nest::set_node_status(base_net_gid2, tmp);
  const nest::index last_node_gid2 = nest::create( "iaf_psc_alpha", 70 );
  std::cout << "current subnet gid " << nest::current_subnet() << " last node gid created " << last_node_gid2 << std::endl;
  nest::change_subnet(nest::current_subnet());


  double nu_thresh = 0.1; // V_th / ( CE * tau_m / C_m * JE_pA * * tau_syn)
  double nu_ext = 0.2; // nu_thresh * eta;
  DictionaryDatum p1(new Dictionary);
  p1->insert( names::rate, nu_ext * CE * 1000. );
  p1->info(std::cout);
  nest::register_poisson_generator();
  nest::set_model_defaults("poisson_generator", p1);

  DictionaryDatum p2(new Dictionary);
  nest::register_static_synapse_hpc();
  nest::set_model_defaults("static_synapse_hpc", p2);
  //params = nest::get_model_defaults(theModel);
  //std::cout << params << std::endl;
  DictionaryDatum syn_std_params(new Dictionary);
  nest::copy_model("static_synapse_hpc", "syn_std", syn_std_params);

  DictionaryDatum syn_ex_params(new Dictionary);
  nest::copy_model("static_synapse_hpc", "syn_ex", syn_ex_params);

  DictionaryDatum syn_in_params(new Dictionary);
  nest::copy_model("static_synapse_hpc", "syn_in", syn_in_params);  

  //nest::register_stdp_pl_synapse_hom_hpc();
  //nest::set_model_defaults("stdp_pl_synapse_hom_hpc", stdp_params);





  // presim stage
  nest::simulate(10);

  nest::simulate(10);

  return 0;
}
