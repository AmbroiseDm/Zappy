using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Egg : MonoBehaviour {

	private int x;
	private int y;
	private int id;
	private int idPlayer;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public int getID()
	{
		return (id);
	}

	public void createEgg(int x0, int y0, int id0, int id1)
	{
		x = x0;
		y = y0;
		id = id0;
		idPlayer = id1;
		transform.position = new Vector3 (x, 1, y);
	}

	public void Die()
	{
		x = -1;
		y = -1;
		id = -1;
		idPlayer = -1;
		transform.position = new Vector3 (-9999, -9999, -9999);
	}

	public void Hatches()
	{
		Material newMat = Resources.Load("EGG_HATCHED", typeof(Material)) as Material;
		GetComponent<Renderer>().material = newMat;
	}
}
