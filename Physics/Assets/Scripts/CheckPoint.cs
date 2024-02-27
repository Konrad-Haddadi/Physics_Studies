using UnityEngine;

public class CheckPoint : MonoBehaviour
{
    [SerializeField] private GameObject rope;
    [SerializeField] private bool win;
    bool triggered = false;

    private void OnTriggerEnter(Collider other)
    {
        Player player = other.GetComponent<Player>();

        if(player)
        {
            if (triggered)
                return;

            triggered = true;
            player.SetNewCheckPoint(this);
            Destroy(rope);

            if (win)
                Application.Quit();
        }
    }
}
