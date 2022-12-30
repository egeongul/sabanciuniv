using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace client
{
    public partial class Form1 : Form
    {

        bool terminating = false;
        bool connected = false;
        int transmissionBits = 256;
        Socket clientSocket;

        public Form1()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            this.FormClosing += new FormClosingEventHandler(Form1_FormClosing);
            InitializeComponent();
        }

        private void sendMessage(string message)
        {
            Byte[] senderBuffer = Encoding.Default.GetBytes(message);
            clientSocket.Send(senderBuffer);
        }

        private string getMessage()
        {
            Byte[] buffer = new Byte[transmissionBits];
            clientSocket.Receive(buffer);
            string incomingMessage = Encoding.Default.GetString(buffer);
            incomingMessage = incomingMessage.Substring(0, incomingMessage.IndexOf("\0"));
            if (incomingMessage == "")
            {
                throw new Exception();
            }
            return incomingMessage;
        }

        private void changeConnection()
        {
            button_connect.Enabled = !button_connect.Enabled;
            nameBox.Enabled = !nameBox.Enabled;
            textBox_ip.Enabled = !textBox_ip.Enabled;
            textBox_port.Enabled = !textBox_port.Enabled;
        }

        private void changeSending(bool opt = true)
        {
            button_send.Enabled = opt;
            textBox_message.Enabled = opt;
        }

        private void button_connect_Click(object sender, EventArgs e)
        {
            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            string IP = textBox_ip.Text;
            string name = nameBox.Text;

            int portNum;
            if(Int32.TryParse(textBox_port.Text, out portNum))
            {
                try
                {
                    if (name != "" && name.Length <= transmissionBits)
                    {
                        clientSocket.Connect(IP, portNum);
                        sendMessage(name);
                        
                        changeConnection();
                        connected = true;
                        logs.AppendText("Connected to the server!\n");

                        Thread receiveThread = new Thread(Receive);
                        receiveThread.Start();
                    }
                }
                catch
                {
                    logs.AppendText("Could not connect to the server!\n");
                }
            }
            else
            {
                logs.AppendText("Check the port\n");
            }

        }

        private void button_send_Click(object sender, EventArgs e)
        {
            string message = textBox_message.Text;
            int numericValue;
            bool isNumber = int.TryParse(message, out numericValue);
            if (isNumber && message.Length <= transmissionBits)
            {
                sendMessage(message);
                changeSending(false);
            }
            else if (!isNumber)
            {
                logs.AppendText("You need to enter numeric characters!\n");
            }
        }

        private void Receive()
        {
            while(connected)
            {
                try
                {
                    string incomingMessage = getMessage();
                    logs.AppendText("Server: " + incomingMessage + "\n");
                    changeSending(true);
                    if (incomingMessage.Contains("The game has ended"))
                    {
                        button_send.Enabled = false;
                    }
                }
                catch
                {
                    if (!terminating)
                    {
                        logs.AppendText("The server has disconnected\n");
                        changeConnection();
                        changeSending(false);
                    }

                    clientSocket.Close();
                    connected = false;
                }

            }
        }

        private void Form1_FormClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            connected = false;
            terminating = true;
            Environment.Exit(0);
        }

        private void textBox_ip_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
