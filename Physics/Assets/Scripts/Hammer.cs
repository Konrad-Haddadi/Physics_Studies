using UnityEngine;

public class Hammer : MonoBehaviour
{
    public HingeJoint hingeJoint;    

    private void OnCollisionEnter(Collision collision)
    {
        Player player = collision.gameObject.GetComponentInParent<Player>();

        if(player)
        {
            player.RagDoll(player.transform.right * (hingeJoint.velocity / 10));
        }
    }
}
