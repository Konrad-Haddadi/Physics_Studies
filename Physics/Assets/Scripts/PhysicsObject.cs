using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PhysicsObject : MonoBehaviour
{
    [Header("Materials")]
    [SerializeField] private Material awakeMat = null;
    [SerializeField] private Material asleepMat = null;

    private Rigidbody rb;

    bool wasSleeping = false;

    void Start()
    {
        rb = GetComponent<Rigidbody>();

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if(rb.IsSleeping() && !wasSleeping && asleepMat != null)
        {
            wasSleeping = true;
            GetComponent<MeshRenderer>().material = asleepMat;
        }

        if (!rb.IsSleeping() && wasSleeping && awakeMat != null)
        {
            wasSleeping = false;
            GetComponent<MeshRenderer>().material = awakeMat;
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
            rb.AddForce(Vector3.up);
    }
}
