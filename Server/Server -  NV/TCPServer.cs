using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;


namespace Server____NV
{
    class TCPServer
    {
        public Socket m_listenSocket;
        private Server mainfrm;
        private Byte[] buffer = new Byte[1024];
        private Socket clientS ;
        bool checkconnect = false;
        bool state = true;

        DataClasses1DataContext db = new DataClasses1DataContext();
        public TCPServer(Server thefrm, int port)
        {
            try
            {
                mainfrm = thefrm;
                m_listenSocket = m_listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPEndPoint localEP = new IPEndPoint(IPAddress.Any, port);
                m_listenSocket.Bind(localEP);
                m_listenSocket.Listen(5);
                mainfrm.AddLbContent("Waiting Connect....... ");
                m_listenSocket.BeginAccept(new AsyncCallback(acceptConnect), null);
            }
            catch (SocketException ex )
            {
                
                throw ex ;
            }
        }

        public Person SoSanh(string code)
        {
            int percent = 0;
            var lPerson = from p in db.Persons
                            select p;

            if (lPerson != null && lPerson.Count() > 0)
            {
                double [] percentar = new double[100]; 
                string []manv = new string [100];
                int flag = 0;
                foreach (Person person in lPerson)
                {
                    percent = 0;
                    for (int i = 0; i < code.Length; i++)
                    {
                        if (person.IrisCode[i] == code[i])
                            percent++;
                    }

                    if (((double) percent / (double) code.Length)* 100 >= 65)
                    {
                        percentar[flag] = ((double) percent / (double) code.Length)* 100;
                        manv[flag] = person.MaNV;
                    }
                }
                double max = 0;
                int j = 0;
                for ( ; j < flag; j++)
                {
                    max = percentar[j];
                    if (max < percentar[j])
                    {
                        max = percentar[j];
                    }
                }
                foreach (Person person in lPerson)
                {
                    if (manv[j] == person.MaNV)
                        return person;
                }

            }

            return null;
        }

        protected void acceptConnect(IAsyncResult iar)
        {
            try
            {
               // NhanVien1 nv = new NhanVien1();
                Socket clientsocket = m_listenSocket.EndAccept(iar);
                // co thebegin típ dc 
                m_listenSocket.BeginAccept(new AsyncCallback(acceptConnect), null);
                checkconnect = true; 
                IPEndPoint remotEP = (IPEndPoint)clientsocket.RemoteEndPoint;
                IPHostEntry remoteHE = Dns.GetHostEntry(remotEP.Address);
                string sReport = string.Format("Co ket noi tu {0}({1} , {2})", remoteHE.HostName, remotEP.Address,remotEP.Port);
                state = true;
                mainfrm.AddLbContent(sReport);
                clientS = clientsocket;
               // clientsocket.Send(Encoding.ASCII.GetBytes("Chuc mung , Ban da ket noi dc vs server"));
                clientsocket.BeginReceive(buffer, 0, 1024, 0, new AsyncCallback(ReceivedData), clientsocket);

            }
            catch (SocketException ex)
            {
                
                throw ex  ;
            }
           
            
        }
        protected void ReceivedData(IAsyncResult iar)
        {
            try
            {
                //NhanVien1 nv = new NhanVien1();
                
                Socket clientsocket = (Socket)iar.AsyncState;
                Byte[] buff = buffer;
                int read = clientsocket.EndReceive(iar);
                string sRequest = Encoding.ASCII.GetString(buff,0,read);
                if (read > 0)
                {
                    HandleRequest(sRequest,clientsocket);   
                }
                if (state == true)
                {
                    clientsocket.BeginReceive(buffer, 0, 1024, 0, new AsyncCallback(ReceivedData), clientsocket);
                }
            }
            catch (SocketException ex )
            {
                
                throw ex ;
            }
        }
        protected void HandleRequest(string sRequest,Socket clientsocket)
        {
            string PureRequest = sRequest.Substring(0, 4);
            string Request = sRequest.Substring(4);

            IPEndPoint remotEP = (IPEndPoint)clientsocket.RemoteEndPoint;
            IPHostEntry remoteHE = Dns.GetHostEntry(remotEP.Address);
            if (PureRequest == "FIND")
            {
               // NhanVien1 nv = new NhanVien1();
                //char manv = nv.MaNV[0];
                
                //NhanVien NV = new NhanVienBus().GetFullInfo(Request);
                //if (NV == new NhanVien())
                //{
                //    string info = " ma nv ko hop le ";
                //    Byte[] hehe = Encoding.UTF8.GetBytes(info);
                //    clientsocket.Send(hehe);

                //}
                //else
                //{
                //    String info = string.Format("INFO{0},{1},{2},{3},{4},{5},{6},{7}", NV.MaNV, NV.Ho, NV.Ten, NV.NgaySinh, NV.GioiTinh, NV.DienThoai, NV.DiaChi, NV.ChucVu);
                //    Byte[] hehe = Encoding.UTF8.GetBytes(info);
                //    clientsocket.Send(hehe);
                //}
            }
            else if (PureRequest == "CLOS")
            {
             
                string sReport = string.Format("Co dong ket  noi tu {0}({1} , {2})", remoteHE.HostName, remotEP.Address, remotEP.Port);
                mainfrm.AddLbContent(sReport);
                clientsocket.Close();
                state = false;
                checkconnect = false;
             //   m_listenSocket.BeginAccept(new AsyncCallback(acceptConnect), null);
            }
            else
            {
                mainfrm.AddLbContent(remoteHE.HostName +" : "  + sRequest);
                Person p1 = SoSanh(sRequest);
                if (p1 == null)
                {
                    clientsocket.Send(Encoding.ASCII.GetBytes("Not Found"));
                }
                else
                {
                    //string s = p1.MaNV;
                    string s = p1.MaNV + "," + p1.Ho + "," + p1.Ten + "," + p1.GioiTinh + "," + p1.NgaySinh;
                    clientsocket.Send(Encoding.ASCII.GetBytes(s));
                  
                }
                   
            }
        }
        public void RequestClose()
        {
            if (checkconnect == true )
                 clientS.Send(Encoding.ASCII.GetBytes("CLOS"));
        }
    }
}
