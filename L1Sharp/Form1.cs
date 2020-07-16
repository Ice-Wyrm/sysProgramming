using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;
using System.Runtime.InteropServices;

namespace L1Sharp
{
    public partial class Form1 : Form
    {
        EventWaitHandle eventStop = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStop");
        EventWaitHandle eventStart = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStart");
        EventWaitHandle eventConfirm = new EventWaitHandle(false, EventResetMode.ManualReset, "eventConfirm");
        EventWaitHandle eventQuit = new EventWaitHandle(false, EventResetMode.AutoReset, "eventQuit");
        EventWaitHandle eventMessageSent = new EventWaitHandle(false, EventResetMode.AutoReset, "eventMessageSent");

        [DllImport("TransportDllMFC.dll")]
        private static extern void SendText(string Str);
        [DllImport("TransportDllMFC.dll")]
        private static extern void SendInfo(int actionId);

        [DllImport("TransportDllMFC.dll")]
        private static extern bool ConnectToServer();
        [DllImport("TransportDllMFC.dll")]
        private static extern void Disconnect();
        [DllImport("TransportDllMFC.dll")]
        private static extern int Response();

        int k;

        public Form1()
        {
            InitializeComponent();
            ThreadList.Items.Clear();
            ThreadList.Items.Add("All threads");
            ThreadList.Items.Add("Main thread");
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            for (var i = 0; i < threadCountField.Value; i++)
            {
                bool Connection = ConnectToServer();
                SendInfo(0);
                int actualThreadNumber = Response() + 1;
                Disconnect();
                ThreadList.Items.Add(String.Format("Thread {0}", k++));
                while (actualThreadNumber != ThreadList.Items.Count)
                    this.CorrectThreadList(actualThreadNumber);
            }
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            if (ThreadList.Items.Count > 2) {
                ConnectToServer();
                SendInfo(1);
                int actualThreadNumber = Response() + 1;
                Disconnect();
                ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                while (actualThreadNumber != ThreadList.Items.Count)
                    this.CorrectThreadList(actualThreadNumber);
                k--;
            }
        }

        private void CorrectThreadList(int actualThreadNumber)
        {
            if (ThreadList.Items.Count < actualThreadNumber)
            {
                ThreadList.Items.Add(String.Format("Thread {0}", k++));
            }

            if (ThreadList.Items.Count > actualThreadNumber)
            {
                ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {

        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            if (threadTextBox.Text.Length == 0)
            {
                return;
            }

            string sb = threadTextBox.Text;
            int threadNum = ThreadList.SelectedIndex;

            ConnectToServer();
            SendInfo(2);
            SendText(sb);
            int actualThreadNumber = Response() + 1;
            Disconnect();

            while (actualThreadNumber != ThreadList.Items.Count)
                this.CorrectThreadList(actualThreadNumber);
        }
             
    }
}
