#ifndef SPIKEEVENT3_H
#define SPIKEEVENT3_H

// C++ includes:
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>

// Includes from nestkernel:
#include "exceptions.h"
#include "nest_time.h"
#include "nest_types.h"
#include "vp_manager.h"

// Includes from sli:
#include "name.h"

namespace nest
{

class Node;

/**
 * Encapsulates information which is sent between Nodes.
 *
 * For each type of information there has to be a specialized event
 * class.
 *
 * Events are used for two tasks. During connection, they are used as
 * polymorphic connect objects. During simulation they are used to
 * transport basic event information from one node to the other.
 *
 * A connection between two elements is physically established in two
 * steps: First, create an event with the two envolved elements.
 * Second, call the connect method of the event.
 *
 * An event object contains only administrative information which is
 * needed to successfully deliver the event. Thus, event objects
 * cannot direcly contain custom data: events are not messages. If a
 * node receives an event, arbitrary abounts of data may be exchanged
 * between the participating nodes.

 * With this restriction it is possible to implement a comparatively
 * efficient event handling scheme. 5-6 function calls per event may
 * seem a long time, but this is cheap if we consider that event
 * handling makes update and communication succeptible to parallel
 * execution.
 *
 * @see Node
 * @see SpikeEvent
 * @see RateEvent
 * @see CurrentEvent
 * @see CurrentEvent
 * @see ConductanceEvent
 * @see GapJunctionEvent
 * @see InstantaneousRateConnectionEvent
 * @see DelayedRateConnectionEvent
 * @see DiffusionConnectionEvent
 * @ingroup event_interface
 */

class SpikeEvent3
{

public:
  SpikeEvent3();

  ~SpikeEvent3()
  {
  }

  /**
   * Virtual copy constructor.
   */
  //virtual SpikeEvent3* clone() const = 0;
  SpikeEvent3* clone() const;

  /**
   * Deliver the event to receiver.
   *
   * This operator calls the handler for the specific event type at
   * the receiver.
   */
  //virtual void operator()() = 0;
  void operator()();

  /**
   * Change pointer to receiving Node.
   */
  void set_receiver( Node& );

  /**
   * Return reference to receiving Node.
   */
  Node& get_receiver() const;

  /**
   * Return node ID of receiving Node.
   */
  index get_receiver_node_id() const;

  /**
   * Return reference to sending Node.
   */
  Node& get_sender() const;

  /**
   * Change pointer to sending Node.
   */
  void set_sender( Node& );

  /**
   * Return node ID of sending Node.
   */
  index get_sender_node_id() const;

  /**
   * Change node ID of sending Node.
   */
  void set_sender_node_id( index );

  /**
   * Return time stamp of the event.
   * The stamp denotes the time when the event was created.
   * The resolution of Stamp is limited by the time base of the
   * simulation kernel (@see class nest::Time).
   * If this resolution is not fine enough, the creation time
   * can be corrected by using the time attribute.
   */
  Time const& get_stamp() const;

  /**
   * Set the transmission delay of the event.
   * The delay refers to the time until the event is
   * expected to arrive at the receiver.
   * @param t delay.
   */

  void set_delay_steps( delay );

  /**
   * Return transmission delay of the event.
   * The delay refers to the time until the event is
   * expected to arrive at the receiver.
   */
  delay get_delay_steps() const;

  /**
   * Relative spike delivery time in steps.
   * Returns the delivery time of the spike relative to a given
   * time in steps.  Causality commands that the result should
   * not be negative.
   *
   * @returns stamp + delay - 1 - t in steps
   * @param Time reference time
   *
   * @see NEST Time Memo, Rule 3
   */
  long get_rel_delivery_steps( const Time& t ) const;

  /**
   * Return the sender port number of the event.
   * This function returns the number of the port over which the
   * Event was sent.
   * @retval A negative return value indicates that no port number
   * was available.
   */
  port get_port() const;

  /**
   * Return the receiver port number of the event.
   * This function returns the number of the r-port over which the
   * Event was sent.
   * @note A return value of 0 indicates that the r-port is not used.
   */
  rport get_rport() const;

  /**
   * Set the port number.
   * Each event carries the number of the port over which the event
   * is sent. When a connection is established, it receives a unique
   * ID from the sender. This number has to be stored in each Event
   * object.
   * @param p Port number of the connection, or -1 if unknown.
   */
  void set_port( port p );

  /**
   * Set the receiver port number (r-port).
   * When a connection is established, the receiving Node may issue
   * a port number (r-port) to distinguish the incomin
   * connection. By the default, the r-port is not used and its port
   * number defaults to zero.
   * @param p Receiver port number of the connection, or 0 if unused.
   */
  void set_rport( rport p );

  /**
   * Return the creation time offset of the Event.
   * Each Event carries the exact time of creation. This
   * time need not coincide with an integral multiple of the
   * temporal resolution. Rather, Events may be created at any point
   * in time.
   */
  double get_offset() const;

  /**
   * Set the creation time of the Event.
   * Each Event carries the exact time of creation in realtime. This
   * time need not coincide with an integral multiple of the
   * temporal resolution. Rather, Events may be created at any point
   * in time.
   * @param t Creation time in realtime. t has to be in [0, h).
   */
  void set_offset( double t );

  /**
   * Return the weight.
   */
  weight get_weight() const;

  /**
   * Set weight of the event.
   */
  void set_weight( weight t );

  /**
   * Set drift_factor of the event (see DiffusionConnectionEvent).
   */
  void set_drift_factor( weight ){};

  /**
   * Set diffusion_factor of the event (see DiffusionConnectionEvent).
   */
  void set_diffusion_factor( weight ){};

