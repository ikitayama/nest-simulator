#include "spikeevent3.h"
#include "node.h"

#include "iaf_psc_alpha.h"

namespace nest
{
SpikeEvent3::SpikeEvent3()
  : sender_node_id_( 0 ) // initializing to 0 as this is an unsigned type
                         // node ID 0 is network, can never send an event, so
                         // this is safe
  , sender_( NULL )
  , receiver_( NULL )
  , p_( -1 )
  , rp_( 0 )
  , d_( 1 )
  , stamp_( Time::step( 0 ) )
  , stamp_steps_( 0 )
  , offset_( 0.0 )
  , w_( 0.0 )
{
}

void
SpikeEvent3::operator()()
{
	//dynamic_cast<iaf_psc_alpha*>(receiver_)->handle(*this);
	//receiver_->handle(*this);
        //printf("ddd\n");
}

}
