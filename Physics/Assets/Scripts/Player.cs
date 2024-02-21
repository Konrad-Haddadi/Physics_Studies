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

    Chain chain;

    [HideInInspector] public Animator animator = null;
    public Rigidbody rb;
    public Rigidbody hips;
    public CapsuleCollider capCollider = null;

    public bool isJumping = false;
    public float jumpTimer = 0;

    public Canvas canvas = null;
    public Image bar = null; 

    void Start()
    {
        animator = GetComponent<Animator>();
        capCollider = GetComponent<CapsuleCollider>();
        rb = GetComponent<Rigidbody>();
        jumpPowerMax = jumpPower;
        up = false;
        canvas.enabled = false;
        chain = GetComponent<Chain>();
    }

    void Update()
    {
        Controls();

        if (chain.swing)
            RagDoll(Vector3.zero);
    }

    private void OnControllerColliderHit(ControllerColliderHit hit)
    {
        Rigidbody body = hit.collider.attachedRigidbody;

        if (!body || body.isKinematic || hit.moveDirection.y < -0.3f)
            return;

        Vector3 pushDirection = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);
        body.AddForce(pushDirection * pushPower, ForceMode.Impulse);
    }

    public void RagDoll(Vector3 _force)
    {
        isJumping = true;
        canvas.enabled = false;

        capCollider.enabled = !isJumping;
        rb.isKinematic = isJumping;

        animator.enabled = false;
        hips.velocity += _force * 10;                
    }

    private void Controls()
    {
        float horizontal = Input.GetAxis("Horizontal");

        animator.SetFloat("Speed", horizontal);

        if (!isJumping)
            transform.position += transform.forward * horizontal * forwardSpeed * Time.deltaTime;

        if (Input.GetKey(KeyCode.Space))
        {
            if (up)
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

            if (!isJumping)
                canvas.enabled = true;

            bar.fillAmount = jumpPower / jumpPowerMax;
        }

        if (Input.GetKeyUp(KeyCode.Space))
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

    public void ResetPos()
    {
        isJumping = false;
        canvas.enabled = false;

        capCollider.enabled = !isJumping;
        rb.isKinematic = isJumping;      
        
        transform.position = new Vector3(hips.transform.position.x, transform.position.y, transform.position.z);
        animator.enabled = true;  

        animator.SetBool("Fall", isJumping);
        chain.SwingChange(null);
    }
}