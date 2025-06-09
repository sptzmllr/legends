
///////////////////////////////////////////////////////////
//                                                       //
//                         SAGA                          //
//                                                       //
//      System for Automated Geoscientific Analyses      //
//                                                       //
//                     Tool Library:                     //
//                       my_tools                        //
//                                                       //
//-------------------------------------------------------//
//                                                       //
//                     my_tool.cpp                       //
//                                                       //
//                 Copyright (C) 2019 by                 //
//                      Hein Bloed                       //
//                                                       //
//-------------------------------------------------------//
//                                                       //
// This file is part of 'SAGA - System for Automated     //
// Geoscientific Analyses'. SAGA is free software; you   //
// can redistribute it and/or modify it under the terms  //
// of the GNU General Public License as published by the //
// Free Software Foundation, either version 2 of the     //
// License, or (at your option) any later version.       //
//                                                       //
// SAGA is distributed in the hope that it will be       //
// useful, but WITHOUT ANY WARRANTY; without even the    //
// implied warranty of MERCHANTABILITY or FITNESS FOR A  //
// PARTICULAR PURPOSE. See the GNU General Public        //
// License for more details.                             //
//                                                       //
// You should have received a copy of the GNU General    //
// Public License along with this program; if not, see   //
// <http://www.gnu.org/licenses/>.                       //
//                                                       //
//-------------------------------------------------------//
//                                                       //
//    e-mail:     hbloed@saga-gis.org                    //
//                                                       //
//    contact:    Hein Bloed                             //
//                Sesamestreet 42                        //
//                Metropolis                             //
//                Middle Earth                           //
//                                                       //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
#include "legends_layer.h"

#include "../lib/layer.h"


///////////////////////////////////////////////////////////
//														 //
//														 //
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
CLegends_Layer::CLegends_Layer(void)
{
	Set_Name		(_TL("Layer Tool"));

	Set_Author		("J. Spitzmueller (c) 2023");

	Set_Description	(_TW(
		"Tool to test a legends table within a CSG_Tool"
	));

	Add_Reference(
		"Conrad, O., Bechtel, B., Bock, M., Dietrich, H., Fischer, E., Gerlitz, L., Wehberg, J., Wichmann, V., and Boehner, J.",
		"2015", "System for Automated Geoscientific Analyses (SAGA) v. 2.1.4",
		"Geosci. Model Dev., 8, 1991-2007.",
		SG_T("https://www.geosci-model-dev.net/8/1991/2015/gmd-8-1991-2015.html"), SG_T("doi:10.5194/gmd-8-1991-2015.")
	);

	Parameters.Add_Shapes("",
		"SHAPES"	, _TL("Shapes"),
		_TL(""), PARAMETER_INPUT
	);
}


///////////////////////////////////////////////////////////
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
int CLegends_Layer::On_Parameters_Enable(CSG_Parameters *pParameters, CSG_Parameter *pParameter)
{
	return( CSG_Tool::On_Parameters_Enable(pParameters, pParameter) );
}


///////////////////////////////////////////////////////////
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
bool CLegends_Layer::On_Execute(void)
{
	CSG_Shapes* pShapes	= Parameters("SHAPES")->asShapes();

	std::shared_ptr<lgnds::layer> layer = std::make_shared<lgnds::layer>( pShapes );

	lgnds::point a = {4.,5.};

	lgnds::point<int> b = {1,2};



	//std::string test = lib_test.b_str();

	//lgnds::table test =Table lgnds::table (pTable);


	//for( int Field=0; Field<pTable->Get_Field_Count(); Field++ )
	//{}








	//Message_Dlg(CSG_String::Format("%s: %f", _TL("Value"), Value), _TL("Hello World"));

	return( true );
}


///////////////////////////////////////////////////////////
//														 //
//														 //
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
