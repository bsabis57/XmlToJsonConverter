
// XmlJsonConverterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XmlJsonConverter.h"
#include "XmlJsonConverterDlg.h"
#include "afxdialogex.h"

#include "NameValueTree.h"
#include "ITreeReader.h"
#include "ITreeWriter.h"

#include <fstream>
#include <sstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXmlJsonConverterDlg dialog



CXmlJsonConverterDlg::CXmlJsonConverterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_XMLJSONCONVERTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXmlJsonConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXmlJsonConverterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_XML, &CXmlJsonConverterDlg::OnBnClickedReadXml)
	ON_BN_CLICKED(IDC_WRITE_JSON, &CXmlJsonConverterDlg::OnBnClickedWriteJson)
END_MESSAGE_MAP()


// CXmlJsonConverterDlg message handlers

BOOL CXmlJsonConverterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_WRITE_JSON)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXmlJsonConverterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXmlJsonConverterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// Command handler for Read XML button
void CXmlJsonConverterDlg::OnBnClickedReadXml()
{
	CFileDialog		fDlg(TRUE, NULL, NULL);

	// run a File Open Dialog and create the input xml stream
	if (fDlg.DoModal() == IDOK)
	{
		m_pathName = (LPCTSTR)fDlg.GetPathName();
		std::wstring			fileName = (LPCTSTR)fDlg.GetFileName();
		std::ifstream			xmlFile(m_pathName);
		std::wostringstream		sstrMsg;
		
		if (!xmlFile.good())
		{
			sstrMsg << fileName << L" - open file failed!";
		}

		else
		{
			// stream is good, instantiate an xml reader and the tree ...
			auto ptrReader = ITreeReader::NewXmlReader();
			m_ptrTree = std::make_shared<NameValueTree>();

			try
			{
				// ... and read the tree
				ptrReader->ReadTree(xmlFile, *m_ptrTree);
				sstrMsg << fileName << " - read ok.";
			}
			catch (ReaderException&)
			{
				m_ptrTree->clear();
				sstrMsg << fileName << " - parsing error!";
			}
			xmlFile.close();

			// enable / disable the output button
			GetDlgItem(IDC_WRITE_JSON)->EnableWindow(m_ptrTree->empty() ? FALSE : TRUE);
		}
		// Add results message
		GetDlgItem(IDC_INPUT)->SetWindowTextW(sstrMsg.str().c_str());
	}
}

// Command handler for Write JSON button
void CXmlJsonConverterDlg::OnBnClickedWriteJson()
{
	std::wstring			strJsonPath;
	std::wostringstream		sstrMsg;

	// find the extension on the filename (if it has one
	auto locX = m_pathName.find_last_of(L"\\.");
	if (locX == std::wstring::npos || m_pathName.at(locX) == L'\\') // no extension
		strJsonPath = m_pathName + L".json";
	else
		strJsonPath = m_pathName.substr(0, locX) +  L".json";

	// now run a File SaveAs dialog
	CFileDialog		fDlg(FALSE, NULL, strJsonPath.c_str());

	if (fDlg.DoModal() == IDOK)
	{
		std::wstring	fileName = (LPCTSTR)fDlg.GetFileName();
		std::ofstream	jsonFile(fDlg.GetPathName());
		if (!jsonFile.good())
			sstrMsg << fileName << L" - unable to open file!";

		else
		{
			try
			{
				// stream is good, instantiate a json writer ...
				auto ptrWriter = ITreeWriter::NewJsonWriter();
				// ... and write the tree
				ptrWriter->WriteTree(*m_ptrTree, jsonFile);
				sstrMsg << fileName << " - write ok.";
			}
			catch (WriterException&)
			{
				sstrMsg << fileName << " - writing error!";
			}

			jsonFile.close();
		}
		GetDlgItem(IDC_OUTPUT)->SetWindowTextW(sstrMsg.str().c_str());
	}
	return;


}
