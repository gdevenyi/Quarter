/**************************************************************************\
 *
 *  This file is part of the SIM Quarter extension library for Coin.
 *  Copyright (C) 1998-2008 by Systems in Motion.  All rights reserved.
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

/*! \mainpage

  Quarter is a light-weight glue library that provides seamless
  integration between Systems in Motions's \COIN high-level 3D
  visualization library and Trolltech's \QT 2D user interface
  library.

  \QT and \COIN is a perfect match since they are both open source,
  widely portable and easy to use. Quarter has evolved from Systems in
  Motion's own experiences using \COIN and \QT together in our
  applications.

  The functionality in Quarter revolves around QuarterWidget, a
  subclass of QGLWidget. This widget provides functionality for
  rendering of Coin scenegraphs and translation of QEvents into
  SoEvents. Using this widget is as easy as using any other QWidget.

  \subpage QuarterWidgetPlugin

  Quarter also comes with a plugin for Qt Designer, Trolltech's tool
  for designing and building GUIs. Once you install Quarter, the
  QuarterWidget becomes accessible in Qt Designer, and you can include
  it in the user interfaces you create. The plugin facility also
  provides you with the capability of dynamically loading ui files
  containing a QuarterWidget in your application.

  By using \COIN, \QT and Quarter to build your 3D graphics
  applications, you have the power to write software that is portable
  across the whole range of UNIX, Linux, Microsoft Windows and Mac OS
  X operating systems, from a 100% common codebase.

  For a small, completely stand-alone usage example on how to
  initialize the library and set up a viewer instance window, see the
  following code:

  \code
  #include <Inventor/nodes/SoBaseColor.h>
  #include <Inventor/nodes/SoCone.h>
  #include <Inventor/nodes/SoSeparator.h>

  #include <Quarter/QuarterWidget.h>
  #include <Quarter/QuarterApplication.h>

  using namespace SIM::Coin3D::Quarter;

  int
  main(int argc, char ** argv)
  {
    // Initializes SoQt library (and implicitly also the Coin and Qt
    // libraries).
    QuarterApplication app(argc, argv);

    // Make a dead simple scene graph by using the Coin library, only
    // containing a single yellow cone under the scenegraph root.
    SoSeparator * root = new SoSeparator;
    root->ref();

    SoBaseColor * col = new SoBaseColor;
    col->rgb = SbColor(1, 1, 0);
    root->addChild(col);

    root->addChild(new SoCone);

    // Create a QuarterWidget for displaying a Coin scene graph
    QuarterWidget * viewer = new QuarterWidget;
    viewer->setSceneGraph(root);

    // Pop up the QuarterWidget
    viewer->show();
    // Loop until exit.
    app.exec();
    // Clean up resources.
    root->unref();
    delete viewer;

    return 0;
  }
  \endcode

  \subpage examples
*/

/*!
  \page examples More Examples

  The examples code is included in Quarter and can be found in the
  src/examples subdirectory.

  \subpage directui

  \subpage dynamicui

  \subpage inheritui

  \subpage mdi

  \subpage examiner
*/


#include <Inventor/SoDB.h>
#include <Inventor/nodekits/SoNodeKit.h>
#include <Inventor/SoInteraction.h>

#include <Quarter/Quarter.h>
#include "SensorManager.h"

#include "QuarterP.h"

using namespace SIM::Coin3D::Quarter;

static QuarterP * self = NULL;

/*!
  initialize Quarter, and implicitly Coin
 */
void
Quarter::init(bool initCoin)
{
  if (self) {
    fprintf(stderr, "Quarter is already initialized\n");
    return;
  }

  if (initCoin) {
    SoDB::init();
    SoNodeKit::init();
    SoInteraction::init();
  }

  self = new QuarterP;
  self->initCoin = initCoin;
  
}

/*!
  clean up resources
 */
void
Quarter::clean(void)
{
  assert(self);
  bool initCoin = self->initCoin;

  delete self;
  self = NULL;

  if (initCoin) {
    //NOTE: Copied this from SoQt 20080617 BFG
#if 0 // FIXME: These methods exist in TGS Inventor. We should add 
      // them, and then call them from here. 20060210 kyrah
    SoInteraction::finish();
    SoNodeKit::finish();
#endif
    SoDB::finish();
  }
}

/*!
  override lower refresh rate limit
 */
void
Quarter::setTimerEpsilon(double sec)
{
  if (!self) {
    fprintf(stderr, "Quarter is not initialized!\n");
    return;
  }

  self->sensormanager->setTimerEpsilon(sec);
}
