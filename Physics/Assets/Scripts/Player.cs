using TMPro;
using UnityEngine;
using UnityEngine.UI;

[RequireComponent(typeof(Animator))]

public class Player : MonoBehaviour
{
    private float jumpPowerMax;
    private bool up;

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

    public Canvas canvas = null;
    public Image bar = null; 

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        capCollider = GetComponent<CapsuleCollider>();
        rb = GetComponent<Rigidbody>();
        jumpPowerMax = jumpPower;
        up = false;
        canvas.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        float horizontal = Input.GetAxis("Horizontal");
        
        animator.SetFloat("Speed", horizontal);

        if(!isJumping)
            transform.position += transform.forward * horizontal * forwardSpeed * Time.deltaTime;

        if(Input.GetKey(KeyCode.Space))
        {
            if(up)
            {
                jumpPower += Time.deltaTime * 20;

                if (jumpPower >= jumpPowerMax)
                    up = false;
            }
            else
            {
                jumpPower -= Time.deltaTime * 20;

                if (jumpPower <= 0)
                    up = true;
            }

            if(!isJumping)            
                canvas.enabled = true;

            bar.fillAmount = jumpPower / jumpPowerMax;
        }

        if(Input.GetKeyUp(KeyCode.Space))
        {
            isJumping = !isJumping;
            canvas.enabled = false;

            capCollider.enabled = !isJumping;
            rb.isKinematic = isJumping;

            if (isJumping)
            {
                animator.enabled = false;
                hips.velocity += transform.up * (jumpPower * 5);
                hips.velocity += transform.forward * horizontal * jumpPowerMax * 5;
            }
            else
            {
                transform.position = new Vector3(hips.transform.position.x, hips.transform.position.y, transform.position.z);
                animator.enabled = true;
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
