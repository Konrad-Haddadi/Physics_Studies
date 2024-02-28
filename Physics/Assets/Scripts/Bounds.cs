using UnityEngine;

public class Bounds : MonoBehaviour
{
    [SerializeField] float timer = 0;
    [SerializeField] float maxRespawnTime = 2;

    [SerializeField] bool respawn;

    [SerializeField] Player thisPlayer = null;

    private void Update()
    {
        if(respawn)
        {
            timer += Time.deltaTime;

            if (timer > maxRespawnTime)
                Respawn();
        }
    }

    private void Respawn()
    {
        thisPlayer.ResetPos();
        respawn = false;
        timer = 0;

        thisPlayer = null;
    }

    private void OnTriggerEnter(Collider other)
    {
        Player player = other.GetComponentInParent<Player>();

        if (!player)
            player = other.GetComponent<Player>();

        if(player)
        {
            thisPlayer = player;
            respawn = true;
        }
    }
}
