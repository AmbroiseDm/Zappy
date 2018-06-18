using UnityEngine;
#if UNITY_EDITOR
using UnityEditor;
#endif
using UnityEngine.UI;
using System.Collections;
using UnityEngine.SceneManagement;

public class ApplicationManager : MonoBehaviour 
{
	public string host;
	public string port;


	public void Play () 
	{	
		SceneManager.UnloadScene(0);
		SceneManager.LoadScene(1);
	}

	public void Back () 
	{	
		SceneManager.UnloadScene(1);
		SceneManager.LoadScene(0);
	}

	public void Quit () 
	{
		Application.Quit();
	}

	public void Win(string data)
	{
		#if UNITY_EDITOR
			EditorUtility.DisplayDialog ("Win", "Congratulation " +data+ " win the game !", "Confirm");
		#endif
		Back ();
	}

	public void End()
	{
		#if UNITY_EDITOR
			EditorUtility.DisplayDialog ("End", "Connection lost\nThe Server is unavailable", "Ok .."); 
		#endif
		Back ();
	}


	public void setHost(InputField setField)
	{
		host = setField.text;
	}

	public void setPort(InputField portField)
	{
		port = portField.text;
	}

	public string getHost()
	{
		return host;
	}

	public string getPort()
	{
		return port;
	}

	public void Connect()
	{
		print ("connect to " + getHost() + ":" + getPort());
	}

}
