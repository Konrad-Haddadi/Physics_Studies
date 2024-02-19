using UnityEngine;

[RequireComponent(typeof(CharacterController), typeof(Animator))]

public class Player : MonoBehaviour
{
    public float forwardSpeed = 160f;
    public float rotationSpeed = 16f;
    public float pushPower = 2f;
    public float jumpPower = 2f;

    [HideInInspector] public CharacterController controller = null;
    [HideInInspector] public Animator animator = null;
    public Rigidbody rb;

    public bool isJumping = false;
    public float jumpTimer = 0;

    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        float horizontal = Input.GetAxis("Horizontal");

        controller.SimpleMove(transform.up * Time.deltaTime);
        animator.SetFloat("Speed", horizontal * forwardSpeed * Time.deltaTime);      
        
        if(Input.GetKey(KeyCode.Space) && !isJumping)
            Jump();

        if (isJumping)
            JumpTimer();
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        Rigidbody body = hit.collider.attachedRigidbody;

        if (!body || body.isKinematic || hit.moveDirection.y < -0.3f)
            return;

        Vector3 pushDirection = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);
        body.AddForce(pushDirection * pushPower, ForceMode.Impulse);
    }

    private void Jump()
    {
        controller.enabled = false;
        animator.enabled = false;

        isJumping = true;

        rb.AddForce( rb.transform.up * (jumpPower * 10), ForceMode.Impulse);
    }

    private void JumpTimer()
    {
        jumpTimer += Time.deltaTime;

        transform.position = rb.transform.localPosition;

        if (jumpTimer > 2)
        {
            jumpTimer = 0;

            controller.enabled = true;
            animator.enabled = true;

            isJumping = false;
        }
    }
}
