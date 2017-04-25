
// CLIENT_IRIS_OFFICALDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CLIENT_IRIS_OFFICAL.h"
#include "CLIENT_IRIS_OFFICALDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <string.h>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCLIENT_IRIS_OFFICALDlg dialog

SOCKET m_hSocket;
const UINT MSG_ASYNC = WM_USER+1;
//const CString CRLF = "\r\n";
const int BUF_LEN = 255;
const int CMD_LEN = 5;


CCLIENT_IRIS_OFFICALDlg::CCLIENT_IRIS_OFFICALDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCLIENT_IRIS_OFFICALDlg::IDD, pParent)
	, SvName(_T(""))
	, Port(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCLIENT_IRIS_OFFICALDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, PIC_BOX, p1);
	DDX_Text(pDX, tbSvName, SvName);
	DDX_Text(pDX, tbPort, Port);
	DDX_Control(pDX, lbState, lbContentState);
	DDX_Control(pDX, IDC_EDIT1, lbtext);
	//  DDX_Control(pDX, LBinfo, LBinfo);
	DDX_Control(pDX, LBinfo, m_lbinfo);
}

BEGIN_MESSAGE_MAP(CCLIENT_IRIS_OFFICALDlg, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(MSG_ASYNC,OnAsyncSelect)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCLIENT_IRIS_OFFICALDlg::OnBnClickedButton1)
	ON_BN_CLICKED(btConnect, &CCLIENT_IRIS_OFFICALDlg::OnBnClickedbtconnect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(btFind, &CCLIENT_IRIS_OFFICALDlg::OnBnClickedbtfind)
END_MESSAGE_MAP()


// CCLIENT_IRIS_OFFICALDlg message handlers

BOOL CCLIENT_IRIS_OFFICALDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCLIENT_IRIS_OFFICALDlg::OnPaint()
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
HCURSOR CCLIENT_IRIS_OFFICALDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCLIENT_IRIS_OFFICALDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	static CString Filter = _T("image files (*.bmp; *.jpg) |*.bmp;*.jpg|All Files (*.*)|*.*||");    //Dinh dang file mo
	CFileDialog Load(TRUE, _T("*.avi"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, Filter, NULL); 

	if (Load.DoModal() == IDOK){
	
	
		file_name1 =  Load.GetPathName();
		CT2CA pszConvertedAnsiString(file_name1);
		string file_n1(pszConvertedAnsiString);
		file_n = file_n1;
		//std::string strStd(pszConvertedAnsiString);
	
	    //imwrite("hinh1.bmp", src1);
		/*LPCSTR pstr;
		pstr =  file_name1;*/
		HBITMAP bitmap1 = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), file_name1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		p1.SetBitmap(bitmap1);
	}


}
bool CCLIENT_IRIS_OFFICALDlg::ConnectToServer(const CString& sServerAdrress, int nServerPort)
{
	m_hSocket = socket(AF_INET,SOCK_STREAM,0);
	if(m_hSocket != INVALID_SOCKET)
	{
		SOCKADDR_IN sockAddr;
		int addrlen = sizeof(sockAddr);
		sockAddr.sin_family= AF_INET;
		sockAddr.sin_port =  htons(nServerPort);
		if(isalpha(sServerAdrress[0]))
		{
			PHOSTENT pHostEnt = gethostbyname((CStringA)sServerAdrress);
			if(pHostEnt)
			{
				memcpy(&sockAddr.sin_addr,pHostEnt->h_addr,4);

			}

		}
		else
		{
			sockAddr.sin_addr.s_addr = inet_addr((CStringA)sServerAdrress);

		}
		if(connect(m_hSocket,(LPSOCKADDR) &sockAddr,addrlen) ==  SOCKET_ERROR ||
			WSAAsyncSelect(m_hSocket,m_hWnd,MSG_ASYNC,FD_READ|FD_CLOSE) == SOCKET_ERROR)
		{
			closesocket(m_hSocket);
			m_hSocket= INVALID_SOCKET;
		}
		

	
	}

	return m_hSocket !=INVALID_SOCKET;
}


