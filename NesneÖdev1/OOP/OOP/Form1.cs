/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**				BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				   NESNEYE DAYALI PROGRAMLAMA DERSİ
**					2023-2024 BAHAR DÖNEMİ
**	
**				ÖDEV NUMARASI : 1
**				ÖĞRENCİ ADI : Eyüp Mutlu Erol
**				ÖĞRENCİ NUMARASI : B231210101
**              DERSİN ALINDIĞI GRUP : B
****************************************************************************/


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace OOP
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void yeniToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(Application.ProductName);
        }

        string kaydedilenYer = "";
        private void dosyaAçToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dosya = new OpenFileDialog();
            dosya.Filter = "txt Dosyaları|*.txt";
            DialogResult sonuc = dosya.ShowDialog();
            if (sonuc == DialogResult.OK)
            {
                kaydedilenYer = dosya.FileName;
                txtYazi.Text = File.ReadAllText(kaydedilenYer);
            }
        }

        void yeniyeKaydet()
        {
            SaveFileDialog dosya = new SaveFileDialog();
            dosya.Filter = "txt Dosyaları|*.txt";
            DialogResult sonuc = dosya.ShowDialog();
            if (sonuc == DialogResult.OK)
            {
                kaydedilenYer = dosya.FileName;
                mevcudaKaydet();
            }
        }
        void mevcudaKaydet()
        {
            File.WriteAllText(kaydedilenYer, txtYazi.Text);
        }

        private void dosyaKaydetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (File.Exists(kaydedilenYer))
            {
                DialogResult sonuc = MessageBox.Show("Yeni Konuma Kaydetmek İster Misiniz?", "Yeni Konum", MessageBoxButtons.YesNo);
                if (sonuc == DialogResult.Yes)
                {
                    yeniyeKaydet();
                }
                else if (sonuc == DialogResult.No)
                {
                    mevcudaKaydet();
                }
            }
            else
            {
                yeniyeKaydet();
            }
        }

        private void çıkışToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult cikis = MessageBox.Show("Programdan Çıkış Yapmak İstediğinize Emin Misiniz?", "Çıkış", MessageBoxButtons.YesNo);
            if (cikis == DialogResult.Yes)
            {
                Application.Exit();
            }
            else
            {
                MessageBox.Show("Çıkış İşlemi İptal Edildi");
            }
        }

        private void kesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtYazi.Cut();
        }

        private void kopyalaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtYazi.Copy();
        }

        private void yapıştırToolStripMenuItem_Click(object sender, EventArgs e)
        {
            txtYazi.Paste();
        }

        private void yazıBiçimiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fontDialog1.ShowDialog();
            txtYazi.Font= fontDialog1.Font;
        }

        private void yazıRengiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            txtYazi.ForeColor=colorDialog1.Color;
        }

        private void arkaPlanRengiToolStripMenuItem_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
            txtYazi.BackColor = colorDialog1.Color;
        }
    }
}


