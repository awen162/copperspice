/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
* Copyright (c) 2012-2016 Digia Plc and/or its subsidiary(-ies).
* Copyright (c) 2008-2012 Nokia Corporation and/or its subsidiary(-ies).
*
* This file is part of CopperSpice.
*
* CopperSpice is free software. You can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License
* version 2.1 as published by the Free Software Foundation.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://www.gnu.org/licenses/
*
***********************************************************************/

#ifndef QSCRIPTDEBUGGERSTANDARDWIDGETFACTORY_P_H
#define QSCRIPTDEBUGGERSTANDARDWIDGETFACTORY_P_H

#include <QtCore/qobject.h>
#include <qscriptdebuggerwidgetfactoryinterface_p.h>

QT_BEGIN_NAMESPACE

class QScriptDebuggerStandardWidgetFactory : public QObject, public QScriptDebuggerWidgetFactoryInterface
{
 public:
   QScriptDebuggerStandardWidgetFactory(QObject *parent = nullptr);
   virtual ~QScriptDebuggerStandardWidgetFactory();

   QScriptDebugOutputWidgetInterface *createDebugOutputWidget();
   QScriptDebuggerConsoleWidgetInterface *createConsoleWidget();
   QScriptErrorLogWidgetInterface *createErrorLogWidget();
   QScriptDebuggerCodeFinderWidgetInterface *createCodeFinderWidget();
   QScriptDebuggerStackWidgetInterface *createStackWidget();
   QScriptDebuggerScriptsWidgetInterface *createScriptsWidget();
   QScriptDebuggerLocalsWidgetInterface *createLocalsWidget();
   QScriptDebuggerCodeWidgetInterface *createCodeWidget();
   QScriptBreakpointsWidgetInterface *createBreakpointsWidget();

 private:
   Q_DISABLE_COPY(QScriptDebuggerStandardWidgetFactory)
};

QT_END_NAMESPACE

#endif
