using UnityEngine;
using System.Collections;
using System;
using System.Collections.Specialized;
using System.Text.RegularExpressions;


public class Parsing : MonoBehaviour {

	private bool MapCreated = false;
	string [] teams = null;
	private GameObject [] players = null;
	private GameObject[] eggs = null;
	public GameObject HUD;
	public bool HUD_Enable = false;
	public Texture2D curseur;

	private int xmap;
	private int ymap;
	// Use this for initialization
	void Start () {
		Cursor.SetCursor (curseur, Vector2.zero, CursorMode.Auto);
	}
	
	// Update is called once per frame
	void Update () {
		HUD.SetActive (HUD_Enable);
	}

	public void checkParse(string[] words)
	{
		int length = words.Length;

		if (words [0] == "msz" && length == 3)
			refresh_map (words [1], words [2]);
		else if (words [0] == "tna" && length == 2)
			check_team (words [1]);
		else if (words [0] == "bct" && length == 10)
			refresh_case (words);
		else if (words [0] == "seg" && length == 2)
			end_game (words [1]);
		else if (words [0] == "pnw" && length == 7)
			create_player (words);
		else if (words [0] == "ppo" && length == 5)
			move_player (words);
		else if (words [0] == "piv" && length == 3)
			set_player_lvl (words);
		else if (words [0] == "pin" && length == 11)
			set_player_inv (words);
		else if (words [0] == "pdi" && length == 2)
			kill_player (words[1]);
		else if (words [0] == "enw" && length == 5)
			create_egg (words);
		else if (words [0] == "edi" && length == 2)
			die_egg (words[1]);
		else if (words [0] == "ebo" && length == 2)
			get_egg (words[1]);
		else if (words [0] == "eht" && length == 2)
			birth_egg (words[1]);
		else if (words [0] == "pdr" && length == 3)
			put_ressources (words);
		else if (words [0] == "pgt" && length == 3)
			get_ressources (words);
	}

