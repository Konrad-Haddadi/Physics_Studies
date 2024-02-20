using UnityEngine;

public class Chain : MonoBehaviour
{
    public GameObject endChain = null;
    public GameObject midChain = null;
    public GameObject handChain = null;
    public GameObject hand = null;


    bool swing;

    private void Start()
    {
        swing = false;
        endChain.SetActive(false);
        midChain.SetActive(false);
        handChain.SetActive(false);
    }

    private void Update()
    {
        
    }

    private void OnMouseDown()
    {
        swing = !swing;

        endChain.SetActive(swing);
        midChain.SetActive(swing);
        handChain.SetActive(swing);

        if (swing)
        {
            HingeJoint joint = hand.GetComponent<HingeJoint>();

            if (!joint)
                joint = hand.AddComponent<HingeJoint>();

            joint.anchor = Vector3.up;
            joint.autoConfigureConnectedAnchor = false;

            joint.connectedBody = handChain.GetComponent<Rigidbody>();
        }  
    }
}
