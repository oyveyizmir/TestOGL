
// TestOGL.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTestOGLApp:
// See TestOGL.cpp for the implementation of this class
//

class CTestOGLApp : public CWinApp
{
public:
	CTestOGLApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTestOGLApp theApp;