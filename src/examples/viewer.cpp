/**************************************************************************\
 *
 *  This file is part of the SIM Quarter extension library for Coin.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License ("GPL") version 2
 *  as published by the Free Software Foundation.  See the file COPYING
 *  at the root directory of this source distribution for additional
 *  information about the GNU GPL.
 *
 *  For using SIM Nuts'n'Bolts with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits of
 *  our support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion AS, Bygd�y all� 5, N-0257 Oslo, NORWAY. (www.sim.no)
 *
\**************************************************************************/

#include <QUiLoader>
#include <QFile>
#include <Quarter/CoinWidget.h>
#include <Quarter/CoinApplication.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCone.h>

int main(int argc, char *argv[])
{
  CoinApplication app(argc, argv);

  QFile file("coinwidget.ui");
  if (!file.open(QFile::ReadOnly)) {
    assert(0 && "could not open ui file");
  }
  QUiLoader loader;
  QWidget * widget = loader.load(&file);
  assert(widget);
  file.close();

  CoinWidget * viewer = qFindChild<CoinWidget *>(widget, "CoinWidget");
  assert(viewer);
  viewer->setSceneGraph(new SoCone);

  widget->show();  
  return app.exec();
}
