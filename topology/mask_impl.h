/*
 *  mask_impl.h
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

#ifndef MASK_IMPL_H
#define MASK_IMPL_H

#include "mask.h"

namespace nest
{

template < int D >
AbstractMask*
Mask< D >::intersect_mask( const AbstractMask& other ) const
{
  const Mask* other_d = dynamic_cast< const Mask* >( &other );
  if ( other_d == 0 )
  {
    throw BadProperty( "Masks must have same number of dimensions." );
  }
  return new IntersectionMask< D >( *this, *other_d );
}

template < int D >
AbstractMask*
Mask< D >::union_mask( const AbstractMask& other ) const
{
  const Mask* other_d = dynamic_cast< const Mask* >( &other );
  if ( other_d == 0 )
  {
    throw BadProperty( "Masks must have same number of dimensions." );
  }
  return new UnionMask< D >( *this, *other_d );
}

template < int D >
AbstractMask*
Mask< D >::minus_mask( const AbstractMask& other ) const
{
  const Mask* other_d = dynamic_cast< const Mask* >( &other );
  if ( other_d == 0 )
  {
    throw BadProperty( "Masks must have same number of dimensions." );
  }
  return new DifferenceMask< D >( *this, *other_d );
}

template < int D >
bool
Mask< D >::inside( const std::vector< double >& pt ) const
{
  return inside( Position< D >( pt ) );
}

template < int D >
bool
Mask< D >::outside( const Box< D >& b ) const
{
  Box< D > bb = get_bbox();
  for ( int i = 0; i < D; ++i )
  {
    if ( ( b.upper_right[ i ] < bb.lower_left[ i ] )
      || ( b.lower_left[ i ] > bb.upper_right[ i ] ) )
      return true;
  }
  return false;
}

template < int D >
bool
BoxMask< D >::inside( const Position< D >& p ) const
{
  return ( p >= lower_left_ ) && ( p <= upper_right_ );
}

template < int D >
bool
BoxMask< D >::inside( const Box< D >& b ) const
{
  return ( b.lower_left >= lower_left_ ) && ( b.upper_right <= upper_right_ );
}

template < int D >
bool
BoxMask< D >::outside( const Box< D >& b ) const
{
  for ( int i = 0; i < D; ++i )
  {
    if ( ( b.upper_right[ i ] < lower_left_[ i ] )
      || ( b.lower_left[ i ] > upper_right_[ i ] ) )
      return true;
  }
  return false;
}

template < int D >
Box< D >
BoxMask< D >::get_bbox() const
{
  return Box< D >( lower_left_, upper_right_ );
}

template < int D >
Mask< D >*
BoxMask< D >::clone() const
{
  return new BoxMask( *this );
}

template < int D >
DictionaryDatum
BoxMask< D >::get_dict() const
{
  DictionaryDatum d( new Dictionary );
  DictionaryDatum maskd( new Dictionary );
  def< DictionaryDatum >( d, get_name(), maskd );
  def< std::vector< double > >( maskd, names::lower_left, lower_left_ );
  def< std::vector< double > >( maskd, names::upper_right, upper_right_ );
  return d;
}

template < int D >
bool
BallMask< D >::inside( const Position< D >& p ) const
{
  return ( p - center_ ).length() <= radius_;
}

template < int D >
bool
BallMask< D >::outside( const Box< D >& b ) const
{
  // Currently only checks if the box is outside the bounding box of
  // the ball. This could be made more refined.
  for ( int i = 0; i < D; ++i )
  {
    if ( ( b.upper_right[ i ] < center_[ i ] - radius_ )
      || ( b.lower_left[ i ] > center_[ i ] + radius_ ) )
      return true;
  }
  return false;
}

template < int D >
Box< D >
BallMask< D >::get_bbox() const
{
  Box< D > bb( center_, center_ );
  for ( int i = 0; i < D; ++i )
  {
    bb.lower_left[ i ] -= radius_;
    bb.upper_right[ i ] += radius_;
  }
  return bb;
}

template < int D >
Mask< D >*
BallMask< D >::clone() const
{
  return new BallMask( *this );
}

template < int D >
DictionaryDatum
BallMask< D >::get_dict() const
{
  DictionaryDatum d( new Dictionary );
  DictionaryDatum maskd( new Dictionary );
  def< DictionaryDatum >( d, get_name(), maskd );
  def< double >( maskd, names::radius, radius_ );
  def< std::vector< double > >( maskd, names::anchor, center_ );
  return d;
}

template < int D >
bool
IntersectionMask< D >::inside( const Position< D >& p ) const
{
  return mask1_->inside( p ) && mask2_->inside( p );
}

template < int D >
bool
IntersectionMask< D >::inside( const Box< D >& b ) const
{
  return mask1_->inside( b ) && mask2_->inside( b );
}

template < int D >
bool
IntersectionMask< D >::outside( const Box< D >& b ) const
{
  return mask1_->outside( b ) || mask2_->outside( b );
}

template < int D >
Box< D >
IntersectionMask< D >::get_bbox() const
{
  Box< D > bb = mask1_->get_bbox();
  Box< D > bb2 = mask2_->get_bbox();
  for ( int i = 0; i < D; ++i )
  {
    if ( bb2.lower_left[ i ] > bb.lower_left[ i ] )
      bb.lower_left[ i ] = bb2.lower_left[ i ];
    if ( bb2.upper_right[ i ] < bb.upper_right[ i ] )
      bb.upper_right[ i ] = bb2.upper_right[ i ];
  }
  return bb;
}

template < int D >
Mask< D >*
IntersectionMask< D >::clone() const
{
  return new IntersectionMask( *this );
}

template < int D >
bool
UnionMask< D >::inside( const Position< D >& p ) const
{
  return mask1_->inside( p ) || mask2_->inside( p );
}

template < int D >
bool
UnionMask< D >::inside( const Box< D >& b ) const
{
  return mask1_->inside( b ) || mask2_->inside( b );
}

template < int D >
bool
UnionMask< D >::outside( const Box< D >& b ) const
{
  return mask1_->outside( b ) && mask2_->outside( b );
}

template < int D >
Box< D >
UnionMask< D >::get_bbox() const
{
  Box< D > bb = mask1_->get_bbox();
  Box< D > bb2 = mask2_->get_bbox();
  for ( int i = 0; i < D; ++i )
  {
    if ( bb2.lower_left[ i ] < bb.lower_left[ i ] )
      bb.lower_left[ i ] = bb2.lower_left[ i ];
    if ( bb2.upper_right[ i ] > bb.upper_right[ i ] )
      bb.upper_right[ i ] = bb2.upper_right[ i ];
  }
  return bb;
}

template < int D >
Mask< D >*
UnionMask< D >::clone() const
{
  return new UnionMask( *this );
}

template < int D >
bool
DifferenceMask< D >::inside( const Position< D >& p ) const
{
  return mask1_->inside( p ) && !mask2_->inside( p );
}

template < int D >
bool
DifferenceMask< D >::inside( const Box< D >& b ) const
{
  return mask1_->inside( b ) && mask2_->outside( b );
}

template < int D >
bool
DifferenceMask< D >::outside( const Box< D >& b ) const
{
  return mask1_->outside( b ) || mask2_->inside( b );
}

template < int D >
Box< D >
DifferenceMask< D >::get_bbox() const
{
  return mask1_->get_bbox();
}

template < int D >
Mask< D >*
DifferenceMask< D >::clone() const
{
  return new DifferenceMask( *this );
}

template < int D >
bool
ConverseMask< D >::inside( const Position< D >& p ) const
{
  return m_->inside( -p );
}

template < int D >
bool
ConverseMask< D >::inside( const Box< D >& b ) const
{
  return m_->inside( Box< D >( -b.upper_right, -b.lower_left ) );
}

template < int D >
bool
ConverseMask< D >::outside( const Box< D >& b ) const
{
  return m_->outside( Box< D >( -b.upper_right, -b.lower_left ) );
}

template < int D >
Box< D >
ConverseMask< D >::get_bbox() const
{
  Box< D > bb = m_->get_bbox();
  return Box< D >( -bb.upper_right, -bb.lower_left );
}

template < int D >
Mask< D >*
ConverseMask< D >::clone() const
{
  return new ConverseMask( *this );
}

template < int D >
bool
AnchoredMask< D >::inside( const Position< D >& p ) const
{
  return m_->inside( p - anchor_ );
}

template < int D >
bool
AnchoredMask< D >::inside( const Box< D >& b ) const
{
  return m_->inside(
    Box< D >( b.lower_left - anchor_, b.upper_right - anchor_ ) );
}

template < int D >
bool
AnchoredMask< D >::outside( const Box< D >& b ) const
{
  return m_->outside(
    Box< D >( b.lower_left - anchor_, b.upper_right - anchor_ ) );
}

template < int D >
Box< D >
AnchoredMask< D >::get_bbox() const
{
  Box< D > bb = m_->get_bbox();
  return Box< D >( bb.lower_left + anchor_, bb.upper_right + anchor_ );
}

template < int D >
Mask< D >*
AnchoredMask< D >::clone() const
{
  return new AnchoredMask( *this );
}

template < int D >
DictionaryDatum
AnchoredMask< D >::get_dict() const
{
  DictionaryDatum d = m_->get_dict();
  def< std::vector< double > >( d, names::anchor, anchor_ );
  return d;
}

} // namespace nest

#endif