void CCLIENT_IRIS_OFFICALDlg::OnBnClickedbtconnect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(SvName != "")
	{
		if(ConnectToServer(SvName,Port))
		{
			lbContentState.AddString(_T("dang ket noi "));
		}
		else
			lbContentState.AddString(_T("ket noi that bai"));
	}
}
void CCLIENT_IRIS_OFFICALDlg::ReceiveData(void)
{
	char szBuffer[BUF_LEN + 1];
	int nRecvBytes = recv(m_hSocket,szBuffer,BUF_LEN,0);
	if(nRecvBytes > 0 )
	{
		szBuffer[nRecvBytes] = '\0';
		HandleResponse((CString)szBuffer);
	}
}
void  CCLIENT_IRIS_OFFICALDlg::HandleResponse(const CString& sResponse)
{
	m_lbinfo.ResetContent();
	int nTokenPos = 0;
	CString strToken = sResponse.Tokenize(_T(","), nTokenPos);
	string hehe[] = {"Ma NV : ", "Ho : ", "Ten : " , "Gioi tinh : ", "Ngay sinh : "};
	int i = 0;
	while (!strToken.IsEmpty())
	{
		CString straa ;
		straa.Format(_T("%S"),hehe[i].c_str());
		CString kq = straa + strToken;
		m_lbinfo.AddString(kq);
		strToken = sResponse.Tokenize(_T(","), nTokenPos);
		i++;
		
	}
	
}
LRESULT CCLIENT_IRIS_OFFICALDlg::OnAsyncSelect(WPARAM wParam, LPARAM lParam)
{
	if(WSAGETSELECTERROR(lParam)==0)
	{
		switch(WSAGETSELECTEVENT(lParam))
		{
		case FD_READ:
			ReceiveData();
			break;
		case FD_CLOSE:
			closesocket(m_hSocket);
			break;
		}
	}
	return LRESULT();
}

