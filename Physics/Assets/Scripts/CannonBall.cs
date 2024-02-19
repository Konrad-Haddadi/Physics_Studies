using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class CannonBall : MonoBehaviour
{
    private Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();

    }    

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
            rb.AddForce(transform.forward * 10, ForceMode.Impulse);
    }
}