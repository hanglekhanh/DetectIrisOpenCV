using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;



namespace Server____NV
{
    public partial class Server : Form
    {
        TCPServer tcp;
        public Server()
        {
            InitializeComponent();
        }

        //private int Compare(string chuoi)
        //{
        //    return 0;
        //}

        private void Server_Load(object sender, EventArgs e)
        {
            DataClasses1DataContext db = new DataClasses1DataContext();
            List<Person> a = (from b in db.Persons
                                    select b).ToList<Person>();

            //foreach (var b in a)
            //{
            //    string code = b.MaNV;
            //    int kq = Compare(code);
            //    if(kq > 60)
                    
            //}
            List<Person> list1 =  a;
            //List<NhanVien> list = new NhanVienBus().GetNV();
            //List<NhanVien> hehe = list;
            DGVNhanVien.DataSource = list1;
            tcp = new TCPServer(this, 2015);
        }
        delegate void SetTextCallback(string text);
        public void AddLbContent(String text)
        {
            if (this.lbContent.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(AddLbContent);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.lbContent.Items.Add(text);
            }
        }

        private void Server_FormClosed(object sender, FormClosedEventArgs e)
        {
            tcp.RequestClose();
        }


    }
}
