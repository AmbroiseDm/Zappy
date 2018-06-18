using UnityEngine;
using System.Collections;

public class myCamera : MonoBehaviour
{
	public Transform target;
	public float turnSpeed = 3.0f;
	public float panSpeed = 3.0f;
	public float zoomSpeed = 3.0f;	

	private Vector3 mousePos;
	private bool isPanning;		
	private bool isRotating;
	private bool isZooming;		

	void Update () 
	{
		if(Input.GetMouseButtonDown(0))
		{
			mousePos = Input.mousePosition;
			isRotating = true;
		}

		if(Input.GetMouseButtonDown(1))
		{
			mousePos = Input.mousePosition;
			isPanning = true;
		}
		if(Input.GetMouseButtonDown(2))
		{
			mousePos = Input.mousePosition;
			isZooming = true;
		}

		if (!Input.GetMouseButton(0)) 
			isRotating=false;
		if (!Input.GetMouseButton(1)) 
			isPanning=false;
		if (!Input.GetMouseButton(2)) 
			isZooming=false;

		if (isRotating)
		{
			Vector3 pos = Camera.main.ScreenToViewportPoint(Input.mousePosition - mousePos);

			transform.RotateAround(transform.position, transform.right, -pos.y * turnSpeed);
			transform.RotateAround(transform.position, Vector3.up, pos.x * turnSpeed);
		}

		if (isPanning)
		{
			Vector3 pos = Camera.main.ScreenToViewportPoint(Input.mousePosition - mousePos);

			Vector3 move = new Vector3(pos.x * panSpeed, pos.y * panSpeed, 0);
			transform.Translate(move, Space.Self);
		}

		if (isZooming)
		{
			Vector3 pos = Camera.main.ScreenToViewportPoint(Input.mousePosition - mousePos);

			Vector3 move = pos.y * zoomSpeed * transform.forward; 
			transform.Translate(move, Space.World);
		}
	}
}