	void put_ressources(string [] words)
	{
		int id = -1;
		int ressources = -1;
		int tmp;

		Int32.TryParse(words[1], out id);
		Int32.TryParse(words[2], out ressources);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1 || ressources <= -1 || ressources > 6)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id (id)) == -1)
			Debug.Log ("No players with this ID.");
		else {
		/*	players [tmp].GetComponent<Player> ().removeRessources (ressources);
			GetComponent<GeneratorMap> ().AddRessources (ressources, players [tmp].GetComponent<Player> ().getX (), players [tmp].GetComponent<Player> ().getY ()); */
			Debug.Log ("Player N" + id + " put ressources=" + ressources);
		}
	}

	void get_ressources(string [] words)
	{
		int id = -1;
		int ressources = -1;
		int tmp;

		Int32.TryParse(words[1], out id);
		Int32.TryParse(words[2], out ressources);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1 || ressources <= -1 || ressources > 6)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id (id)) == -1)
			Debug.Log ("No players with this ID.");
		else {
			/* players [tmp].GetComponent<Player> ().addRessources (ressources);
			GetComponent<GeneratorMap> ().removeRessources (ressources, players [tmp].GetComponent<Player> ().getX (), players [tmp].GetComponent<Player> ().getY ()); */
			Debug.Log ("Player N" + id + " get ressources=" + ressources);
		}
	}

	void set_player_lvl(string [] words)
	{
		int id = -1;
		int lvl = -1;
		int tmp;

		Int32.TryParse(words[1], out id);
		Int32.TryParse(words[2], out lvl);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1 || lvl <= -1)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id (id)) == -1)
			Debug.Log ("No players with this ID.");
		else {
			players [tmp].GetComponent<Player> ().setLvl (lvl);
			Debug.Log ("Player N" + id + " have lvl=" + lvl);
		}
	}

	void set_player_inv(string [] words)
	{
		int id = -1;
		int r0 = -1;
		int r1 = -1;
		int r2 = -1;
		int r3 = -1;
		int r4 = -1;
		int r5 = -1;
		int r6 = -1;
		int tmp;

		Int32.TryParse(words[1], out id);
		Int32.TryParse(words[4], out r0);
		Int32.TryParse(words[5], out r1);
		Int32.TryParse(words[6], out r2);
		Int32.TryParse(words[7], out r3);
		Int32.TryParse(words[8], out r4);
		Int32.TryParse(words[9], out r5);
		Int32.TryParse(words[10], out r6);

		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		}
		else if (r0 <= -1 || r1 <= -1 || r2 <= -1 || r3 <= -1 || r4 <= -1 || r5 <= -1 || r6 <= -1 || id <= -1)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id (id)) == -1)
			Debug.Log ("No players with this ID.");
		else {
			players [tmp].GetComponent<Player> ().setInv (r0, r1, r2, r3, r4, r5, r6);
			Debug.Log ("Player N" + id + " have inventory refresh.");
		}
	}

	void end_game(string winner)
	{

		for (int i = 0; i < players.Length; i++)
		{
			if (players[i].GetComponent<Player> ().getName() == winner) 
				players [i].GetComponent<Player> ().playVictory ();
			else 
				players [i].GetComponent<Player> ().playDie ();
		}
		Debug.Log ("Game is over: " + winner + " win the game.");
		GetComponent<ApplicationManager> ().Win (winner);
		GetComponent<ApplicationManager> ().End ();
		GetComponent<Socket> ().endGame (winner);
	}

	void birth_egg(string tmp_id)
	{
		int id = -1;
		int tmp;

		Int32.TryParse(tmp_id, out id);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id_egg (id)) == -1)
			Debug.Log ("Not eggs with this ID.");
		else {
			eggs [tmp].GetComponent<Egg>().Hatches ();
			Debug.Log ("Egg N" + id + " hatches.");
		}
	}

	void get_egg(string tmp_id)
	{
		int id = -1;
		int tmp;

		Int32.TryParse(tmp_id, out id);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id_egg (id)) == -1)
			Debug.Log ("Not eggs with this ID.");
		else {
			eggs [tmp].GetComponent<Egg>().Die ();
			Debug.Log ("Egg N" + id + " is keep by a new Player" +
				".");
		}
	}

	void die_egg(string tmp_id)
	{
		int id = -1;
		int tmp;

		Int32.TryParse(tmp_id, out id);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id_egg (id)) == -1)
			Debug.Log ("Not eggs with this ID.");
		else {
			eggs [tmp].GetComponent<Egg>().Die ();
			Debug.Log ("Egg N" + id + " die.");
		}
	}

	void create_egg(string[] words)
	{
		int id = -1;
		int new_x = -1;
		int new_y = -1;
		int eggid = -1;

		Int32.TryParse(words[1], out eggid);
		Int32.TryParse(words[2], out id);
		Int32.TryParse(words[3], out new_x);
		Int32.TryParse(words[4], out new_y);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1 | new_x <= -1 || new_y <= -1 || eggid <= -1 || new_x > xmap || new_y > ymap)
			Debug.Log ("Bad input ressources.");
		else if (check_id (id) == -1)
			Debug.Log ("No player with this ID.");
		else if (check_id_egg (id) != -1)
			Debug.Log ("ID of the egg is already use.");
		else {
			if (eggs == null)
			{
				eggs = new GameObject[1];
				eggs[0] = Instantiate(Resources.Load("EGG")) as GameObject;
				eggs[0].GetComponent<Egg> ().createEgg (new_x, new_y, eggid, id);
			}	
			else {
				Array.Resize (ref eggs, eggs.Length + 1);
				eggs[eggs.Length - 1] = Instantiate(Resources.Load("EGG")) as GameObject;
				eggs[eggs.Length - 1].GetComponent<Egg> ().createEgg (new_x, new_y, eggid, id);
			}
			Debug.Log ("New Eggs N" + eggid + " at x=" + new_x + " and y=" + new_y);

		}
	}

	void kill_player(string tmp_id)
	{
		int id = -1;
		int tmp;

		Int32.TryParse(tmp_id, out id);
		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1)
			Debug.Log ("Bad input ressources.");
		else if ((tmp = check_id (id)) == -1)
			Debug.Log ("No players with this ID.");
		else {
			players [tmp].GetComponent<Player> ().Die ();
			Debug.Log ("Player N" + id + " die.");
		}
	}

	void move_player(string[] words)
	{
		int id = -1;
		int new_x = -1;
		int new_y = -1;
		int orientation = -1;
		int tmp;

		Int32.TryParse(words[1], out id);
		Int32.TryParse(words[2], out new_x);
		Int32.TryParse(words[3], out new_y);
		Int32.TryParse(words[4], out orientation);

		if (!MapCreated) {
			writeMapToServ ();
			Debug.Log ("Need to know length of the map before do this.");
		} else if (id <= -1 | new_x <= -1 || new_y <= -1 || orientation <= 0 || new_x > xmap || new_y > ymap)
			Debug.Log ("Bad input ressources.");
		else if (orientation >= 5)
			Debug.Log ("Bad orientation.");
		else if ((tmp = check_id(id)) == -1)
			Debug.Log ("No player with this ID.");
		else {
			players [tmp].GetComponent<Player>().Move (new_x, new_y, orientation);
			Debug.Log ("Player N" + id + " move at x=" + new_x + " and y=" + new_y);
		}
	}

	void create_player(string[] words)
	{
		int id = -1;
		int new_x = -1;
		int new_y = -1;
		int orientation = -1;
		int lvl = -1;
		string team = null;

		Int32.TryParse(words[1], out id);
		Int32.TryParse(words[2], out new_x);
		Int32.TryParse(words[3], out new_y);
		Int32.TryParse(words[4], out orientation);
		Int32.TryParse(words [5], out lvl);
		team = words [6];

		if (!MapCreated)
		{
			writeMapToServ();
			Debug.Log ("Need to know length of the map before do this.");
		}
		else if (id <= -1 | new_x <= -1 || new_y <= -1 || orientation <= 0 || lvl <= -1 || new_x > xmap || new_y > ymap)
			Debug.Log ("Bad input ressources.");
		else if (orientation >= 5)
			Debug.Log ("Bad orientation.");
		else if (check_id (id) != -1)
			Debug.Log ("ID already use.");
		else if (check_team_exist (team))
			Debug.Log ("Team not found.");
		else {
			if (players == null)
			{
				players = new GameObject[1];
				players[0] = Instantiate(Resources.Load("FreeLich")) as GameObject;
				players[0].GetComponent<Player> ().createPlayer (new_x, new_y, id, orientation, lvl, team);
			}	
			else {
				Array.Resize (ref players, players.Length + 1);
				players[players.Length - 1] = Instantiate(Resources.Load("FreeLich")) as GameObject;
				players[players.Length - 1].GetComponent<Player> ().createPlayer (new_x, new_y, id, orientation, lvl, team);
			}
			Debug.Log ("New Player N" + id + " at x=" + new_x + " and y=" + new_y);
			GetComponent<Socket>().writeToServ ("pin " + id);
		}
	}

	int check_id(int id)
	{
		int i = 0;

		while (players != null && i != players.Length) {
			if (players[i].GetComponent<Player>().getID() == id)
			{
				return (i);
			}
			i = i + 1;
		}
		return (-1);
	}

	int check_id_egg(int id)
	{
		int i = 0;

		while (eggs != null && i != eggs.Length) {
			if (eggs[i].GetComponent<Egg>().getID() == id)
			{
				return (i);
			}
			i = i + 1;
		}
		return (-1);
	}

	bool check_team_exist (string team)
	{
		int i = 0;

		if (teams == null)
			return (true);
		while (teams != null && i != teams.Length) {
			if (teams[i] == team)
			{
				return (false);
			}
			i = i + 1;
		}
		return (true);
	}

	void refresh_case(string[] words)
	{
		int new_x = -1;
		int new_y = -1;
		int r0 = -1;
		int r1 = -1;
		int r2 = -1;
		int r3 = -1;
		int r4 = -1;
		int r5 = -1;
		int r6 = -1;
		
		Int32.TryParse(words[1], out new_x);
		Int32.TryParse(words[2], out new_y);
		Int32.TryParse(words[3], out r0);
		Int32.TryParse(words[4], out r1);
		Int32.TryParse(words[5], out r2);
		Int32.TryParse(words[6], out r3);
		Int32.TryParse(words[7], out r4);
		Int32.TryParse(words[8], out r5);
		Int32.TryParse(words[9], out r6);

		if (!MapCreated) {
			writeMapToServ ();
		}
		else if (new_x <= -1 || new_y <= -1 || new_x > xmap || new_y > ymap)
			Debug.Log ("Bad x y.");
		else if (r0 <= -1 || r1 <= -1 || r2 <= -1 || r3 <= -1 || r4 <= -1 || r5 <= -1 || r6 <= -1)
			Debug.Log ("Bad input ressources.");
		else {
			GetComponent<GeneratorMap> ().refresh_case (new_x, new_y, r0, r1, r2, r3, r4, r5, r6);
			Debug.Log ("Block x=" + new_x + " | y=" + new_y + " is updated.");
		}

	}

	void refresh_map(string x, string y)
	{
		int new_x = 0;
		int new_y = 0;

		Int32.TryParse(x, out new_x);
		Int32.TryParse(y, out new_y);

		if (MapCreated == true)
			Debug.Log ("Map already created.");
		else if (new_x > 0 && new_y > 0) {
			GetComponent<GeneratorMap> ().createMap (new_x, new_y);
			Debug.Log ("Map created with x=" + new_x + " and y=" + new_y);
			MapCreated = true;
			xmap = new_x;
			ymap = new_y;
		}
		else
			Debug.Log ("Bad x y");
	}

	int check_team(string team)
	{
		int i = 0;

		while (teams != null && i != teams.Length) {
			if (teams[i] == team)
			{
				Debug.Log("Team {" + team + "} as already created.");
				return (1);
			}
			i = i + 1;
		}
		if (teams == null)
		{
			teams = new String[1];
			teams[0] = team;
		}	
		else {
			Array.Resize (ref teams, teams.Length + 1);
			teams [teams.Length - 1] = team;
		}
		Debug.Log ("Team {" + team + "} succefull added. Team Length:" + teams.Length);
		return (0);
	}

	void writeMapToServ()
	{
		GetComponent<Socket>().writeToServ ("msz");
	}
}
