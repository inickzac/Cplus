namespace CIPHER
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.openFileButtom = new System.Windows.Forms.Button();
            this.pathTextBox = new System.Windows.Forms.TextBox();
            this.cryptButtom = new System.Windows.Forms.Button();
            this.deciperButton = new System.Windows.Forms.Button();
            this.PrLabel = new System.Windows.Forms.Label();
            this.savePathTextBox = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.readedLabel = new System.Windows.Forms.Label();
            this.panelControlFalseInChipering = new System.Windows.Forms.Panel();
            this.KeytextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.OpenKeybutton = new System.Windows.Forms.Button();
            this.SaveKeybutton = new System.Windows.Forms.Button();
            this.Savebut = new System.Windows.Forms.Button();
            this.panelProgress = new System.Windows.Forms.Panel();
            this.kettextlabel = new System.Windows.Forms.Label();
            this.genTextKeylabel = new System.Windows.Forms.Label();
            this.GenKeytextBox = new System.Windows.Forms.TextBox();
            this.Keylabel = new System.Windows.Forms.Label();
            this.panelControlFalseInChipering.SuspendLayout();
            this.panelProgress.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFileButtom
            // 
            this.openFileButtom.Location = new System.Drawing.Point(208, 136);
            this.openFileButtom.Name = "openFileButtom";
            this.openFileButtom.Size = new System.Drawing.Size(147, 23);
            this.openFileButtom.TabIndex = 10;
            this.openFileButtom.Text = "Открыть файл";
            this.openFileButtom.UseVisualStyleBackColor = true;
            this.openFileButtom.Click += new System.EventHandler(this.OpenFileButtom_Click);
            // 
            // pathTextBox
            // 
            this.pathTextBox.Location = new System.Drawing.Point(10, 136);
            this.pathTextBox.Name = "pathTextBox";
            this.pathTextBox.Size = new System.Drawing.Size(176, 20);
            this.pathTextBox.TabIndex = 11;
            // 
            // cryptButtom
            // 
            this.cryptButtom.Location = new System.Drawing.Point(10, 54);
            this.cryptButtom.Name = "cryptButtom";
            this.cryptButtom.Size = new System.Drawing.Size(147, 23);
            this.cryptButtom.TabIndex = 12;
            this.cryptButtom.Text = "Зашифровать";
            this.cryptButtom.UseVisualStyleBackColor = true;
            this.cryptButtom.Click += new System.EventHandler(this.CryptButtom_Click);
            // 
            // deciperButton
            // 
            this.deciperButton.Location = new System.Drawing.Point(10, 83);
            this.deciperButton.Name = "deciperButton";
            this.deciperButton.Size = new System.Drawing.Size(147, 23);
            this.deciperButton.TabIndex = 13;
            this.deciperButton.Text = "Расшифровать";
            this.deciperButton.UseVisualStyleBackColor = true;
            this.deciperButton.Click += new System.EventHandler(this.DeciperButton_Click);
            // 
            // PrLabel
            // 
            this.PrLabel.AutoSize = true;
            this.PrLabel.Location = new System.Drawing.Point(10, 29);
            this.PrLabel.Name = "PrLabel";
            this.PrLabel.Size = new System.Drawing.Size(0, 13);
            this.PrLabel.TabIndex = 14;
            // 
            // savePathTextBox
            // 
            this.savePathTextBox.Location = new System.Drawing.Point(10, 162);
            this.savePathTextBox.Name = "savePathTextBox";
            this.savePathTextBox.Size = new System.Drawing.Size(176, 20);
            this.savePathTextBox.TabIndex = 15;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(10, 3);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(406, 23);
            this.progressBar1.TabIndex = 16;
            // 
            // readedLabel
            // 
            this.readedLabel.AutoSize = true;
            this.readedLabel.Location = new System.Drawing.Point(131, 29);
            this.readedLabel.Name = "readedLabel";
            this.readedLabel.Size = new System.Drawing.Size(0, 13);
            this.readedLabel.TabIndex = 17;
            // 
            // panelControlFalseInChipering
            // 
            this.panelControlFalseInChipering.Controls.Add(this.KeytextBox);
            this.panelControlFalseInChipering.Controls.Add(this.label1);
            this.panelControlFalseInChipering.Controls.Add(this.OpenKeybutton);
            this.panelControlFalseInChipering.Controls.Add(this.SaveKeybutton);
            this.panelControlFalseInChipering.Controls.Add(this.Savebut);
            this.panelControlFalseInChipering.Controls.Add(this.openFileButtom);
            this.panelControlFalseInChipering.Controls.Add(this.cryptButtom);
            this.panelControlFalseInChipering.Controls.Add(this.pathTextBox);
            this.panelControlFalseInChipering.Controls.Add(this.savePathTextBox);
            this.panelControlFalseInChipering.Controls.Add(this.deciperButton);
            this.panelControlFalseInChipering.Location = new System.Drawing.Point(2, 12);
            this.panelControlFalseInChipering.Name = "panelControlFalseInChipering";
            this.panelControlFalseInChipering.Size = new System.Drawing.Size(419, 206);
            this.panelControlFalseInChipering.TabIndex = 18;
            // 
            // KeytextBox
            // 
            this.KeytextBox.Location = new System.Drawing.Point(10, 17);
            this.KeytextBox.Name = "KeytextBox";
            this.KeytextBox.Size = new System.Drawing.Size(391, 20);
            this.KeytextBox.TabIndex = 26;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 1);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(216, 13);
            this.label1.TabIndex = 25;
            this.label1.Text = "Введите цифры от 0 до 255 через пробел";
            // 
            // OpenKeybutton
            // 
            this.OpenKeybutton.Location = new System.Drawing.Point(218, 83);
            this.OpenKeybutton.Name = "OpenKeybutton";
            this.OpenKeybutton.Size = new System.Drawing.Size(137, 23);
            this.OpenKeybutton.TabIndex = 22;
            this.OpenKeybutton.Text = "Открыть файл ключа";
            this.OpenKeybutton.UseVisualStyleBackColor = true;
            this.OpenKeybutton.Click += new System.EventHandler(this.OpenKeybutton_Click);
            // 
            // SaveKeybutton
            // 
            this.SaveKeybutton.Location = new System.Drawing.Point(218, 54);
            this.SaveKeybutton.Name = "SaveKeybutton";
            this.SaveKeybutton.Size = new System.Drawing.Size(137, 23);
            this.SaveKeybutton.TabIndex = 21;
            this.SaveKeybutton.Text = "Сохранить ключ";
            this.SaveKeybutton.UseVisualStyleBackColor = true;
            this.SaveKeybutton.Click += new System.EventHandler(this.SaveKeybutton_Click);
            // 
            // Savebut
            // 
            this.Savebut.Location = new System.Drawing.Point(208, 160);
            this.Savebut.Name = "Savebut";
            this.Savebut.Size = new System.Drawing.Size(147, 23);
            this.Savebut.TabIndex = 16;
            this.Savebut.Text = "Путь сохранения файла";
            this.Savebut.UseVisualStyleBackColor = true;
            this.Savebut.Click += new System.EventHandler(this.Savebut_Click);
            // 
            // panelProgress
            // 
            this.panelProgress.Controls.Add(this.readedLabel);
            this.panelProgress.Controls.Add(this.progressBar1);
            this.panelProgress.Controls.Add(this.PrLabel);
            this.panelProgress.Location = new System.Drawing.Point(2, 568);
            this.panelProgress.Name = "panelProgress";
            this.panelProgress.Size = new System.Drawing.Size(419, 48);
            this.panelProgress.TabIndex = 19;
            // 
            // kettextlabel
            // 
            this.kettextlabel.AutoSize = true;
            this.kettextlabel.Location = new System.Drawing.Point(9, 266);
            this.kettextlabel.Name = "kettextlabel";
            this.kettextlabel.Size = new System.Drawing.Size(130, 13);
            this.kettextlabel.TabIndex = 27;
            this.kettextlabel.Text = "Сгенерированный ключ:";
            // 
            // genTextKeylabel
            // 
            this.genTextKeylabel.AutoSize = true;
            this.genTextKeylabel.Location = new System.Drawing.Point(12, 243);
            this.genTextKeylabel.Name = "genTextKeylabel";
            this.genTextKeylabel.Size = new System.Drawing.Size(0, 13);
            this.genTextKeylabel.TabIndex = 28;
            // 
            // GenKeytextBox
            // 
            this.GenKeytextBox.Location = new System.Drawing.Point(12, 282);
            this.GenKeytextBox.Multiline = true;
            this.GenKeytextBox.Name = "GenKeytextBox";
            this.GenKeytextBox.Size = new System.Drawing.Size(409, 280);
            this.GenKeytextBox.TabIndex = 29;
            // 
            // Keylabel
            // 
            this.Keylabel.AutoSize = true;
            this.Keylabel.Location = new System.Drawing.Point(12, 225);
            this.Keylabel.Name = "Keylabel";
            this.Keylabel.Size = new System.Drawing.Size(106, 13);
            this.Keylabel.TabIndex = 30;
            this.Keylabel.Text = "исходные значения";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(429, 628);
            this.Controls.Add(this.Keylabel);
            this.Controls.Add(this.GenKeytextBox);
            this.Controls.Add(this.genTextKeylabel);
            this.Controls.Add(this.panelControlFalseInChipering);
            this.Controls.Add(this.kettextlabel);
            this.Controls.Add(this.panelProgress);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panelControlFalseInChipering.ResumeLayout(false);
            this.panelControlFalseInChipering.PerformLayout();
            this.panelProgress.ResumeLayout(false);
            this.panelProgress.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button openFileButtom;
        private System.Windows.Forms.TextBox pathTextBox;
        private System.Windows.Forms.Button cryptButtom;
        private System.Windows.Forms.Button deciperButton;
        private System.Windows.Forms.Label PrLabel;
        private System.Windows.Forms.TextBox savePathTextBox;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Label readedLabel;
        private System.Windows.Forms.Panel panelControlFalseInChipering;
        private System.Windows.Forms.Panel panelProgress;
        private System.Windows.Forms.Button Savebut;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button OpenKeybutton;
        private System.Windows.Forms.Button SaveKeybutton;
        private System.Windows.Forms.TextBox KeytextBox;
        private System.Windows.Forms.Label genTextKeylabel;
        private System.Windows.Forms.Label kettextlabel;
        private System.Windows.Forms.TextBox GenKeytextBox;
        private System.Windows.Forms.Label Keylabel;
    }
}

