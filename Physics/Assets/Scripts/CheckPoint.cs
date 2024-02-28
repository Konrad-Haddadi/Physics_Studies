using UnityEngine;
using UnityEngine.UIElements;

public class CheckPoint : MonoBehaviour
{
    [SerializeField] private bool win;
    [SerializeField] private Cloth rope;
    [SerializeField] private ParticleSystem particles;
    [SerializeField] private GameObject rightStand;
    [SerializeField] private GameObject leftStand;


    bool triggered = false;

    private void Start()
    {
        rope.capsuleColliders[0] = FindObjectOfType<Player>().capCollider;
    }

    private void OnTriggerEnter(Collider other)
    {
        Player player = other.GetComponent<Player>();

        if(player)
        {
            if (triggered)
                return;

            triggered = true;
            player.SetNewCheckPoint(this);
            Destroy(rope.gameObject);

            Instantiate(particles, rightStand.transform.position, particles.transform.rotation);
            Instantiate(particles, leftStand.transform.position, particles.transform.rotation);

            if (win)
                Application.Quit();
        }
    }
}
