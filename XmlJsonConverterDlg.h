// XmlJsonConverterDlg.h : header file
//

#pragma once
#include <memory>
#include "NameValueTree.h"

// CXmlJsonConverterDlg dialog
class CXmlJsonConverterDlg : public CDialogEx
{
// Construction
public:
	CXmlJsonConverterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XMLJSONCONVERTER_DIALOG };
#endif
public:
	afx_msg void OnBnClickedReadXml();
	afx_msg void OnBnClickedWriteJson();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


// Implementation
protected:
	HICON							m_hIcon;
	std::shared_ptr<NameValueTree>	m_ptrTree;
	std::wstring					m_pathName;

	// Generated message map functions
	DECLARE_MESSAGE_MAP()


};
