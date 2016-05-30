/**************************************************************************
** This file is part of LiteIDE
**
** Copyright (c) 2011-2016 LiteIDE Team. All rights reserved.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** In addition, as a special exception,  that plugins developed for LiteIDE,
** are allowed to remain closed sourced and can be distributed under any license .
** These rights are included in the file LGPL_EXCEPTION.txt in this package.
**
**************************************************************************/
// Module: filtermanager.cpp
// Creator: visualfc <visualfc@gmail.com>

#include "filtermanager.h"
#include <QToolBar>
#include <QComboBox>
//lite_memory_check_begin
#if defined(WIN32) && defined(_MSC_VER) &&  defined(_DEBUG)
     #define _CRTDBG_MAP_ALLOC
     #include <stdlib.h>
     #include <crtdbg.h>
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
#endif
//lite_memory_check_end

FilterManager::FilterManager()
{

}

bool FilterManager::initWithApp(IApplication *app)
{
    if (!IFilterManager::initWithApp(app)) {
        return false;
    }
    return true;
}

void FilterManager::createActions()
{
    m_filterToolBar = m_liteApp->actionManager()->loadToolBar("toolbar/filter");
    m_filterCombo = new QComboBox;
    m_filterCombo->setEditable(true);
    m_filterCombo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    m_filterToolBar->addWidget(m_filterCombo);
}

void FilterManager::addFilter(const QString &sym, IFilter *filter)
{
    m_filterMap.insert(sym,filter);
}

void FilterManager::removeFilter(IFilter *filter)
{
    QMutableMapIterator<QString,IFilter*> i(m_filterMap);
    while (i.hasNext()) {
        i.next();
        if (i.value() == filter) {
            m_filterMap.remove(i.key());
            break;
        }
    }
}

QList<IFilter *> FilterManager::filterList() const
{
    return m_filterMap.values();
}

void FilterManager::setCurrentFilter(IFilter *filter)
{
    m_currentFilter = filter;
}

IFilter *FilterManager::currentFilter() const
{
    return m_currentFilter;
}
