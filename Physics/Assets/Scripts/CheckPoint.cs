using UnityEngine;

public class CheckPoint : MonoBehaviour
{
    [SerializeField] private GameObject rope;
    [SerializeField] private bool win;

    private void OnTriggerEnter(Collider other)
    {
        Player player = other.GetComponent<Player>();

        if(player)
        {
            player.SetNewCheckPoint(this);
            Destroy(rope);

            if (win)
                Application.Quit();
        }
    }
}
