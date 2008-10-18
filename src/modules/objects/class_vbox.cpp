//=============================================================================
//
//   File : class_vbox.cpp
//   Creation date : Fri Mar 18 14:30:48 CEST 2005
//   by Tonino Imbesi(Grifisx) and Alessandro Carbone(Noldor)
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2005-2008 Alessandro Carbone (elfonol at gmail dot com)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc. ,59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//=============================================================================

#define _KVI_DEBUG_CHECK_RANGE_
#include "kvi_debug.h"
#include "kvi_locale.h"

#include "class_vbox.h"

#include "kvi_tal_vbox.h"


// Tables used in $setAlignment & $alignment
const char * const align_tbl[] = {
			"Left", 
			"Right",
			"HCenter",
			"VCenter",
			"Center",
			"Top",
			"Bottom",
			"WordBreak"
			   };



const int align_cod[] = {
		Qt::AlignLeft,
		Qt::AlignRight,
	    Qt::AlignHCenter,
	    Qt::AlignVCenter,
	    Qt::AlignCenter,
	 	Qt::AlignTop,
	    Qt::AlignBottom,
	    Qt::AlignJustify,
	};

#define align_num	(sizeof(align_tbl) / sizeof(align_tbl[0]))
/*
	@doc: vbox
	@keyterms:
		vbox object class, child widgets
	@title:
		vbox class
	@type:
		class
	@short:
		Manages child widget vertical geometry
	@inherits:
		[class]object[/class]
	@description:
		The vbox class widget provides vertical geometry management for its child widgets.
	@functions:
		!fn: $setSpacing(<spacing:int>)
		Sets the default spacing of the widgets in pixels
		!fn: $setMargin(<margin:int>)
		Sets the dimension of the layout margin : the distance from the border to the outermost child widget edges.
		!fn: $setStretchFactor(<widget:hobject>,<stretch:uint>)
		Sets the stretch factor of widget to stretch.
		!fn: $addStretch(<stretch:integer>)
		Adds a stretchable space with zero minimum size and stretch factor stretch to the end of this box layout.
		!fn: $setAlignment(<flag1:string>, <flag2:string>, ...)
		Sets the alignment for widget w to  flags, given as parameters. 
		Valid flags are:Right,Left,Top,Bottom,HCenter,VCenter,Center  
*/


KVSO_BEGIN_REGISTERCLASS(KviKvsObject_vbox,"vbox","widget")
	KVSO_REGISTER_HANDLER_NEW(KviKvsObject_vbox,setMargin)
	KVSO_REGISTER_HANDLER_NEW(KviKvsObject_vbox,setSpacing)
	KVSO_REGISTER_HANDLER_NEW(KviKvsObject_vbox,setStretchFactor)
	KVSO_REGISTER_HANDLER_NEW(KviKvsObject_vbox,addStretch)
	KVSO_REGISTER_HANDLER_NEW(KviKvsObject_vbox,setAlignment)
KVSO_END_REGISTERCLASS(KviKvsObject_vbox)

KVSO_BEGIN_CONSTRUCTOR(KviKvsObject_vbox,KviKvsObject_widget)

KVSO_END_CONSTRUCTOR(KviKvsObject_vbox)


KVSO_BEGIN_DESTRUCTOR(KviKvsObject_vbox)

KVSO_END_CONSTRUCTOR(KviKvsObject_vbox)

bool KviKvsObject_vbox::init(KviKvsRunTimeContext * pContext,KviKvsVariantList *pParams)
{
	SET_OBJECT(KviTalVBox);
	return true;
}

KVSO_CLASS_FUNCTION(vbox,setMargin)
{
	kvs_int_t iMargin;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("margin",KVS_PT_INT,0,iMargin)
	KVSO_PARAMETERS_END(c)
	if (widget()) ((KviTalVBox *)widget())->setMargin(iMargin);
	return true;
}

KVSO_CLASS_FUNCTION(vbox,setSpacing)
{
	kvs_int_t iSpacing;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("spacing",KVS_PT_INT,0,iSpacing)
	KVSO_PARAMETERS_END(c)
	if (widget()) ((KviTalVBox *)widget())->setSpacing(iSpacing);
	return true;
}

KVSO_CLASS_FUNCTION(vbox,setStretchFactor)
{
	KviKvsObject * pObject;
	kvs_hobject_t hObject;
	kvs_uint_t uStretch;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("widget",KVS_PT_HOBJECT,0,hObject)
		KVSO_PARAMETER("stretch",KVS_PT_UNSIGNEDINTEGER,0,uStretch)
	KVSO_PARAMETERS_END(c)
	pObject=KviKvsKernel::instance()->objectController()->lookupObject(hObject);
	if(!widget())return true;
	CHECK_HOBJECT_IS_WIDGET(pObject)
	if(((KviKvsObject_widget *)pObject)->widget()->parentWidget() != widget())
	{
		c->warning(__tr2qs("The widget must be a child of this vbox"));
		return true;
	}
	((KviTalVBox *)widget())->setStretchFactor(((QWidget *)(pObject->object())),uStretch);
	return true;
}
KVSO_CLASS_FUNCTION(vbox,addStretch)
{
	kvs_int_t iStretch;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("stretch",KVS_PT_INT,0,iStretch)
	KVSO_PARAMETERS_END(c)
	
	if (widget())((KviTalVBox *)widget())->addStretch(iStretch);
	return true;
}
KVSO_CLASS_FUNCTION(vbox,setAlignment)
{
	QStringList alignment;
	KviKvsObject * pObject;
	kvs_hobject_t hObject;
	KVSO_PARAMETERS_BEGIN(c)
		KVSO_PARAMETER("widget",KVS_PT_HOBJECT,0,hObject)
		KVSO_PARAMETER("alignment",KVS_PT_STRINGLIST,KVS_PF_OPTIONAL,alignment)
	KVSO_PARAMETERS_END(c)
	pObject=KviKvsKernel::instance()->objectController()->lookupObject(hObject);
	if(!widget())return true;
	CHECK_HOBJECT_IS_WIDGET(pObject)
	if(((KviKvsObject_widget *)pObject)->widget()->parentWidget() != widget())
	{
		c->warning(__tr2qs("The widget must be a child of this hbox"));
		return true;
	}

	int align,sum=0;
	for ( QStringList::Iterator it = alignment.begin(); it != alignment.end(); ++it )
		{
		
			align = 0;
			for(unsigned int j = 0; j < align_num; j++)
			{
				if(KviQString::equalCI((*it), align_tbl[j]))
				{
					align=align_cod[j];
					break;
				}
			}
			if(align)
				sum = sum | align;
			else
				c->warning(__tr2qs("Unknown alignment: '%Q'"),&(*it));
			
		}
	if (widget()) ((KviTalHBox *)widget())->setAlignment(((QWidget *)(pObject->object())),(Qt::Alignment)sum);
	return true;
}

