using UnityEngine;

public class RagdollHitTrigger : MonoBehaviour
{
    public Rigidbody rb = null;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    private void OnCollisionEnter(Collision collision)
    {
        Player player = collision.gameObject.GetComponentInParent<Player>();

        if (player)
        {
            player.RagDoll(rb.angularVelocity);
        }
    }
}
