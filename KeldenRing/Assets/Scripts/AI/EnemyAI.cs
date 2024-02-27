using UnityEngine;
using UnityEngine.AI;
using UnityEngine.LowLevel;

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
            {
                if(LookForPlayer())
                    agent.SetDestination(player.transform.position);
            }

            float dist = Vector3.Distance(player.transform.position, agent.pathEndPosition);

            if(dist > 2)
            {
                if(LookForPlayer())
                    agent.SetDestination(player.transform.position);
                
            }

            Debug.DrawRay(transform.position, (player.transform.position - transform.position) * 5);
        }        
    }

    private bool LookForPlayer()
    {
        RaycastHit hit;
        Ray raycast = new Ray(transform.position, player.transform.position + Vector3.up - transform.position);

        if (Physics.Raycast(raycast, out hit, visionDist))
        {
            if (hit.transform.GetComponent<PlayerComponents>())
                return true;
        }

        return false;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (player)
            return;

        PlayerComponents playerComp = other.GetComponent<PlayerComponents>();

        if(playerComp)
        {
            player = playerComp;
        }      
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.GetComponent<PlayerComponents>())
        {
            player = null;
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(transform.position, visionDist);
    }
}
