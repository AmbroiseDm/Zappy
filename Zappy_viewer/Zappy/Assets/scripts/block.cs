using UnityEngine;
using System.Collections;

public class block : MonoBehaviour 
{
	public uint Nourriture = 0;
	public uint Linemate = 0;
	public uint Derau = 0;
	public uint Sibur = 0;
	public uint Mendiane = 0;
	public uint Phiras = 0;
	public uint Thystame = 0;

	public uint x = 0;
	public uint y = 0;
	public uint z = 0;
	private bool reloadInfo = true;
	private bool enable = false;

	int i = 0;

	void Start ()
	{
	}
	// Update is called once per frame


	void Update () 
	{
		if (reloadInfo == false) {
			if (i >= 500) {
				reloadInfo = true;
				i = 0;
			}
			i = i + 1;
		}
	}

	void OnMouseOver () 
	{
	//	if (Input.GetMouseButtonDown (0))
		if (reloadInfo) { /*
			print ("nourriture : " + Nourriture + "\n" +
			"Linemate : " + Linemate + "\n" +
			"Derau :  " + Derau + "\n" +
			"Sibur : " + Sibur + "\n" +
			"Mendiane : " + Mendiane + "\n" +
			"Phiras : " + Phiras + "\n" +
			"Thystame : " + Thystame + "\n"); */
			reloadInfo = false;
		}
		Camera.main.GetComponent<Parsing> ().HUD_Enable = true;
		enable = true;
	}

	void OnMouseExit()
	{
		enable = false;
		Camera.main.GetComponent<Parsing> ().HUD_Enable = false;
	}

	void OnGUI()
	{
		if (enable) {
			GUI.Label (new Rect (Screen.width / 2 - 190,  Screen.height - 38, 40, 40), Nourriture.ToString ());
			GUI.Label (new Rect (Screen.width / 2 - 120, Screen.height - 38, 40, 40), Linemate.ToString ());
			GUI.Label (new Rect (Screen.width / 2 - 60, Screen.height - 38, 40, 40), Derau.ToString ());
			GUI.Label (new Rect (Screen.width / 2, Screen.height - 38, 40, 40), Sibur.ToString ());
			GUI.Label (new Rect (Screen.width / 2 + 60, Screen.height - 38, 40, 40), Mendiane.ToString ());
			GUI.Label (new Rect (Screen.width / 2 + 115, Screen.height - 38, 40, 40), Phiras.ToString ());
			GUI.Label (new Rect (Screen.width / 2 + 165, Screen.height - 38, 40, 40), Thystame.ToString ());
		}
	}

	public void setRessources(int r0, int r1, int r2, int r3, int r4, int r5, int r6)
	{
		Nourriture = (uint)r0;
		Linemate = (uint)r1;
		Derau = (uint)r2;
		Sibur = (uint)r3;
		Mendiane = (uint)r4;
		Phiras = (uint)r5;
		Thystame = (uint)r6;
	}

	public void removeRessources(int ressources)
	{
		if (ressources == 0 && Nourriture > 0)
			Nourriture = Nourriture - 1;
		else if (ressources == 1 && Linemate > 0)
			Linemate = Linemate - 1;
		else if (ressources == 2 && Derau > 0)
			Derau = Derau - 1;
		else if (ressources == 3 && Sibur > 0)
			Sibur = Sibur - 1;
		else if (ressources == 4 && Mendiane > 0)
			Mendiane = Mendiane - 1;
		else if (ressources == 5 && Phiras > 0)
			Phiras = Phiras - 1;
		else if (ressources == 6 && Thystame > 0)
			Thystame = Thystame - 1;
	}

	public void addRessources(int ressources)
	{
		if (ressources == 0)
			Nourriture = Nourriture + 1;
		else if (ressources == 1)
			Linemate = Linemate + 1;
		else if (ressources == 2)
			Derau = Derau + 1;
		else if (ressources == 3)
			Sibur = Sibur + 1;
		else if (ressources == 4)
			Mendiane = Mendiane + 1;
		else if (ressources == 5)
			Phiras = Phiras + 1;
		else if (ressources == 6)
			Thystame = Thystame + 1;
	}

	public void posBlock(uint a, uint b, uint c)
	{
		x = a;
		y = c;
		z = b;
		transform.position = new Vector3 (a, b, c);
	}

	void OnCollisionenter(Collision col)
	{
		print (col.gameObject.name);
		Destroy(col.gameObject);
	}
 
}
