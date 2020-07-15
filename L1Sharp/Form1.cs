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
        bool ChildProcessStarted = false;
        EventWaitHandle eventStop = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStop");
        EventWaitHandle eventStart = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStart");
        EventWaitHandle eventConfirm = new EventWaitHandle(false, EventResetMode.ManualReset, "eventConfirm");
        EventWaitHandle eventQuit = new EventWaitHandle(false, EventResetMode.AutoReset, "eventQuit");
        EventWaitHandle eventMessageSent = new EventWaitHandle(false, EventResetMode.AutoReset, "eventMessageSent");

        [DllImport("TransportDll.dll")]
        private static extern void SendText(string Str, int threadNum);
        [DllImport("TransportDll.dll")]
        private static extern void SendInfo(int actionId);
        [DllImport("TransportDll.dll")]
        private static extern void Init();

        int k;

        public Form1()
        {
            InitializeComponent();
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            if (!ChildProcessStarted)
            {
                Init();
                ChildProcessStarted = true;
                ThreadList.Items.Clear();
                ThreadList.Items.Add("All threads");
                ThreadList.Items.Add("Main thread");
                threadCountField.Enabled = true;
                k = 0;
            }
            else
            {
                for (var i = 0; i < threadCountField.Value; i++)
                {
                    SendInfo(0);
                    ThreadList.Items.Add(String.Format("Thread {0}", k++));
                }
            }

        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            if (!ChildProcessStarted)
            {
            }
            else
            {
                if (k == 0)
                {
                    SendInfo(3);
                    ChildProcessStarted = false;
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    threadCountField.Enabled = false;
                }
                if (ThreadList.Items.Count != 0) {
                    SendInfo(1);
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    k--;
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            SendInfo(3);
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            if (threadTextBox.Text.Length == 0)
            {
                return;
            }

            string sb = threadTextBox.Text;
            int threadNum = ThreadList.SelectedIndex;
            SendText(sb, threadNum);
            SendInfo(2);
        }
             
    }
}
