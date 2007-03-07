#ifndef QUARTER_COINWIDGET_H
#define QUARTER_COINWIDGET_H

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

#include <QGLWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <Inventor/SbBasic.h>
#include <Quarter/Basic.h>

class QKeyEvent;
class QGLContext;
class QMouseEvent;
class QDropEvent;
class QDragEnterEvent;

class SoNode;
class SoSceneManager;
class DeviceManager;

class QUARTER_DLL_API CoinWidget : public QGLWidget {
  typedef QGLWidget inherited;
  Q_OBJECT

public:
  CoinWidget(QWidget * parent = 0);
  CoinWidget(QGLContext * context, QWidget * parent = 0);
  ~CoinWidget();

  virtual SbBool setSceneGraph(SoNode * root);
  DeviceManager * getDeviceManager(void) const;

protected:
  virtual void resizeGL(int width, int height);
  virtual void initializeGL(void);
  virtual void paintGL(void);
  virtual bool event(QEvent * event);
  
  static void renderCB(void * closure, SoSceneManager * manager);

private:
  void constructor(void);
  friend class CoinWidgetP;
  class CoinWidgetP * pimpl;
};

#endif // QUARTER_COINWIDGET_H
