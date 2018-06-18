using UnityEngine;
using System.Collections;
using System;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Text.RegularExpressions;
using UnityEngine.UI;

public class Socket : MonoBehaviour {
	private TcpClient socketTCP;
	private NetworkStream stream;
	internal Boolean socketOK = false;
	private StreamWriter streamWrite;
	private StreamReader streamRead;
	private String Host = "127.0.0.1";
	private Int32 Port = 4242;
	private String readOfSocket;
	private bool isRead = false;
	private bool isEnd = false;
	private bool isWin = false;
	public GameObject End;
	public GameObject Win;
	public GameObject textWin;

	private string[] words;

	void Start () {
		setupClient ();
		if (socketOK)
		{
			Debug.Log ("Launched");
			writeToServ ("GRAPHIC");
			socketTCP.ReceiveTimeout = 5000;
			Thread readThread = new Thread (new ThreadStart (readSocketThread));
			readThread.Start ();
		}
	}

	void Update () {
		if (isEnd)
			textWin.GetComponent<ApplicationManager> ().End ();
		if (streamRead == null || streamWrite == null || readOfSocket == null)
			isEnd = true;
		else if (isRead == true && isEnd == false) {
			if (readOfSocket != "") {
				Debug.Log ("Output: " + readOfSocket);
				words = Regex.Split(readOfSocket, @"\W|_");
				if (words[0] != null)
				{
					GetComponent<Parsing>().checkParse(words);
				}
			}
			isRead = false;
		}
	}

	void OnGUI()
	{
	}

	public void endGame(string winner)
	{
	/*	UnityEngine.UI.Text myText = textWin.AddComponent<UnityEngine.UI.Text>();
		myText.text = "End of the game\n" + winner + "  Win !";
		myText.font = Resources.GetBuiltinResource(typeof(Font), "Arial.ttf") as Font;
		myText.color = new Color (0, 255, 0); */
		isWin = true;
		GetComponent<ApplicationManager> ().Win (winner);
	}

	void OnDestroy() {
			closeClient();
		print("End of Client");
	}

	void readSocketThread()
	{
		while (!isEnd) {
			if (isRead == false)
			{
				readOfSocket = readToServ ();
				isRead = true;
			}
		}
	}

	public void setupClient() {
		try {
			socketTCP = new TcpClient(Host, Port);
			stream = socketTCP.GetStream();
			streamWrite = new StreamWriter(stream);
			streamRead = new StreamReader(stream);
			socketOK = true;
		}
		catch (Exception e) {
			Debug.Log("Socket error: " + e);
		}
	}
	public void writeToServ(string str) {
		if (!socketOK)
			return;
		String tmp = str + "\n";
		streamWrite.Write(tmp);
		streamWrite.Flush();
	}

	public String readToServ() {
		if (!socketOK)
			return "";
		try {
			return streamRead.ReadLine();
		} catch (Exception e) {
			return "";
		}
	}

	public void closeClient() {
		if (!socketOK)
			return;
		streamWrite.Close();
		streamRead.Close();
		socketTCP.Close();
		socketOK = false;
	}

}


