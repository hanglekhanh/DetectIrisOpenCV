
// CLIENT_IRIS_OFFICALDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <opencv2/opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;
// CCLIENT_IRIS_OFFICALDlg dialog
class CCLIENT_IRIS_OFFICALDlg : public CDialogEx
{
// Construction
public:
	CCLIENT_IRIS_OFFICALDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_IRIS_OFFICAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic p1;
	CString file_name1;

	Mat src1;
	
	string file_n;
	afx_msg void OnBnClickedButton1();
	bool ConnectToServer(const CString& sServerAdrress, int nServerPort);
	CString SvName;
	int Port;
	CListBox lbContentState;
	void ReceiveData(void);
	void HandleResponse(const CString& sResponse);
	LRESULT OnAsyncSelect(WPARAM wParam, LPARAM lParam);
	bool SendData(const CString& sData);
	int UCLN(int a, int b);
	//Mat Haar(Mat data, int interations);
	vector<double> Haar(vector<double> data);
	vector<int> GetCode(vector<double> source);
	vector<int> iriscode(String Path);
	//string iriscode(Mat scr);
	float roundf(float x);
	vector<double> Mat_toArray(Mat source);
	afx_msg void OnBnClickedbtconnect();
	afx_msg void OnClose();
	afx_msg void OnBnClickedbtfind();
	CEdit lbtext;
//	CListBox LBinfo;
	CListBox m_lbinfo;
};
