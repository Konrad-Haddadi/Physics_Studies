using UnityEngine;
using UnityEngine.UI;

class HeadAccessory : MonoBehaviour
{
    [SerializeField] private Material mat;

    public Button next;
    public GameObject sliders;

    [Header("Mesh Editor")]
    public Slider red;
    public Slider green;
    public Slider blue;
    public Slider metallic;
    public Slider smoothness;

    private Player player;
    private int count;

    private void Start()
    {
        count = 0;
        player = FindObjectOfType<Player>();
        next.onClick.AddListener(Next);

        red.onValueChanged.AddListener(SetRed);
        green.onValueChanged.AddListener(SetGreen);
        blue.onValueChanged.AddListener(SetBlue);
        metallic.onValueChanged.AddListener(SetMetallic);
        smoothness.onValueChanged.AddListener(SetSmoothness);

        red.value = mat.color.r;
        green.value = mat.color.g;
        blue.value = mat.color.b;

        metallic.value = mat.GetFloat("_Metallic");
        smoothness.value = mat.GetFloat("_Glossiness");

    }
    
    public void Next()
    {
        if (count + 1 < player.accessories.Count)
            count++;
        else
            count = 0;

        Destroy(player.currentAccessory);
        player.currentAccessory = Instantiate(player.accessories[count], player.headPos.transform);
    }

    private void SetRed(float _val)
    {
        Color color = new(_val, mat.color.g, mat.color.b);

        mat.color = color;
    }

    private void SetGreen(float _val)
    {
        Color color = new(mat.color.r, _val, mat.color.b);

        mat.color = color;
    }

    private void SetBlue(float _val)
    {
        Color color = new(mat.color.r, mat.color.g, _val);

        mat.color = color;
    }

    private void SetMetallic(float _val)
    {
        mat.SetFloat("_Metallic", _val);
    }

    private void SetSmoothness(float _val)
    {
        mat.SetFloat("_Glossiness", _val);

    }

}

