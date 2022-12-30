using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;




namespace server
{
    public partial class Form1 : Form
    {
        public class question
        {
            public string data;
            public int answer;

            public question(string d, int a)
            {
                data = d;
                answer = a;
            }
        };

        public class player
        {
            public Socket playerSocket;
            public string name;
            public int answer;
            public double score;

            public player(Socket s, string n)
            {
                playerSocket = s;
                name = n;
                answer = 0;
                score = 0;
            }
        };


        Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        public List<player> players = new List<player>();
        public List<string> puşts = new List<string>();
        public List<player> playerQueue = new List<player>();
        public List<question> questions = new List<question>();


        bool terminating = false;
        bool listening = false;
        bool inGame = false;

        int counter = 0;
        int playerNumber = 10;
        int currentQuestion = 0;
        int questionCount = 0;
       


        public Form1()
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            this.FormClosing += new FormClosingEventHandler(Form1_FormClosing);
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\90538\OneDrive\Desktop\ahmetatayolu_Atayolu_Ahmet_Step2\questions.txt");

            for (int x = 0; x < lines.Count();  x +=2)
            {
                question newQuestion = new question(lines[x], Int32.Parse(lines[x + 1]));
                questions.Add(newQuestion);
            }
            InitializeComponent();
            
        }

        private void sendMessage(string message, Socket to = null)
        {
            Byte[] senderBuffer = Encoding.Default.GetBytes(message);
            if (to != null)
            {
                to.Send(senderBuffer);
            }
            else
            {
                foreach (player player in players)
                {
                    try
                    {
                        //logs.AppendText("set\n");
                        player.playerSocket.Send(senderBuffer);
                    }
                    catch {
                        //logs.AppendText("zort\n");
                    }
                }
            }
        }

        private string getMessage(Socket thisClient)
        {
            Byte[] buffer = new Byte[64];
            thisClient.Receive(buffer);

            string incomingMessage = Encoding.Default.GetString(buffer);
            return incomingMessage.Substring(0, incomingMessage.IndexOf("\0"));
        }

        private void sendQuestion()
        {
            sendMessage(questions[(currentQuestion) % questions.Count()].data);
            currentQuestion++;
        }

        private List<player> Compare(bool opt, int numQuestion = 0)
        {
            List<double> howNear = new List<double>();
            List<player> winners = new List<player>();

            foreach (player x in players)
            {
                double scr = 0;
                if (opt) {scr = Math.Abs(questions[numQuestion].answer - x.answer); }
                else {scr = -1 * x.score; }

                if (howNear.Count() == 0 || scr == howNear.Min())
                {
                    howNear.Add(scr);
                    winners.Add(x);
                }
                else if (scr <= howNear.Min())
                {
                    howNear = new List<double>();
                    howNear.Add(scr);

                    winners = new List<player>();
                    winners.Add(x);
                }
            }
            logs.AppendText("\n");
            return winners;
        }

        private void sendScores()
        {
            string message = "Current Scores:\n\n";
            players = players.OrderByDescending(x => x.score).ToList();
            foreach (player x in players)
            {
                message += x.name + ": " + x.score.ToString() +"\n";
            }
            foreach (string name in puşts)
            {
                message += name + ": 0\n";
            }
            sendMessage(message);
        }

        private void finishGame()
        {
            try
            {
                button1.Enabled = true;
                string message = "The game has " + "ended\n\n";
                List<player> winners = Compare(false);

                if (winners.Count() == 1)
                {
                    message += "Congrats, " + winners[0].name + ".\nYou won this game with a score of " + winners[0].score.ToString() + "!\n";
                }
                else
                {
                    message += "its a tie!\n" +
                        "Congrats";
                    foreach (player x in winners)
                    {
                        message += ", " + x.name;
                    }
                    message += ".\nYou won the game with a combined score of " + winners[0].score.ToString() + "!\n";
                }
                sendMessage(message);
                foreach (player x in players)
                {
                    x.score = 0;
                }
                foreach (player x in playerQueue)
                {
                    players.Add(x);
                }
                playerQueue = new List<player>();
                inGame = false;
                button1.Enabled = true;
                currentQuestion = 0;
                puşts.Clear();
                // eyvah
                puşts = null;
                puşts = new List<string>();

            }
            catch {}
        }

