using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HastaneVeritabani_Arayuzu
{
    public partial class Hasta : Form
    {
        public Hasta()
        {
            InitializeComponent();
        }pgsqlConnection baglanti = new NpgsqlConnection("server=localHost; port=5432; Database=hastane; user ID=postgres; password=yns748596");
        private void bhListele_Click(object sender, EventArgs e)
        N
        {
            try
            {
                string sorgu = "select hasta.kisiid,ad,soyad,tckimlikno,cinsiyeti,kan,sigorta,boy,kilo,telefon,mail from hasta join insan on insan.kisiid = hasta.kisiid order by hasta.kisiid";
                NpgsqlDataAdapter da = new NpgsqlDataAdapter(sorgu, baglanti);
                DataSet ds = new DataSet();
                da.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
            }
            catch
            {
                MessageBox.Show("Lütfen geçerli bir giriş yapınız...");
            }

        }

        private void bhEkle_Click_1(object sender, EventArgs e)
        {
            try
            {
                baglanti.Open();
                NpgsqlCommand komut1 = new NpgsqlCommand("insert into insan(kisiid,ad,soyad,cinsiyeti,telefon,mail) values (@p1,@p2,@p3,@p4,@p5,@p6); insert into hasta(kisiid,boy,kilo,kan,sigorta,tckimlikno) values (@p7,@p8,@p9,@p10,@p11,@p12)", baglanti);
                komut1.Parameters.AddWithValue("@p1", int.Parse(txHastaid.Text));
                komut1.Parameters.AddWithValue("@p2", txAd.Text);
                komut1.Parameters.AddWithValue("@p3", txSoyad.Text);
                komut1.Parameters.AddWithValue("@p4", int.Parse(txCinsiyet.Text));
                komut1.Parameters.AddWithValue("@p5", txTel.Text);
                komut1.Parameters.AddWithValue("@p6", txMail.Text);
                komut1.Parameters.AddWithValue("@p7", int.Parse(txHastaid.Text));
                komut1.Parameters.AddWithValue("@p8", txBoy.Text);
                komut1.Parameters.AddWithValue("@p9", txKilo.Text);
                komut1.Parameters.AddWithValue("@p10", int.Parse(txKangrubu.Text));
                komut1.Parameters.AddWithValue("@p11", int.Parse(txSigorta.Text));
                komut1.Parameters.AddWithValue("@p12", txTc.Text);

                komut1.ExecuteNonQuery();
                baglanti.Close();
                MessageBox.Show("Hasta ekleme işlemi başarılı bir şekilde gerçekleşti.");
            }
            catch
            {
                MessageBox.Show("Lütfen geçerli bir giriş yapınız...");
            }
        }

        private void bhSil_Click_1(object sender, EventArgs e)
        {
            baglanti.Open();
            try
            {
                NpgsqlCommand komut2 = new NpgsqlCommand("delete from insan where kisiid=@p1", baglanti);
                komut2.Parameters.AddWithValue("@p1", int.Parse(txHastaid.Text));
                komut2.ExecuteNonQuery();
                MessageBox.Show("Hasta silme işlemi başarılı oldu.", "Bilgi", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
            catch
            {
                MessageBox.Show("Lütfen geçerli bir giriş yapınız...");
            }
            baglanti.Close();
        }

        private void bhGuncelle_Click_1(object sender, EventArgs e)
        {
            try
            {
                baglanti.Open();
                NpgsqlCommand komut3 = new NpgsqlCommand("update hasta set sigorta=@p1,boy=@p2,kilo=@p3 where kisiid=@p4", baglanti);

                komut3.Parameters.AddWithValue("@p1", int.Parse(txSigorta.Text));
                komut3.Parameters.AddWithValue("@p2", txBoy.Text);
                komut3.Parameters.AddWithValue("@p3", txKilo.Text);
                komut3.Parameters.AddWithValue("@p4", int.Parse(txHastaid.Text));
                komut3.ExecuteNonQuery();
                MessageBox.Show("Hasta güncelleme işlemi başarılı oldu.", "Bilgi", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                baglanti.Close();
            }
            catch
            {
                MessageBox.Show("Lütfen geçerli bir giriş yapınız...");
            }
        }
    }
}
