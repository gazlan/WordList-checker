/* ******************************************************************** **
** @@ WhatsNewDlg
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#ifndef _LISTERDLG_HPP_
#define _LISTERDLG_HPP_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(push,1)
struct DB_RECORD
{
   DWORD       _dwCount;
   BYTE        _bySize;
   char        _pToken[1];
};
#pragma pack(pop)

#pragma pack(push,1)
struct DB_KEY
{
   DWORD       _pHashDigest[sizeof(DWORD) * 4];
   BYTE        _byExists;
};
#pragma pack(pop)

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

class CListerDlg : public CDialog
{
   private:

      MMF                  _Learn;
      MMF                  _Test;
      MMF                  _Map;
      BPPTreeIndex         _Index;
      char                 _pszTempIdx    [MAX_PATH + 1];
      char                 _pszTempDBLearn[MAX_PATH + 1];
      char                 _pszTempDBTest [MAX_PATH + 1];

   private:

      void     Cleanup();
      int      GetToken();
      void     LoadMap();
      void     Learn(HANDLE hDB);
      void     Check(HANDLE hDB);
      void     Report(const char* const pszIn,FILE* pOut);

// Construction
public:
   CListerDlg(CWnd* pParent = NULL); // standard constructor

// Dialog Data
   //{{AFX_DATA(CListerDlg)
   enum { IDD = IDD_LISTER };
   CProgressCtrl  m_Progress;
   CSpinButtonCtrl   m_SpMax;
   CSpinButtonCtrl   m_SpMin;
   UINT  m_Min;
   UINT  m_Max;
   CString  m_Src;
   CString  m_Out;
   CString  m_Map;
   CString  m_Test;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CListerDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   HICON m_hIcon;

   // Generated message map functions
   //{{AFX_MSG(CListerDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   virtual void OnCancel();
   afx_msg void OnBtnSrc();
   afx_msg void OnBtnOut();
   afx_msg void OnBtnMap();
   afx_msg void OnBtnGo();
   afx_msg void OnBtnTest();
   afx_msg void OnBtnLearn();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif

/* ******************************************************************** **
**                End of File
** ******************************************************************** */
