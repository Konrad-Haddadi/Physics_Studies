using UnityEngine;

[RequireComponent(typeof(Animator))]

public class Player : MonoBehaviour
{
    public float forwardSpeed = 160f;
    public float rotationSpeed = 16f;
    public float pushPower = 2f;
    public float jumpPower = 2f;

    [HideInInspector] public Animator animator = null;
    public Rigidbody rb;
    public Rigidbody hips;
    public CapsuleCollider capCollider = null;

    public bool isJumping = false;
    public float jumpTimer = 0;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        capCollider = GetComponent<CapsuleCollider>();
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        float horizontal = Input.GetAxis("Horizontal");

        animator.SetFloat("Speed", horizontal);

        if(!isJumping)
            transform.position += transform.forward * horizontal * forwardSpeed * Time.deltaTime;


        if (Input.GetKeyDown(KeyCode.Space))
        {
            isJumping = !isJumping;
            
            capCollider.enabled = !isJumping;
            rb.isKinematic = isJumping;

            if (isJumping)
            {
                animator.enabled = !isJumping;
                hips.velocity += (Vector3.up + transform.forward * horizontal) * (jumpPower * 5);            
            }
            else
            {
                transform.position = new Vector3(hips.transform.position.x, hips.transform.position.y, transform.position.z);
                animator.enabled = !isJumping;
            }            
        }


        animator.SetBool("Fall", isJumping);
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        Rigidbody body = hit.collider.attachedRigidbody;

        if (!body || body.isKinematic || hit.moveDirection.y < -0.3f)
            return;

        Vector3 pushDirection = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);
        body.AddForce(pushDirection * pushPower, ForceMode.Impulse);
    }

    private void JumpTimer()
    {
        jumpTimer += Time.deltaTime;

        transform.position = rb.transform.localPosition;

        if (jumpTimer > 2)
        {

            jumpTimer = 0;
            isJumping = false;
        }
    }
}
