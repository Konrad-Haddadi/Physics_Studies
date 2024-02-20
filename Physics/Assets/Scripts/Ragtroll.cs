using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Ragtroll : MonoBehaviour
{
    private Animator animator;
    private Player player;

    [SerializeField] private Rigidbody hips;

    public List<Rigidbody> rigidbodies = new List<Rigidbody>();

    public bool RagtrollOn
    {
        get { return !animator; }
        set
        {
            animator.enabled = !value;

            foreach (Rigidbody r in rigidbodies)
                r.isKinematic = !r.isKinematic;
        }
    }

    private void Start()
    {
        player = GetComponent<Player>();
        animator = GetComponent<Animator>();

        foreach (Rigidbody r in rigidbodies)
        {
            r.isKinematic = true;
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            RagtrollOn = !RagtrollOn;            
        }
    }
}
