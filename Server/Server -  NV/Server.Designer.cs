namespace Server____NV
{
    partial class Server
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lbContent = new System.Windows.Forms.ListBox();
            this.DGVNhanVien = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.DGVNhanVien)).BeginInit();
            this.SuspendLayout();
            // 
            // lbContent
            // 
            this.lbContent.FormattingEnabled = true;
            this.lbContent.Location = new System.Drawing.Point(497, 12);
            this.lbContent.Name = "lbContent";
            this.lbContent.Size = new System.Drawing.Size(366, 69);
            this.lbContent.TabIndex = 0;
            // 
            // DGVNhanVien
            // 
            this.DGVNhanVien.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DGVNhanVien.Location = new System.Drawing.Point(12, 87);
            this.DGVNhanVien.Name = "DGVNhanVien";
            this.DGVNhanVien.Size = new System.Drawing.Size(851, 404);
            this.DGVNhanVien.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(163)));
            this.label1.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(478, 68);
            this.label1.TabIndex = 3;
            this.label1.Text = "Server System";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Server
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(874, 500);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DGVNhanVien);
            this.Controls.Add(this.lbContent);
            this.Name = "Server";
            this.Text = "Server";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Server_FormClosed);
            this.Load += new System.EventHandler(this.Server_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DGVNhanVien)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lbContent;
        private System.Windows.Forms.DataGridView DGVNhanVien;
        private System.Windows.Forms.Label label1;
    }
}

