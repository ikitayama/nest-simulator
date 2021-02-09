#include "spikeevent3.h"
#include "node.h"

#include "iaf_psc_alpha.h"


void
nest::SpikeEvent3::operator()()
{
	dynamic_cast<iaf_psc_alpha*>(receiver_)->handle(*this);
}

