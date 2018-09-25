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
#include <omp.h>
#include <math.h>
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

#include <gsl/gsl_errno.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_sf_erf.h>   // as more and more special functions get
#include <gsl/gsl_sf_gamma.h> // added, replace by <gsl/gsl_sf.h>
#include <gsl/gsl_sf_lambert.h>

using namespace nest;


double ConvertSynapseWeight(double tauMem, double tauSyn, double CMem)
{
	double a = tauMem / tauSyn;
	double b = 1.0 / tauSyn - 1.0 / tauMem;

  	gsl_sf_result result;
  	int status = gsl_sf_lambert_Wm1_e( -exp(1.0/a)/a, &result );
  	if ( status )
  	{
    		return 0;
  	}

	//double t_rise = 1.0 / b * (-LambertWm1(-exp(1.0/a)/a)-1.0/a);
	double t_rise = 1.0 / b * (-result.val - 1.0 / a);

	double r = exp(1.0)/(tauSyn*CMem*b) * ((exp(-t_rise/tauMem) - exp(-t_rise/tauSyn)) / b - t_rise * exp(-t_rise/tauSyn));

	return 1. / r;
}

int
main( int argc, char* argv[] )
{
  nest::init_nest( &argc, &argv );
  
  // before we begin; reset
  nest::reset_kernel();

  double tau_syn = 0.32582722403722841; // ms

  DictionaryDatum brunel_params(new Dictionary);
  brunel_params->insert("NE", 9000);
  brunel_params->insert("NI", 2250);
  brunel_params->insert("Nrec", 1000);

  DictionaryDatum iaf_psc_alpha_params(new Dictionary);
  iaf_psc_alpha_params->insert(names::E_L, 0.0); // mV
  iaf_psc_alpha_params->insert(names::C_m, 250.0); // pF
  iaf_psc_alpha_params->insert(names::tau_m, 10.0); // ms
  iaf_psc_alpha_params->insert(names::t_ref, 0.5); // ms
  iaf_psc_alpha_params->insert(names::V_th, 20.0); // mV
  iaf_psc_alpha_params->insert(names::V_reset, 0.0); // mV
  iaf_psc_alpha_params->insert(names::tau_syn_ex, tau_syn); // time const.
  iaf_psc_alpha_params->insert(names::tau_syn_in, tau_syn); 
  iaf_psc_alpha_params->insert(names::tau_minus, 30.0); // ms
  iaf_psc_alpha_params->insert(names::V_m, 5.7); // mV

  brunel_params->insert("randomize_Vm", true);
  brunel_params->insert("mean_potential", 5.7); // mV
  brunel_params->insert("sigma_potential", 7.2); // mV
  brunel_params->insert(names::delay, 1.5); // ms
  brunel_params->insert("JE", 0.14); //mV
  brunel_params->insert("sigma_w", 3.47); // pA
  brunel_params->insert(names::g, -5.0);

  DictionaryDatum stdp_params(new Dictionary);  
  stdp_params->insert(names::delay, 1.5); // ms
  stdp_params->insert(names::alpha, 0.0513);
  stdp_params->insert(names::lambda, 0.1); // STDP step size
  stdp_params->insert(names::mu, 0.4); // STDP weight dependence exponent (potentiation)
  stdp_params->insert(names::tau_plus, 15.0); // time constant for potentiation
  
  brunel_params->insert(names::eta, 1.685);

  brunel_params->info(std::cout);

  // BuildNetwork
  // create node 0
  DictionaryDatum kernel_params(new Dictionary);
  //dict->insert(names::total_num_virtual_procs, omp_get_num_threads()); // simulation setup is 1 node, multiple threads
  kernel_params->insert(names::total_num_virtual_procs, 2); // simulation setup is 1 node, multiple threads
  kernel_params->insert(names::resolution, 0.1); // ms
  kernel_params->insert(names::overwrite_files, false);
  kernel_params->info(std::cout);
  //bool new_value = false; // do not write to logs
  //updateValue< bool >( kernel_params, names::overwrite_files, new_value );
  nest::set_kernel_status(kernel_params); 
  std::cout << "resolution " << kernel_params->lookup2(names::resolution) << std::endl;
  std::cout << "overwrite_files " << kernel_params->lookup2(names::overwrite_files) << std::endl;
  std::cout << "current subnet gid " << nest::current_subnet() << std::endl;
 
  nest::register_conn_builders(); // "all_to_all" etc.

  double scale = 1.0;
  //int CE = std::round(1. * getValue<int>(brunel_params, "NE")/scale);
  int CE = std::round(1. * 9000 / scale);

  nest::register_iaf_psc_alpha();
  nest::set_model_defaults("iaf_psc_alpha", iaf_psc_alpha_params);
  iaf_psc_alpha_params->info(std::cout);
  nest::create("iaf_psc_alpha", 1); 
  std::cout << "iaf_psc_alpha model id " << nest::get_model_id("iaf_psc_alpha") << std::endl; 
  const nest::index current_net = current_subnet();
  std::cout << "current net gid " << current_net << std::endl;
  const nest::index base_net_gid = nest::create( "subnet", 1 ); // for excitatory neurons network
  std::cout << "base net gid " << base_net_gid << std::endl;
  const nest::index e_from = base_net_gid + 1;
  nest::print_network(0,3,std::cout); 
  DictionaryDatum tmp(new Dictionary);
  nest::set_node_status(1, tmp);
  std::cout << "set_node_status done" << std::endl;
  nest::change_subnet(base_net_gid); // to the excititely neurons subnet
  std::cout << "current subnet gid " << nest::current_subnet() << std::endl;
  const nest::index e_to = nest::create( "iaf_psc_alpha", brunel_params->lookup2("NE") );
  std::cout << "excitatory last node gid " << e_to << std::endl;
  nest::change_subnet(0);

  nest::index base_net_gid2 = nest::create( "subnet", 1 );
  nest::change_subnet(base_net_gid2);
  nest::set_node_status(base_net_gid2, tmp);
  const nest::index i_from = base_net_gid2 + 1;
  const nest::index i_to = nest::create( "iaf_psc_alpha", brunel_params->lookup2("NI") );
  std::cout << "current subnet gid " << nest::current_subnet() << std::endl;
  std::cout << " inhibitory last node gid created " << i_to << std::endl;
  nest::change_subnet(0); // back to kernel

  // randomize Vm
  /*
  nest::index i;
  for (i=1;i<last_node_gid+1;i++) {
        DictionaryDatum tmp(new Dictionary);
        //tmp->insert(names::V_m
	//set_node_status(i, );	
  }
  */
  double tau_m = iaf_psc_alpha_params->lookup2(names::tau_m);
  double C_m = iaf_psc_alpha_params->lookup2(names::C_m);
  double conversion_factor = ConvertSynapseWeight(tau_m, tau_syn, C_m);
  std::cout << "conversion_factor " << conversion_factor << std::endl;
  double eta = brunel_params->lookup2(names::eta);
  double JE = brunel_params->lookup2("JE");
  double JE_pA = conversion_factor * JE;
  double V_th = iaf_psc_alpha_params->lookup2(names::V_th);

  double nu_thresh = V_th / ( CE * tau_m / C_m * JE_pA * exp(1.) * tau_syn);
  double nu_ext = nu_thresh * eta;

  DictionaryDatum poisson_generator_params(new Dictionary);
  poisson_generator_params->insert( names::rate, nu_ext * CE * 1000. );
  nest::register_poisson_generator();
  nest::set_model_defaults("poisson_generator", poisson_generator_params);
  poisson_generator_params->info(std::cout);
  nest::change_subnet(0);
  const nest::index generator_gid = nest::create("poisson_generator", 1);
  std::cout << "E_stimulus (generator) gid " << generator_gid << std::endl;
  GIDCollectionDatum e_stimulus = GIDCollection(generator_gid, generator_gid);
  e_stimulus.print_me(std::cout);

  DictionaryDatum p2(new Dictionary);
  p2->insert(names::delay, brunel_params->lookup2(names::delay));
  nest::register_synapses();
  //const nest::index static_synpase_gid = nest::create("static_synapse_hpc", 1);
  nest::set_model_defaults("static_synapse_hpc", p2);
  p2->info(std::cout);
  DictionaryDatum syn_std_params(new Dictionary);
  nest::copy_model("static_synapse_hpc", "syn_std", syn_std_params);

  DictionaryDatum syn_ex_params(new Dictionary);
  syn_ex_params->insert(names::weight, JE_pA);
  nest::copy_model("static_synapse_hpc", "syn_ex", syn_ex_params);

  DictionaryDatum syn_in_params(new Dictionary);
  syn_in_params->insert(names::weight, JE_pA * getValue<double>(brunel_params->lookup2(names::g)));
  nest::copy_model("static_synapse_hpc", "syn_in", syn_in_params);  

  stdp_params->insert(names::weight, JE_pA);
  nest::set_model_defaults("stdp_pl_synapse_hom_hpc", stdp_params);

  GIDCollectionDatum e_Neurons = GIDCollection(e_from, e_to);
  e_Neurons.print_me(std::cout);
  GIDCollectionDatum i_Neurons = GIDCollection(i_from, i_to);
  i_Neurons.print_me(std::cout);

  nest::index n_size = e_Neurons.size() + i_Neurons.size();
  std::cout << "total network size " << n_size << std::endl;
  DictionaryDatum conn_rule(new Dictionary);
  conn_rule->insert(names::rule, "all_to_all");
  DictionaryDatum conn_model(new Dictionary);
  conn_model->insert(names::model, "syn_ex");
  nest::connect(e_Neurons, e_stimulus, conn_rule, conn_model);

  conn_model->insert(names::model, "syn_in");
  //nest::connect(i_Neurons, e_Neurons, conn_rule, conn_model);
  
  nest::print_network(0, 6, std::cout);

  // presim stage
  nest::simulate(10);

  nest::simulate(10);

  return 0;
}
