
// CLIENT_IRIS_OFFICAL.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCLIENT_IRIS_OFFICALApp:
// See CLIENT_IRIS_OFFICAL.cpp for the implementation of this class
//

class CCLIENT_IRIS_OFFICALApp : public CWinApp
{
public:
	CCLIENT_IRIS_OFFICALApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCLIENT_IRIS_OFFICALApp theApp;