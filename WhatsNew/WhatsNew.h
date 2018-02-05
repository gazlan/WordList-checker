/* ******************************************************************** **
** @@ Lister
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#if !defined(AFX_LISTER_H__978A3504_1AE7_437C_8C72_9DDF7BD346A3__INCLUDED_)
#define AFX_LISTER_H__978A3504_1AE7_437C_8C72_9DDF7BD346A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"      // main symbols

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */

/* ******************************************************************** **
** @@                   prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   Classes
** ******************************************************************** */

class CListerApp : public CWinApp
{
   private:

      HANDLE      _hMutex;

public:
   CListerApp();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CListerApp)
   public:
   virtual BOOL InitInstance();
   virtual int  ExitInstance();
   //}}AFX_VIRTUAL

// Implementation

   //{{AFX_MSG(CListerApp)
      // NOTE - the ClassWizard will add and remove member functions here.
      //    DO NOT EDIT what you see in these blocks of generated code !
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTER_H__978A3504_1AE7_437C_8C72_9DDF7BD346A3__INCLUDED_)

/* ******************************************************************** **
**                End of File
** ******************************************************************** */
