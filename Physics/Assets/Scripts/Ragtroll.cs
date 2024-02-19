using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Ragtroll : MonoBehaviour
{
    private Animator animator;

    public List<Rigidbody> rigidbodies = new List<Rigidbody>();

    public bool RagtrollOn
    {
        get { return !animator; }
        set
        {
            animator.enabled = !value;

            foreach (Rigidbody r in rigidbodies)
                r.isKinematic = !value;
        }
    }

    private void Start()
    {
        animator = GetComponent<Animator>();
        foreach (Rigidbody r in rigidbodies)
            r.isKinematic = true;
    }
}
