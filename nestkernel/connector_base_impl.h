/*
 *  connector_base_impl.h
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

#include "connector_base.h"

// Includes from nestkernel:
#include "kernel_manager.h"

#ifndef CONNECTOR_BASE_IMPL_H
#define CONNECTOR_BASE_IMPL_H

namespace nest
{

template < typename ConnectionT >
void
Connector< ConnectionT >::send_weight_event( const thread tid,
  const unsigned int lcid,
  Event& e,
  const CommonSynapseProperties& cp )
{
  // If the pointer to the receiver node in the event is invalid,
  // the event was not sent, and a WeightRecorderEvent is therefore not created.
  if ( cp.get_weight_recorder() and e.receiver_is_valid() )
  {
    wr_e.set_receiver( *cp.get_weight_recorder()->get_thread_sibling( tid ) );
    // Put the gid of the postsynaptic node as receiver gid
    wr_e.set_receiver_gid( e.get_receiver().get_gid() );*/
    //wr_e();
  }
}

template < typename ConnectionT >
void
Connector< ConnectionT >::send_weight_event1( const thread tid,
  const unsigned int lcid,
  Event& e,
  const CommonSynapseProperties& cp, index* source_id, WeightRecorderEvent& wr_e )
{
  // Comment:
  // cp.get_weight_recorder() always returns false
  // e.get_receiver().get_gid leads to a runtime failure

  if ( cp.get_weight_recorder() )
  {
    index wr_node_id = cp.get_wr_node_id();
    Node* wr_node = kernel().node_manager.get_node_or_proxy( wr_node_id, tid );
    wr_e.set_receiver( *wr_node );
    // Put the node_id of the postsynaptic node as receiver node ID
    wr_e.set_receiver_node_id( e.get_receiver_node_id() );
    wr_e();
  }
}

} // of namespace nest

#endif
