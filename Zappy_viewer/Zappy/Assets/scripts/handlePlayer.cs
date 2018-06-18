using UnityEngine;
using System.Collections;

public class handlePlayer : MonoBehaviour 
{
	private bool walk;
	private bool victory;
	private bool die;


	void Start ()
	{
		walk = false;
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (walk == false) {
			GetComponent<Animation> ().Stop ("walk");
			GetComponent<Animation> ().Play ("idle");
		} else {
			GetComponent<Animation> ().Stop ("idle");
			GetComponent<Animation> ().Play ("walk");
		}
	}

	public void Nord()
	{
		transform.eulerAngles = new Vector3 (0, 0, 0);
	}

	public void Sud()
	{
		transform.eulerAngles = new Vector3 (0, 180, 0);
	}

	public void Est()
	{
		transform.eulerAngles = new Vector3 (0, 90, 0);
	}

	public void Ouest()
	{
		transform.eulerAngles = new Vector3 (0, -90, 0);
	}

	public void move(int x0, int y0)
	{
		walk = true;
		transform.position  = new Vector3(x0 , 1, y0);
	}
}
