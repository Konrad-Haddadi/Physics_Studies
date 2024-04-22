using UnityEngine;
using UnityEngine.UI;

class HeadAccessory : MonoBehaviour
{
    [SerializeField] private Material mat;

    public Button next;
    public Button nextMesh;

    private Player player;
    private int count;

    float r;
    float g;
    float b;

    private void Start()
    {
        count = 0;
        player = FindObjectOfType<Player>();
        next.onClick.AddListener(Next);
        nextMesh.onClick.AddListener(NextMesh);
    }

    private void Update()
    {
        r = Random.Range(0, 1f);
        g = Random.Range(0, 1f);
        b = Random.Range(0, 1f);


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

    public void NextMesh()
    {   
        mat.color = new Color(r,g,b, 1);
    }
}

