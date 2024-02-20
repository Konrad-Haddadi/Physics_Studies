using UnityEngine;

public class Chain : MonoBehaviour
{
    public HingeJoint endChain = null;
    public HingeJoint midChain = null;
    public HingeJoint handChain = null;
    public GameObject hand = null;


    bool swing;

    private void Start()
    {
        swing = false;
        endChain.gameObject.SetActive(false);
        midChain.gameObject.SetActive(false);
        handChain.gameObject.SetActive(false);
    }

    private void Update()
    {
        if (swing && Input.GetKeyDown(KeyCode.Space))
            SwingChange(false);
    }

    public void SwingChange(bool _val)
    {
        if(_val)
        {
            midChain.transform.position = endChain.transform.position - Vector3.up;
            handChain.transform.position = midChain.transform.position - Vector3.up;
            return;
        }

        swing = !swing;  

        endChain.gameObject.SetActive(swing);
        midChain.gameObject.SetActive(swing);
        handChain.gameObject.SetActive(swing);


        if (swing)
        {
            HingeJoint joint = hand.GetComponent<HingeJoint>();

            if (!joint)
                joint = hand.AddComponent<HingeJoint>();

            joint.anchor = Vector3.up;
            joint.autoConfigureConnectedAnchor = false;

            joint.connectedBody = handChain.GetComponent<Rigidbody>();
        }
        else
            endChain.connectedBody = null;

    }   

    public void ChangePoint()
    {
        midChain.transform.position = endChain.transform.position - Vector3.up;
        handChain.transform.position = midChain.transform.position - Vector3.up;
    }
}
