using UnityEngine;
using System.Collections;

public class GeneratorMap : MonoBehaviour 
{
	int r0, r1, r2, r3, r4, r5, r6 = 0;
	private string[] name = new string[7];
	private GameObject [][] map = null;
	private GameObject [] crystal = null;
	private GameObject cube;

	void Start () 
	{
	}
 
	void Update () 
	{

	}

	public void init_resource()
	{
		crystal = new GameObject[7];
		crystal[0] = Instantiate(Resources.Load("Food")) as GameObject;
		crystal[1] = Instantiate(Resources.Load("Linemate")) as GameObject;
		crystal[2] = Instantiate(Resources.Load("Derau")) as GameObject;
		crystal[3] = Instantiate(Resources.Load("Sibur")) as GameObject;
		crystal[4] = Instantiate(Resources.Load("Mendiane")) as GameObject;
		crystal[5] = Instantiate(Resources.Load("Phiras")) as GameObject;
		crystal[6] = Instantiate(Resources.Load("Thystame")) as GameObject;

		name [0] = "Nourriture";
		name [1] = "Linemate";
		name [2] = "Derau";
		name [3] = "Sibur";
		name [4] = "Mendiane";
		name [5] = "Phiras";
		name [6] = "Thystame";
	}

	public int generate_nb()
	{
		return (Random.Range (0, 20));
	}

	public void refresh_case(int x, int y, int r0, int r1, int r2, int r3, int r4, int r5, int r6)
	{
		map [x] [y].GetComponent<block>().setRessources (r0, r1, r2, r3, r4, r5, r6);
	}

	public void AddRessources(int ressources, int x0, int y0)
	{
		map [x0] [y0].GetComponent<block> ().addRessources (ressources);
	}

	public void removeRessources(int ressources, int x0, int y0)
	{
		map [x0] [y0].GetComponent<block> ().removeRessources (ressources);
	}

	private void inc_resource(int offset)
	{
		if (name[offset].Equals("Nourriture"))
			r0++;
		else if (name [offset].Equals("Linemate"))
			r1++;
		else if (name [offset].Equals("Derau"))
			r2++;
		else if (name [offset].Equals("Sibur"))
			r3++;
		else if (name [offset].Equals("Mendiane"))
			r4++;
		else if (name [offset].Equals("Phiras"))
			r5++;
		else if (name [offset].Equals("Thystame"))
			r6++;
	}

	public void createMap(int width, int height)
	{
		int i = 0;
		int nb = 0;
		uint y = 0;
		uint x = 0;

 
		map = new GameObject[width][];
		while (x < width)
		{
			map[x] = new GameObject[height];
			y = 0;
			while (y < height) 
			{
				cube = Instantiate(Resources.Load("grass")) as GameObject;
				cube.GetComponent<block> ().posBlock (x, 0, y);
				init_resource ();
				nb = generate_nb();
				for (int idx = 0; idx < nb; idx++) 
				{
					i = Random.Range (0, 7);
					crystal [i].GetComponent<Crystal> ().posResource (x, 0.7F, y);
					inc_resource (i);
				}
				map[x][y] = cube;
				refresh_case ((int)x, (int)y, r0, r1, r2, r3, r4, r5, r6);
				y++;
			}
			x++;
		}	
	}
}
