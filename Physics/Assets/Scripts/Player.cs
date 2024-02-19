using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(CharacterController), typeof(Animator))]

public class Player : MonoBehaviour
{
    public float forwardSpeed = 160f;
    public float rotationSpeed = 16f;
    public float pushPower = 2f;

    public CharacterController controller = null;
    [HideInInspector] public Animator animator = null;

    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        float vertical = Input.GetAxis("Vertical");    
        float horizontal = Input.GetAxis("Horizontal");

        controller.SimpleMove(transform.up * Time.deltaTime);
        transform.Rotate(transform.up, horizontal * rotationSpeed * Time.deltaTime);
        animator.SetFloat("Speed", vertical * forwardSpeed * Time.deltaTime);

        
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        Rigidbody body = hit.collider.attachedRigidbody;

        if (!body || body.isKinematic || hit.moveDirection.y < -0.3f)
            return;

        Vector3 pushDirection = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);
        body.AddForce(pushDirection * pushPower, ForceMode.Impulse);
    }
}
