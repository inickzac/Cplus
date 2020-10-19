using System;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CIPHER
{
    public partial class Form1 : Form
    {
       
        SaveFileDialog saveFileDial = new SaveFileDialog();
        OpenFileDialog openCryptfile = new OpenFileDialog();
        SaveFileDialog keySaveDial = new SaveFileDialog();
        OpenFileDialog keyOpenFile = new OpenFileDialog();

        public Form1()
        {
         
            InitializeComponent();           
            cryptButtom.Enabled = false;
           
            panelProgress.Visible = false;
            // Значение ключей по умолчанию          
            

        }

          
      

        private void OpenFileButtom_Click(object sender, EventArgs e)  //Диалог открытия файла
        {
            
            if(openCryptfile.ShowDialog()==DialogResult.OK)
            {
                pathTextBox.Text = openCryptfile.FileName;

                    cryptButtom.Enabled = true;
               
            }
        }

        private void CryptButtom_Click(object sender, EventArgs e)  //Шифруем файл 
        {
            CreateAndStartThreadHiper(1);
        }

        private void DeciperButton_Click(object sender, EventArgs e)  //дешифруем файл 
        {
            CreateAndStartThreadHiper(2);
        }

        public async void CreateAndStartThreadHiper(int par) 
        {
            try
            {
                GenKeytextBox.Text = "";
                genTextKeylabel.Text = "";
                byte[] key = null;
                var reg = new Regex(@"(^\d+| \d+)");
                var byteStringCol = reg.Matches(KeytextBox.Text);

                key = new byte[byteStringCol.Count];
                for (int i = 0; i < byteStringCol.Count; i++)
                {
                    genTextKeylabel.Text += byteStringCol[i].Value + " ";
                    int keyint = Int32.Parse(byteStringCol[i].Value);
                    if (keyint > 255)
                    {
                        throw new Exception("Введите числа от 1 до 255 через пробел");
                    }
                    key[i] = Byte.Parse(byteStringCol[i].Value);
                }


                RC4 rc4 = new RC4(key);

                rc4.secKeyBite += (strKey) => {
                    Action textkey = () => GenKeytextBox.Text += strKey + " ";
                    if (InvokeRequired) Invoke(textkey);
                    else textkey();


                };
                panelProgress.Visible = true;
                rc4.ProgressChange += progressChange; //подписываемся для отображения прогресса на форме
                await Task.Run(() => rc4.CipherFile(pathTextBox.Text, savePathTextBox.Text, par)); //Асинхронно запускаем метод для шифрования или дешифрования файла
                panelProgress.Visible = false; MessageBox.Show("Успешно");
                panelControlFalseInChipering.Enabled = true;
            }
            catch ( Exception ex) { MessageBox.Show(ex.Message); panelControlFalseInChipering.Enabled = true; } //Если произошла ошибка выводим ее
        }

      
        private void Savebut_Click(object sender, EventArgs e)
        {
            if ( saveFileDial.ShowDialog() == DialogResult.OK)
            {
                savePathTextBox.Text = saveFileDial.FileName;
            }
        }
     
        void progressChange(long[] prog) //Отображает и изменяет строку прогресса
        {
            
            Action vi = () =>
            {
                PrLabel.Text = prog[1].ToString(); readedLabel.Text = prog[0].ToString();
                progressBar1.Maximum = (int)prog[0]; progressBar1.Value = (int)prog[1];
            };

            if (InvokeRequired)
            { Invoke(vi); }
            else vi();




        }

        private void OpenKeybutton_Click(object sender, EventArgs e)
        {

            try
            {
                if (keyOpenFile.ShowDialog() == DialogResult.Cancel)
                    return;

                using (System.IO.BinaryReader keyReader = new System.IO.BinaryReader(keyOpenFile.OpenFile()))
                {
                    string key = keyReader.ReadString();
                    KeytextBox.Text = key;
                }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message); panelControlFalseInChipering.Enabled = true; }
        }

        private void SaveKeybutton_Click(object sender, EventArgs e)
        {
            try
            {
                if (keySaveDial.ShowDialog() == DialogResult.Cancel)
                    return;

                using (System.IO.BinaryWriter keyWriter = new System.IO.BinaryWriter(keySaveDial.OpenFile()))
                {
                    keyWriter.Write(KeytextBox.Text);

                }
            }
            catch (Exception ex) { MessageBox.Show(ex.Message); panelControlFalseInChipering.Enabled = true; }
            
            }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
