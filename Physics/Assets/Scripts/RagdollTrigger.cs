using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RagdollTrigger : MonoBehaviour
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
