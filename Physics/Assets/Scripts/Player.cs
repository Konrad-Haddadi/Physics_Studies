using TMPro;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.XR;

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

    public bool ragdolled = false;
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

        if (ragdolled)
        {
            if (Input.GetKey(KeyCode.A))
                rb.AddForce(Vector3.right * -5, ForceMode.Acceleration);

            if (Input.GetKey(KeyCode.D))
                rb.AddForce(Vector3.right * 5, ForceMode.Acceleration);
        }
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
        ragdolled = true;
        canvas.enabled = false;

        capCollider.enabled = !ragdolled;
        rb.isKinematic = ragdolled;

        animator.enabled = false;
        hips.velocity += _force * 10;                
    }

    private void Controls()
    {
        float horizontal = Input.GetAxis("Horizontal");

        animator.SetFloat("Speed", horizontal);

        if (!ragdolled)
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

            if (!ragdolled)
                canvas.enabled = true;

            bar.fillAmount = jumpPower / jumpPowerMax;
        }

        if (Input.GetKeyUp(KeyCode.Space))
        {
            ragdolled = !ragdolled;
            canvas.enabled = false;

            capCollider.enabled = !ragdolled;
            rb.isKinematic = ragdolled;

            if (ragdolled)
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

        animator.SetBool("Fall", ragdolled);
    }

    public void ResetPos()
    {
        ragdolled = false;
        canvas.enabled = false;

        capCollider.enabled = !ragdolled;
        rb.isKinematic = ragdolled;      
        
        transform.position = new Vector3(hips.transform.position.x, transform.position.y, transform.position.z);
        animator.enabled = true;  

        animator.SetBool("Fall", ragdolled);
        chain.SwingChange(null);
    }
}