void CCLIENT_IRIS_OFFICALDlg::OnClose()
{
	SendData(_T("CLOS"));
	// TODO: Add your message handler code here and/or call default
	closesocket(m_hSocket);

	CDialogEx::OnClose();
}
bool CCLIENT_IRIS_OFFICALDlg::SendData(const CString& sData)
{
	return send(m_hSocket,(CStringA)sData,sData.GetLength(),0)!=SOCKET_ERROR;
}
int CCLIENT_IRIS_OFFICALDlg::UCLN(int a, int b)
{
	int r;
	while (b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
vector<double> CCLIENT_IRIS_OFFICALDlg::Haar(vector<double> data)
{
	vector<double> result;

	
		int value = 0;
		for(int i = 0; i < data.size() / 2; i++)
		{
			double m = ((double)data[value] + (double)data[value + 1]) / sqrt((double)2);

			value += 2;

			result.push_back(m);
		}
	
	return result;
}
vector<int> CCLIENT_IRIS_OFFICALDlg::GetCode(vector<double> source)
{
	vector<int> newCode;
	int value = 0;
	int i = 0;

	while (i < source.size())
	{
		if (source[i] - source[i + 1] >= 0)
			value = 1;
		else
			value = 0;

		newCode.push_back(value);

		i += 2;
	}

	return newCode;
}
vector<double> CCLIENT_IRIS_OFFICALDlg::Mat_toArray(Mat source)
{
	vector<double> result;
	
	for(int i = 0; i < source.rows; i++)
	{
		for(int j = 0; j < source.cols; j++)
		{
			result.push_back(source.at<uchar>(i, j));
		}
	}

	return result;
}

vector<int> CCLIENT_IRIS_OFFICALDlg::iriscode(String Path)
{

	Mat src;
	src = imread(Path, 1);

	// Nap anh, chuyen thanh anh muc xam

	//imshow("Before", src);
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);

	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	//imshow("GaussianBlur", gray);
	// Xac dinh Pupil , Iris
	vector<Vec3f> circles;

  
  HoughCircles(gray, circles, 3, 1, 10, 100, 30, 0, 49);
  if(circles.size() == 0)
  {
	  vector<int> a;
	  a.empty();
	  return a;
  }
	//HoughCircles(gray, circles, 3, 1, 10, 100, 30, 11, 49);
		
	double radius, r;
	Point center;

	center = Point(cvRound(circles[0][0]), cvRound(circles[0][1]));
	if (cvRound(circles[0][2]) < 70) // ktra la pupil hay iris
	{
		radius = cvRound(circles[0][2]);
		r = radius * 2.5;
	}
	else
	{
		r = cvRound(circles[0][2]);
		radius = r / 4;
	}
	circle(src, center, radius, Scalar(0, 0, 255), 2, 8, 0);

	circle(src, center, r, Scalar(0, 0, 255), 2, 8, 0);

// Lay diem tren duong tron, chuyen duong tron thanh duong thang
	double total = 360;
	double arc = 360 / total;
	double tmp = CV_PI / 4 + CV_PI / 2;
	double x, y;
	int numCircle = 24;
	double dist;
	int ucln = UCLN(r - radius, numCircle);
	/*if ((numCircle / ucln) % 2 == 0 || (numCircle / ucln) % 5 == 0)
		dist = (r - radius) / (double)numCircle;
	else
		dist = roundf(double(r - radius) / numCircle);*/

	dist = (r - radius) / ((double)(numCircle));
	//double tmp_r = radius;
	//vector< vector<Point> > Iris((int)(r - radius) / dist + 1, vector<Point>(total));
	vector< vector<Point> > Iris(numCircle, vector<Point>(total / 2));
	int m = 0, n = 0;

	bool flag = true;

	int count = 1; 

	while ((radius  + (count * dist)) <= r)
	{
		//tmp = CV_PI / 4;
		tmp = CV_PI / 4 + CV_PI / 2;
	//	while (tmp < 3 * CV_PI / 4 - 0.01)
		while (tmp < 3 * CV_PI / 4 - 0.01 + CV_PI / 2)
		{
			x = roundf((radius  + (count * dist)) * cos(tmp) + center.x);
			y = roundf((radius  + (count * dist)) * sin(tmp) + center.y);

			Iris[m][n] = Point(x, y);

			if (n < total / 4 - 1)
				n++;
			else
			{
				m++;
				n = 0;
			}

			tmp += (arc * CV_PI / 180);
		}
		//tmp_r += dist;
		count++;
	}

	//tmp_r = radius;
	m = 0;
	n = 90;
	count = 1;

	while ((radius  + (count * dist)) <= r)
	{
		tmp = 5 * CV_PI / 4 +  CV_PI / 2 ;
	//	tmp = CV_PI / 4 + CV_PI ;
		//while (tmp < 3 * CV_PI / 4 - 0.01 + CV_PI )	
		while (tmp < 7 * CV_PI / 4 - 0.01 + CV_PI / 2 )
		{
			x = roundf((radius  + (count * dist)) * cos(tmp) + center.x);
			y = roundf((radius  + (count * dist)) * sin(tmp) + center.y);

			Iris[m][n] = Point(x, y);

			if (n < total / 2 - 1)
				n++;
			else
			{
				m++;
				n = 90;
			}

			tmp += (arc * CV_PI / 180);
		}
		//tmp_r += dist;
		count++;
	}

	// Ve len anh
	for (int i = 0; i < Iris.size(); i++)
	{
		for (int j = 0; j < Iris[i].size(); j++)
			circle(src, Iris[i][j], 0, Scalar(0, 255, 255), 1, 8, 0);
	}
	//imwrite("D:\\src.bmp",src);
	//imshow("After", src);
	//cout << "So dong: " << Iris.size() << endl;
	//cout << "So cot: " << Iris[0].size() << endl;
	/*Mat binary;
	adaptiveThreshold(gray, binary, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 35, 5);*/
	int col, row;
 	row = Iris.size();
	col = Iris[0].size();
	Mat IrisCode_B(row, col, CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			try {
			IrisCode_B.at<uchar>(i, j) = gray.at<uchar>(Iris[i][j]);
			}
			catch( Exception ex)
			{
			//	tttt << Path << '\t' << i << '\t' << j << endl;	
				 vector<int> a;
				 a.empty();
				 return a;

			}
		}
			//IrisCode_B.at<uchar>(i, j) = (uchar) Iris[i][j];
	}
	//adaptiveThreshold(IrisCode_B, IrisCode_B, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 35, 5); // MAT ra binary
	//bitwise_not(IrisCode_B, IrisCode_B); // nghich dao mang
	//imshow("IrisCode", IrisCode_B);

	//..
	vector<double> IrisCode = Mat_toArray(IrisCode_B.clone());

	//IrisCode = Haar(IrisCode);

	//IrisCode = Haar(IrisCode);

	//IrisCode = Haar(IrisCode);
	vector<double> Haar1 , Haar2, Haar3;
//
	Haar1 = Haar(IrisCode);

	Haar2 = Haar(Haar1);
	
	Haar3 = Haar(Haar2);
	//imshow("Haar", IrisCode);

	//..
	vector<int> a = GetCode(Haar3);

	
	return a;


}
float CCLIENT_IRIS_OFFICALDlg::roundf(float x)
{
   return x >= 0.0f ? floorf(x + 0.5f) : ceilf(x - 0.5f);
}

void CCLIENT_IRIS_OFFICALDlg::OnBnClickedbtfind()
{
	// TODO: Add your control notification handler code here
	vector<int> a;
	a =	iriscode(file_n);
	
	
	string cs ;

	char ch;
	for (int i = 0; i < a.size(); i++) 
	{
		
		ch = '0' + a[i];
		cs += ch;

	}
	//cs+= '\0';
	CString CS;
	CS.Format(_T("%S"),cs.c_str());
	//lbContentState.AddString(CS);
	lbtext.SetWindowTextW(CS);
	SendData(CS);
	
	
	

}
