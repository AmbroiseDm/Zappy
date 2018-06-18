using UnityEngine;
using System.Collections;

//------------ BIBLIO -------------
using UnityEngine.UI;
// ----------------------------

public class BarreVie
{
    public GameObject gameobject;
    public Color fullLife;
    public Color midLife;
    public Color endLife;

    public BarreVie(Canvas canvas_vie, GameObject healthBar, Color fullLife, Color midLife, Color endLife,
        Vector3 scale, float vie)
    {
        this.gameobject = healthBar;

        this.fullLife = fullLife;
        this.midLife = midLife;
        this.endLife = endLife;

        //this.gameobject = (GameObject)GameObject.Instantiate(healthBar);
        this.gameobject.transform.parent = canvas_vie.gameObject.transform;
        
        this.gameobject.transform.localScale = scale;
        this.gameobject.transform.rotation = healthBar.transform.rotation;

        this.gameobject.GetComponent<Scrollbar>().size = vie;

        this.ColorLife();
    }

    public void set_vie(float vie)
    {
        this.gameobject.GetComponent<Scrollbar>().size = vie;
        this.gameobject.GetComponent<Scrollbar>().value = 0;
        this.ColorLife();
    }

    public void ColorLife()
    {
        float value = this.gameobject.GetComponent<Scrollbar>().size;

        if (value > 0.7)
            this.gameobject.transform.Find("Mask").Find("Sprite").GetComponent<Image>().color = this.fullLife;
        else if (value > 0.3 && value <= 0.7)
            this.gameobject.transform.Find("Mask").Find("Sprite").GetComponent<Image>().color = this.midLife;
        else
            this.gameobject.transform.Find("Mask").Find("Sprite").GetComponent<Image>().color = this.endLife;
    }

    public void set_position(Vector3 pos)
    {
        this.gameobject.transform.position = new Vector3(pos.x, pos.y, 0);
    }
}