        private void finishRound()
        {
            if (counter == players.Count())
            {
                int numQuestion = (currentQuestion - 1) % questions.Count();

                List<player> winners = Compare(true, numQuestion);

                string message = "The round has ended, \n" +
                    "The answer was : " + questions[numQuestion].answer.ToString() + "\n" +
                    "\n" +
                    "Players Answers:\n";
                foreach (player x in players)
                {
                    message += x.name + ": " + x.answer.ToString() + "\n";
                    x.answer = 0;
                }

                if (winners.Count() == 1)
                {
                    winners[0].score += 1;
                    message += winners[0].name + " won this round and got 1 points!\n";
                }
                else
                {
                    message += "its a tie!\n";
                    foreach (player x in winners)
                    {
                        double k = Math.Round(1.0 / (winners.Count()),2);
                        x.score += k;
                        message += x.name + " won this round and got " + k.ToString() + " points!\n";
                    }
                }
                sendMessage(message);
                sendScores();
                counter = 0;
                if (currentQuestion + 1 <= questionCount)
                {
                    sendQuestion();
                }
                else if (inGame)  //Oyun biterse
                {
                    finishGame();
                }
            }
        }

        private void button_listen_Click(object sender, EventArgs e)
        {
            int serverPort;

            if (Int32.TryParse(textBox_port.Text, out serverPort) && Int32.TryParse(textBox1.Text, out questionCount))
            {
                IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, serverPort);
                serverSocket.Bind(endPoint);
                serverSocket.Listen(playerNumber);

                listening = true;
                button_listen.Enabled = false;

                Thread acceptThread = new Thread(Accept);
                acceptThread.Start();

                logs.AppendText("Started listening on port: " + serverPort + "\n");
                button_listen.Enabled = false;

            }
            else
            {
                logs.AppendText("Please check port number \n");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (players.Count() >= 2)
            {
                logs.AppendText("The Game Has Started!\n");
                puşts.Clear();
                
                inGame = true;
                button1.Enabled = false;
                Int32.TryParse(textBox1.Text, out questionCount);
                foreach (player x in players)
                {
                    Thread receiveThread = new Thread(() => Receive(x));
                    receiveThread.Start();
                }
                sendQuestion();
            }
            else
            {
                logs.AppendText("Not Enough Players!\n");
            }
        }

        private void Accept()
        {
            while(listening)
            {
                try
                {
                    Socket newClient = serverSocket.Accept();
                    string name = getMessage(newClient);

                    var allPlayers = players.Concat(playerQueue).ToList();
                    bool same = false;
                    for(int x = 0; x < allPlayers.Count(); x++)
                    {
                        if(name == allPlayers[x].name)
                        {
                            same = true;
                            break;
                        }
                    }
                    if (same)
                    {
                        sendMessage("This name is already taken!", newClient);
                        newClient.Close();
                    }
                    else if (!inGame)
                    {
                        logs.AppendText("New player here: " + name + "!\n");
                        player newPlayer = new player(newClient, name);
                        players.Add(newPlayer);
                        terminating = false;
                    }
                    else
                    {
                        logs.AppendText("New player in queue: " + name + "!\n");
                        player newPlayer = new player(newClient, name);
                        playerQueue.Add(newPlayer);
                        terminating = false;
                    }
                }
                catch
                {
                    if (terminating)
                    {
                        listening = false;
                    }
                    else
                    {
                        logs.AppendText("The socket stopped working.\n");
                    }

                }
            }
        }

        private void Receive(player thisPlayer)
        {
            bool connected = true;

            while(connected && !terminating)
            {
                try
                {
                    string incomingMessage = getMessage(thisPlayer.playerSocket);
                    logs.AppendText(thisPlayer.name + ": "+ incomingMessage + "!\n");

                    int answer;
                    if(int.TryParse(incomingMessage, out answer))
                    {
                        thisPlayer.answer = answer;
                        counter++;
                    }
                    finishRound();
                }
                catch //player disconnected
                {
                    if(!terminating)
                    {
                        players.Remove(thisPlayer);
                        
                        logs.AppendText("A client has disconnected\n");
                        sendMessage("One player left the game.");
                    }
                    for (int x = 0; x < players.Count(); x++)
                    {
                        if (players[x].name == thisPlayer.name)
                        {
                            players.RemoveAt(x);
                        }
                    }
                    puşts.Add(thisPlayer.name);
                    thisPlayer.playerSocket.Close();
                    connected = false;
                    if (players.Count() == 0)
                    {
                        logs.AppendText("All clients have disconnected\n");
                    }
                    else
                    {
                        finishRound();
                        if (players.Count() < 2)
                        {
                            sendScores(); //Optional not clear in document
                            finishGame();
                        }
                    }
                }
            }
        }

        private void Form1_FormClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            listening = false;
            terminating = true;
            Environment.Exit(0);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
