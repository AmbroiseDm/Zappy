using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

	public int x;
	public int y;
	private int id;
	public int orientation;
	private int lvl;
	private string team;

	public int Nourriture = 0;
	public int Linemate = 0;
	public int Derau = 0;
	public int Sibur = 0;
	public int Mendiane = 0;
	public int Phiras = 0;
	public int Thystame = 0;

	int i = 0;
	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {

		if (id != -1) {
			if (i >= 100) {
				Camera.main.GetComponent<Socket> ().writeToServ ("pin " + id);
				i = 0;
			}
			i = i + 1;
		}

	}

	public int getID()
	{
		return (id);
	}

	public int getX()
	{
		return (x);
	}

	public int getY()
	{
		return (y);
	}

	public void createPlayer(int x0, int y0, int id0, int orientation0, int lvl0, string team0)
	{
		x = x0;
		y = y0;
		id = id0;
		orientation = orientation0;
		lvl = lvl0;
		team = team0;
		transform.position = new Vector3 (x, 1, y);
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

	public void Move(int x0, int y0, int orien)
	{
		orientation = orien;
		if (orientation == 1)
			GetComponent<handlePlayer> ().Nord ();
		else if (orientation == 2)
			GetComponent<handlePlayer> ().Est ();
		else if (orientation == 3)
			GetComponent<handlePlayer> ().Sud ();
		else if (orientation == 4)
			GetComponent<handlePlayer> ().Ouest ();
		GetComponent<handlePlayer> ().move (x0, y0);
		x = x0;
		y = y0;
	}

	public void Die()
	{
		playDie ();
		x = -1;
		y = -1;
		id = -1;
		orientation = -1;
		lvl = -1;
		team = null;
		transform.position = new Vector3 (-9999, -9999, -9999);
		stopDie ();
	}

	public void setLvl(int new_lvl)
	{
		lvl = new_lvl;
	}

	public void playVictory()
	{
		GetComponent<Animation> ().Stop ("idle");
		GetComponent<Animation> ().Play ("victory");
	}

	public void playDie()
	{
		GetComponent<Animation> ().Stop ("idle");
		GetComponent<Animation> ().Play ("die");
	}

	public void stopVictory()
	{
		GetComponent<Animation> ().Stop ("victory");
	}

	public void stopDie()
	{
		GetComponent<Animation> ().Stop ("die");
	}

	public void setName(string name)
	{
		team = name;
	}

	public string getName()
	{
		return team;
	}

	public void setInv(int r0, int r1, int r2, int r3, int r4, int r5, int r6)
	{
		Nourriture = r0;
		Linemate = r1;
		Derau = r2;
		Sibur = r3;
		Mendiane = r4;
		Phiras = r5;
		Thystame = r6;
	}
}
