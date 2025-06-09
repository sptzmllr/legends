
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
#include "legends_grid.h"

#include <chrono>
#include <numeric>

#include "../lib/grid.h"


///////////////////////////////////////////////////////////
//														 //
//														 //
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
CLegends_Grid::CLegends_Grid(void)
{
	Set_Name		(_TL("Grid Tool"));

	Set_Author		("J. Spitzmueller (c) 2023");

	Set_Description	(_TW(
		"Tool to test a legends grid within a CSG_Tool"
	));

	Add_Reference(
		"Conrad, O., Bechtel, B., Bock, M., Dietrich, H., Fischer, E., Gerlitz, L., Wehberg, J., Wichmann, V., and Boehner, J.",
		"2015", "System for Automated Geoscientific Analyses (SAGA) v. 2.1.4",
		"Geosci. Model Dev., 8, 1991-2007.",
		SG_T("https://www.geosci-model-dev.net/8/1991/2015/gmd-8-1991-2015.html"), SG_T("doi:10.5194/gmd-8-1991-2015.")
	);

	Parameters.Add_Grid("",
		"GRID"	, _TL("Grid"),
		_TL(""), PARAMETER_INPUT
	);
}


///////////////////////////////////////////////////////////
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
int CLegends_Grid::On_Parameters_Enable(CSG_Parameters *pParameters, CSG_Parameter *pParameter)
{
	return( CSG_Tool::On_Parameters_Enable(pParameters, pParameter) );
}


///////////////////////////////////////////////////////////
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
bool CLegends_Grid::On_Execute(void)
{
	CSG_Grid* pGrid	= Parameters("GRID")->asGrid();

	//std::shared_ptr<lgnds::grid<double>> 	grid_ptr( new lgnds::grid<double>(pGrid) );

	std::shared_ptr<lgnds::grid<double>> test( new lgnds::grid<double>(pGrid) );


	auto start = std::chrono::steady_clock::now();

	double sum = 0.;
	for( size_t y=0; y<test->rows(); y++)
	{
		for( size_t x=0; x<test->rows(); x++)
		{
			sum += test->at(x,y);
	 	
	 	}
	}

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
	Message_Fmt( "Sum Legends x,y loop = %f in %f seconds\n", sum, elapsed_seconds );
	
	start = std::chrono::steady_clock::now();

	sum = 0.;
	//for( size_t y=0; y<test->rows(); y++)
	//{
	//	for( size_t x=0; x<test->rows(); x++)
	//	{
	//		sum += *test[x];
	// 	
	// 	}
	//}

	lgnds::grid<double> hallo( 101, 101);

	hallo[12][12] = 6.6;

    elapsed_seconds = end-start;
	Message_Fmt( "Sum Legends x,y loop = %f in %f seconds\n", sum, elapsed_seconds );

	start = std::chrono::steady_clock::now();


	//for( lgnds::grid<int>::iterator it= test->begin(); it != test->end(); it++ )
	//
	
	sum = 0.0;

	for( double& value : *test )
	{
		sum += value;
			
	}
    
	end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Legends range based for loop = %f in %f seconds\n", sum, elapsed_seconds );

	start = std::chrono::steady_clock::now();
	double sum2 = 0;
	for( sLong i=0; i<pGrid->Get_NCells(); i++ )
	{
		sum2+= pGrid->asDouble(i);

	}
	end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Saga = %f in %f seconds\n", sum2, elapsed_seconds );


	start = std::chrono::steady_clock::now();
	double sum3 = std::accumulate( test->begin(), test->end(), 0.);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Legends = %f in %f seconds\n", sum3, elapsed_seconds );


	start = std::chrono::steady_clock::now();
	double sum4 = 0;
	for( int x=0; x<pGrid->Get_NX(); x++ )
	{
		for( int y=0; y<pGrid->Get_NY(); y++ )
		{
			sum4+= pGrid->asDouble(x,y);
		}
	}
	end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Saga x,y = %f in %f seconds\n", sum4, elapsed_seconds );


	start = std::chrono::steady_clock::now();
	double sum5 = 0;
	for( int y=0; y<pGrid->Get_NY(); y++ )
	{
		for( int x=0; x<pGrid->Get_NX(); x++ )
		{
			sum5+= pGrid->asDouble(x,y);
		}
	}
	end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Saga y,x = %f in %f seconds\n", sum5, elapsed_seconds );

	//Message_Dlg(CSG_String::Format("%s: %f", _TL("Value"), Value), _TL("Hello World"));


	start = std::chrono::steady_clock::now();
	std::shared_ptr<lgnds::grid<float>> test2( new lgnds::grid<float>(pGrid) );
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Float casting needed %f seconds\n", elapsed_seconds );

	start = std::chrono::steady_clock::now();
	double sum6 = std::accumulate( test2->begin(), test2->end(), 0.);
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Legends = %f in %f seconds\n", sum6, elapsed_seconds );
	
	start = std::chrono::steady_clock::now();
	for( lgnds::grid<double>::iterator it=test->begin(); it != test->end(); it++ )
	{
		sum += *it;
	}
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end-start;
	Message_Fmt( "Sum Legends = %f in %f seconds\n", sum, elapsed_seconds );



	return( true );
}


///////////////////////////////////////////////////////////
//														 //
//														 //
//														 //
///////////////////////////////////////////////////////////

//---------------------------------------------------------
