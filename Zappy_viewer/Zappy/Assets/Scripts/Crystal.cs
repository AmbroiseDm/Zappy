using UnityEngine;
using System.Collections;

public class Crystal : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void posResource(uint a, float b, uint c)
	{
		float posPositive1 = Random.Range (0.0F, 0.5F);
		float posNegatif1 = Random.Range (-0.0F, -0.5F);
		float posPositive2 = Random.Range (0.0F, 0.5F);
		float posNegatif2 = Random.Range (-0.0F, -0.5F);
		int i = Random.Range (0, 1000);

		if (i % 2 == 0)
			transform.position = new Vector3 (a + posNegatif1, b, c + posPositive2);
		else
			transform.position = new Vector3 (a - posPositive1, b, c + posNegatif2);		
	}
}
