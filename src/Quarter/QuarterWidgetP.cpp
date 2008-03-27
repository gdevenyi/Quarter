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

#include "QuarterWidgetP.h"

#include <Inventor/nodes/SoCamera.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/SoEventManager.h>
#include <Inventor/scxml/SoScXMLStateMachine.h>

#include <stdlib.h>

using namespace SIM::Coin3D::Quarter;

class QuarterWidgetP_cachecontext {
public:
  SbList <const QGLWidget *> widgetlist;
  uint32_t id;
};

static SbList <QuarterWidgetP_cachecontext *> * cachecontext_list = NULL;

QuarterWidgetP::QuarterWidgetP(QuarterWidget * masterptr, const QGLWidget * sharewidget)
{
  this->master = masterptr;
  this->cachecontext = findCacheContext(masterptr, sharewidget);
}

QuarterWidgetP::~QuarterWidgetP()
{
  this->cachecontext->widgetlist.removeItem((const QGLWidget*) this->master);
}

SoCamera *
QuarterWidgetP::searchForCamera(SoNode * root)
{
  SoSearchAction sa;
  sa.setInterest(SoSearchAction::FIRST);
  sa.setType(SoCamera::getClassTypeId());
  sa.apply(root);

  if (sa.getPath()) {
    SoNode * node = sa.getPath()->getTail();
    if (node && node->isOfType(SoCamera::getClassTypeId())) {
      return (SoCamera *) node;
    }
  }
  return NULL;
}

uint32_t
QuarterWidgetP::getCacheContextId(void) const
{
  return this->cachecontext->id;
}

QuarterWidgetP_cachecontext *
QuarterWidgetP::findCacheContext(QuarterWidget * widget, const QGLWidget * sharewidget)
{
  if (cachecontext_list == NULL) {
    // FIXME: static memory leak
    cachecontext_list = new SbList <QuarterWidgetP_cachecontext*>;
  }
  for (int i = 0; i < cachecontext_list->getLength(); i++) {
    QuarterWidgetP_cachecontext * cachecontext = (*cachecontext_list)[i];

    for (int j = 0; j < cachecontext->widgetlist.getLength(); j++) {
      if (cachecontext->widgetlist[j] == sharewidget) {
        cachecontext->widgetlist.append((const QGLWidget*) widget);
        return cachecontext;
      }
    }
  }
  QuarterWidgetP_cachecontext * cachecontext = new QuarterWidgetP_cachecontext;
  cachecontext->id = SoGLCacheContextElement::getUniqueCacheContext();
  cachecontext->widgetlist.append((const QGLWidget*) widget);
  cachecontext_list->append(cachecontext);

  return cachecontext;
}

void
QuarterWidgetP::prerendercb(void * userdata, SoRenderManager * manager)
{
  QuarterWidgetP * thisp = static_cast<QuarterWidgetP *>(userdata);
  SoEventManager * evman = thisp->soeventmanager;
  assert(evman);
  for (int c = 0; c < evman->getNumSoScXMLStateMachines(); ++c) {
    SoScXMLStateMachine * statemachine = evman->getSoScXMLStateMachine(c);
    statemachine->preGLRender();
  }
}

void
QuarterWidgetP::postrendercb(void * userdata, SoRenderManager * manager)
{
  QuarterWidgetP * thisp = static_cast<QuarterWidgetP *>(userdata);
  SoEventManager * evman = thisp->soeventmanager;
  assert(evman);
  for (int c = 0; c < evman->getNumSoScXMLStateMachines(); ++c) {
    SoScXMLStateMachine * statemachine = evman->getSoScXMLStateMachine(c);
    statemachine->postGLRender();
  }
}

void
QuarterWidgetP::statechangecb(void * userdata, ScXMLStateMachine * statemachine, const char * stateid, SbBool enter, SbBool)
{
  //QuarterWidgetP * thisp = static_cast<QuarterWidgetP *>(userdata);
  if (enter) {
    //SoDebugError::postInfo("QuarterWidget::stateChange",
    //                       "entering state '%s'", stateid);
  } else {
    //SoDebugError::postInfo("QuarterWidget::stateChange",
    //                       "exiting state '%s'", stateid);
  }
}

