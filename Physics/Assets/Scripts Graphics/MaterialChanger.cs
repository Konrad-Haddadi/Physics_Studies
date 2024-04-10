
using UnityEngine;
using UnityEngine.UI;

class MaterialChanger : MonoBehaviour
{
    [SerializeField] private Slider red;
    [SerializeField] private Slider green;
    [SerializeField] private Slider blue;
    [SerializeField] private Slider metallic;
    [SerializeField] private Slider smoothness;

    [SerializeField] private Material mat;
    [SerializeField] private Image color;

    private void Start()
    {
        red.onValueChanged.AddListener(Red);
        green.onValueChanged.AddListener(Green);
        blue.onValueChanged.AddListener(Blue);

        red.value = mat.color.r;
        green.value = mat.color.g;
        blue.value = mat.color.b;
    }

    private void Update()
    {
        color.color = mat.color;
    }


    public void Red(float _red)
    {
        mat.color = new Color(_red, mat.color.g, mat.color.b, 1);
    }

    public void Green(float _green)
    {
        mat.color = new Color(mat.color.r, _green, mat.color.b, 1);
    }

    public void Blue(float _blue)
    {
        mat.color = new Color(mat.color.r, mat.color.g, _blue ,1);
    }

    public void Metallic(float _metallic)
    {
        
    }

}

