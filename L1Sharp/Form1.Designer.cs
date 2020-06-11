namespace L1Sharp
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.StartButton = new System.Windows.Forms.Button();
            this.StopButton = new System.Windows.Forms.Button();
            this.ThreadList = new System.Windows.Forms.ListBox();
            this.threadCountField = new System.Windows.Forms.NumericUpDown();
            this.sendButton = new System.Windows.Forms.Button();
            this.threadTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.threadCountField)).BeginInit();
            this.SuspendLayout();
            // 
            // StartButton
            // 
            resources.ApplyResources(this.StartButton, "StartButton");
            this.StartButton.Name = "StartButton";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // StopButton
            // 
            resources.ApplyResources(this.StopButton, "StopButton");
            this.StopButton.Name = "StopButton";
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // ThreadList
            // 
            this.ThreadList.FormattingEnabled = true;
            resources.ApplyResources(this.ThreadList, "ThreadList");
            this.ThreadList.Name = "ThreadList";
            // 
            // threadCountField
            // 
            resources.ApplyResources(this.threadCountField, "threadCountField");
            this.threadCountField.Name = "threadCountField";
            // 
            // sendButton
            // 
            resources.ApplyResources(this.sendButton, "sendButton");
            this.sendButton.Name = "sendButton";
            this.sendButton.UseVisualStyleBackColor = true;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // threadTextBox
            // 
            resources.ApplyResources(this.threadTextBox, "threadTextBox");
            this.threadTextBox.Name = "threadTextBox";
            // 
            // Form1
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.threadTextBox);
            this.Controls.Add(this.sendButton);
            this.Controls.Add(this.threadCountField);
            this.Controls.Add(this.ThreadList);
            this.Controls.Add(this.StopButton);
            this.Controls.Add(this.StartButton);
            this.Name = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.threadCountField)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.ListBox ThreadList;
        private System.Windows.Forms.NumericUpDown threadCountField;
        private System.Windows.Forms.Button sendButton;
        private System.Windows.Forms.TextBox threadTextBox;
    }
}

