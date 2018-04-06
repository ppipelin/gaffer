//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012-2013, John Haddon. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "boost/python.hpp"

#include "ContextAlgoBinding.h"
#include "SceneHierarchyBinding.h"
#include "ToolBinding.h"
#include "ViewBinding.h"
#include "VisualiserBinding.h"

#include "GafferSceneUI/SceneGadget.h"

#include "GafferUIBindings/GadgetBinding.h"

#include "GafferBindings/NodeBinding.h"

using namespace boost::python;
using namespace IECorePython;
using namespace GafferSceneUI;
using namespace GafferSceneUIModule;

namespace
{

GafferScene::ScenePlugPtr getScene( SceneGadget &g )
{
	return const_cast<GafferScene::ScenePlug *>( g.getScene() );
}

IECore::InternedStringVectorDataPtr objectAt( SceneGadget &g, IECore::LineSegment3f &l )
{
	IECore::InternedStringVectorDataPtr result = new IECore::InternedStringVectorData;
	if( g.objectAt( l, result->writable() ) )
	{
		return result;
	}
	return nullptr;
}

} // namespace

BOOST_PYTHON_MODULE( _GafferSceneUI )
{

	bindViews();
	bindTools();
	bindVisualisers();

	GafferUIBindings::GadgetClass<SceneGadget>()
		.def( init<>() )
		.def( "setScene", &SceneGadget::setScene )
		.def( "getScene", &getScene )
		.def( "setContext", &SceneGadget::setContext )
		.def( "getContext", (Gaffer::Context *(SceneGadget::*)())&SceneGadget::getContext, return_value_policy<CastToIntrusivePtr>() )
		.def( "setExpandedPaths", &SceneGadget::setExpandedPaths )
		.def( "getExpandedPaths", &SceneGadget::getExpandedPaths, return_value_policy<copy_const_reference>() )
		.def( "setMinimumExpansionDepth", &SceneGadget::setMinimumExpansionDepth )
		.def( "getMinimumExpansionDepth", &SceneGadget::getMinimumExpansionDepth )
		.def( "baseState", &SceneGadget::baseState, return_value_policy<CastToIntrusivePtr>() )
		.def( "objectAt", &objectAt )
		.def( "objectsAt", &SceneGadget::objectsAt )
		.def( "setSelection", &SceneGadget::setSelection )
		.def( "getSelection", &SceneGadget::getSelection, return_value_policy<copy_const_reference>() )
		.def( "selectionBound", &SceneGadget::selectionBound )
	;

	bindSceneHierarchy();
	bindContextAlgo();

}
