using UnityEngine;
using UnityEngine.AI;

public class EnemyAI : MonoBehaviour
{
    [SerializeField, Range(5,10)] private float visionDist = 5;
    [SerializeField] private PlayerComponents player = null;

    private NavMeshAgent agent;
    private SphereCollider visionCollider;

    void Start()
    {
        agent = GetComponentInChildren<NavMeshAgent>();
        visionCollider = GetComponent<SphereCollider>();
    }

    void Update()
    {
        if(visionCollider.radius != visionDist)
            visionCollider.radius = visionDist;

        if(player)
        {
            if (!agent.hasPath)
                agent.SetDestination(player.transform.position);

            float dist = Vector3.Distance(player.transform.position, agent.destination);

            if(dist > 2)
                agent.SetDestination(player.transform.position);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (player)
            return;
        
        player = other.GetComponentInParent<PlayerComponents>();
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.GetComponentInParent<PlayerComponents>())
        {
            player = null;
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(transform.position, visionDist);
    }
}
