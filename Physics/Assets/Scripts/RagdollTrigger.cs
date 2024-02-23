using UnityEngine;

public class BHitTrigger : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        Ragtroll ragtroll = other.gameObject.GetComponentInParent<Ragtroll>();

        if (ragtroll)
        {
            ragtroll.RagtrollOn = true;
        }
    }
}
