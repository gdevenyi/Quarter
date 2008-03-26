/**************************************************************************\
 *
 *  This file is part of the SIM Quarter extension library for Coin.
 *  Copyright (C) 1998-2007 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License ("GPL") version 2
 *  as published by the Free Software Foundation.  See the file COPYING
 *  at the root directory of this source distribution for additional
 *  information about the GNU GPL.
 *
 *  For using SIM Quarter with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits of
 *  our support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion AS, Bygd�y all� 5, N-0257 Oslo, NORWAY. (www.sim.no)
 *
\**************************************************************************/

/*!
  \class SIM::Coin3D::Quarter::QuarterApplication
  QuarterApplication.h
  Quarter/QuarterApplication.h

  \brief
  The QuarterApplication does not do anything particularly
  interesting, other than initialize Quarter in its constructor and
  deinitialize Quarter in its destructor.
*/


#include <Quarter/QuarterApplication.h>
#include <Quarter/Quarter.h>
#include "ImageReader.h"

using namespace SIM::Coin3D::Quarter;

/*!
  constructor
 */
QuarterApplication::QuarterApplication(int & argc, char ** argv)
  : inherited(argc, argv)
{
  Quarter::init();
  this->imagereader = new ImageReader;
}

/*!
  destructor
 */
QuarterApplication::~QuarterApplication()
{
  delete this->imagereader;
  Quarter::clean();
}
