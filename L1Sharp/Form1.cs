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
        Process ChildProcess = null;
        EventWaitHandle eventStop = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStop");
        EventWaitHandle eventStart = new EventWaitHandle(false, EventResetMode.AutoReset, "eventStart");
        EventWaitHandle eventConfirm = new EventWaitHandle(false, EventResetMode.ManualReset, "eventConfirm");
        EventWaitHandle eventQuit = new EventWaitHandle(false, EventResetMode.AutoReset, "eventQuit");
        EventWaitHandle eventMessageSent = new EventWaitHandle(false, EventResetMode.AutoReset, "eventMessageSent");

        [DllImport("TransportDll.dll")]
        private static extern void sendTextToMMF(string Str, int thread);

        int k;

        public Form1()
        {
            InitializeComponent();
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            if (ChildProcess == null || ChildProcess.HasExited)
            {
                ChildProcess = Process.Start("L1\\L1.exe");
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
                    eventStart.Set();
                    eventConfirm.WaitOne();
                    ThreadList.Items.Add(String.Format("Thread {0}", k++));
                    eventConfirm.Reset();
                }
            }

        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            if (ChildProcess == null || ChildProcess.HasExited)
            {
            }
            else
            {
                if (k == 0)
                {
                    
                    eventQuit.Set();
                    eventConfirm.WaitOne();
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    threadCountField.Enabled = false;
                }
                if (ThreadList.Items.Count != 0) {
                    eventStop.Set();
                    eventConfirm.WaitOne();
                    ThreadList.Items.RemoveAt(ThreadList.Items.Count - 1);
                    k--;
                    eventConfirm.Reset();
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (ChildProcess != null && !ChildProcess.HasExited)
            {
                ChildProcess.CloseMainWindow();
                ChildProcess.Close();
            }
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            if (threadTextBox.Text.Length == 0)
            {
                return;
            }

            string sb = threadTextBox.Text;
            int threadNum = ThreadList.SelectedIndex;
            sendTextToMMF(sb, threadNum);
            eventMessageSent.Set();
            eventConfirm.WaitOne();
        }
             
    }
}