  /**
   * Returns true if the pointer to the sender node is valid.
   */
  bool sender_is_valid() const;

  /**
   * Returns true if the pointer to the receiver node is valid.
   */
  bool receiver_is_valid() const;

  /**
   * Check integrity of the event.
   * This function returns true, if all data, in particular sender
   * and receiver pointers are correctly set.
   */
  bool is_valid() const;

  /**
   * Set the time stamp of the event.
   * The time stamp refers to the time when the event
   * was created.
   */
  void set_stamp( Time const& );

protected:
  index sender_node_id_; //!< node ID of sender or -1.
                         /*
                          * The original formulation used references to Nodes as
                          * members, however, in order to avoid the reference of reference
                          * problem, we store sender and receiver as pointers and use
                          * references in the interface.
                          * Thus, we can still ensure that the pointers are never NULL.
                          */
  Node* sender_;         //!< Pointer to sender or NULL.
  Node* receiver_;       //!< Pointer to receiver or NULL.


  /**
   * Sender port number.
   * The sender port is used as a unique identifier for the
   * connection.  The receiver of an event can use the port number
   * to obtain data from the sender.  The sender uses this number to
   * locate target-specific information.  @note A negative port
   * number indicates an unknown port.
   */
  port p_;

  /**
   * Receiver port number (r-port).
   * The receiver port (r-port) can be used by the receiving Node to
   * distinguish incoming connections. E.g. the r-port number can be
   * used by Events to access specific parts of a Node. In most
   * cases, however, this port will no be used.
   * @note The use of this port number is optional.
   * @note An r-port number of 0 indicates that the port is not used.
   */
  rport rp_;

  /**
   * Transmission delay.
   * Number of simulations steps that pass before the event is
   * delivered at the receiver.
   * The delay must be at least 1.
   */
  delay d_;

  /**
   * Time stamp.
   * The time stamp specifies the absolute time
   * when the event shall arrive at the target.
   */
  Time stamp_;

  /**
   * Time stamp in steps.
   * Caches the value of stamp in steps for efficiency.
   * Needs to be declared mutable since it is modified
   * by a const function (get_rel_delivery_steps).
   */
  mutable long stamp_steps_;

  /**
   * Offset for precise spike times.
   * offset_ specifies a correction to the creation time.
   * If the resolution of stamp is not sufficiently precise,
   * this attribute can be used to correct the creation time.
   * offset_ has to be in [0, h).
   */
  double offset_;

  /**
   * Weight of the connection.
   */
  weight w_;



  void set_multiplicity( int );
  int get_multiplicity() const;

  int multiplicity_;
};




inline SpikeEvent3::SpikeEvent3()
  : multiplicity_( 1 )
{
}
/*

inline SpikeEvent*
SpikeEvent::clone() const
{
  return new SpikeEvent( *this );
}
*/

inline void
SpikeEvent3::set_multiplicity( int multiplicity )
{
  multiplicity_ = multiplicity;
}

inline int
SpikeEvent3::get_multiplicity() const
{
  return multiplicity_;
}

//*************************************************************
// Inline implementations.

inline bool
SpikeEvent3::sender_is_valid() const
{
  return sender_ != nullptr;
}

inline bool
SpikeEvent3::receiver_is_valid() const
{
  return receiver_ != nullptr;
}

inline bool
SpikeEvent3::is_valid() const
{
  return ( sender_is_valid() and receiver_is_valid() and ( d_ > 0 ) );
}

inline void
SpikeEvent3::set_receiver( Node& r )
{
  receiver_ = &r;
}

inline void
SpikeEvent3::set_sender( Node& s )
{
  sender_ = &s;
}

inline void
SpikeEvent3::set_sender_node_id( index node_id )
{
  sender_node_id_ = node_id;
}

inline Node&
SpikeEvent3::get_receiver( void ) const
{
  return *receiver_;
}

inline Node&
SpikeEvent3::get_sender( void ) const
{
  return *sender_;
}

inline index
SpikeEvent3::get_sender_node_id( void ) const
{
  assert( sender_node_id_ > 0 );
  return sender_node_id_;
}

inline weight
SpikeEvent3::get_weight() const
{
  return w_;
}

inline void
SpikeEvent3::set_weight( weight w )
{
  w_ = w;
}

inline Time const&
SpikeEvent3::get_stamp() const
{
  return stamp_;
}

inline void
SpikeEvent3::set_stamp( Time const& s )
{
  stamp_ = s;
  stamp_steps_ = 0; // setting stamp_steps to zero indicates
                    // stamp_steps needs to be recalculated from
                    // stamp_ next time it is needed (e.g., in
                    // get_rel_delivery_steps)
}

inline delay
SpikeEvent3::get_delay_steps() const
{
  return d_;
}

inline long
SpikeEvent3::get_rel_delivery_steps( const Time& t ) const
{
  if ( stamp_steps_ == 0 )
  {
    stamp_steps_ = stamp_.get_steps();
  }
  return stamp_steps_ + d_ - 1 - t.get_steps();
}

inline void
SpikeEvent3::set_delay_steps( delay d )
{
  d_ = d;
}

inline double
SpikeEvent3::get_offset() const
{
  return offset_;
}

inline void
SpikeEvent3::set_offset( double t )
{
  offset_ = t;
}

inline port
SpikeEvent3::get_port() const
{
  return p_;
}

inline rport
SpikeEvent3::get_rport() const
{
  return rp_;
}

inline void
SpikeEvent3::set_port( port p )
{
  p_ = p;
}

inline void
SpikeEvent3::set_rport( rport rp )
{
  rp_ = rp;
}
}

#endif // EVENT_H
