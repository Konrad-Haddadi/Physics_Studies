using UnityEngine;

public class Bounds : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        Player player = other.GetComponentInParent<Player>();

        if (!player)
            player = other.GetComponent<Player>();

        if(player)
        {
            player.ResetPos();

            Debug.Log("Reset Player");
        }
    }
}
