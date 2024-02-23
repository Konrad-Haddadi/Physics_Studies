using UnityEngine;

public class Bounds : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        Player player = other.transform.gameObject.GetComponentInParent<Player>();

        if(player)
        {
            player.ResetPos();
        }
    }
}
