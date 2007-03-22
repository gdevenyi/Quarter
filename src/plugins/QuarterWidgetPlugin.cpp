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

#include "QuarterWidgetPlugin.h"

#include <QtPlugin>
#include <Inventor/nodes/SoCube.h>
#include <Quarter/Quarter.h>
#include <Quarter/QuarterWidget.h>

namespace SIM { namespace Coin3D { namespace Quarter {

class QuarterWidgetPluginP {
public:
  QuarterWidgetPluginP(void) {}
  bool initialized;
};

}}} // namespace

using namespace SIM::Coin3D::Quarter;

#define PRIVATE(obj) obj->pimpl

QuarterWidgetPlugin::QuarterWidgetPlugin(QObject * parent)
  : QObject(parent)
{
  PRIVATE(this) = new QuarterWidgetPluginP;
  PRIVATE(this)->initialized = false;
}

QuarterWidgetPlugin::~QuarterWidgetPlugin()
{
  delete PRIVATE(this);
}

void 
QuarterWidgetPlugin::initialize(QDesignerFormEditorInterface *)
{
  if (PRIVATE(this)->initialized) {
    return;
  }

  Quarter::init();
  PRIVATE(this)->initialized = true;
}

bool 
QuarterWidgetPlugin::isInitialized(void) const
{
  return PRIVATE(this)->initialized;
}

QWidget *
QuarterWidgetPlugin::createWidget(QWidget * parent)
{
  QuarterWidget * widget = new QuarterWidget(parent);
  widget->setSceneGraph(new SoCube);
  return widget;
}

QString 
QuarterWidgetPlugin::name(void) const
{
  return "QuarterWidget";
}

QString 
QuarterWidgetPlugin::group(void) const
{
  return "Display Widgets [Coin3D]";
}

QIcon
QuarterWidgetPlugin::icon(void) const
{
  return QIcon();
}

QString 
QuarterWidgetPlugin::toolTip(void) const
{
  return "";
}

QString 
QuarterWidgetPlugin::whatsThis(void) const
{
  return "";
}

bool 
QuarterWidgetPlugin::isContainer(void) const
{
  return false;
}

QString 
QuarterWidgetPlugin::domXml(void) const
{
  return "<widget class=\"QuarterWidget\" name=\"QuarterWidget\">\n"
    " <property name=\"geometry\">\n"
    "  <rect>\n"
    "   <x>0</x>\n"
    "   <y>0</y>\n"
    "   <width>100</width>\n"
    "   <height>100</height>\n"
    "  </rect>\n"
    " </property>\n"
    " <property name=\"toolTip\" >\n"
    "  <string>QuarterWidget</string>\n"
    " </property>\n"
    " <property name=\"whatsThis\" >\n"
    "  <string>The QuarterWidget displays Open Inventor scene graphs.</string>\n"
    " </property>\n"
    "</widget>\n";
}

QString 
QuarterWidgetPlugin::includeFile(void) const
{
  return "QuarterWidget.h";
}

Q_EXPORT_PLUGIN2(quarterwidget, QuarterWidgetPlugin)

#undef PRIVATE
