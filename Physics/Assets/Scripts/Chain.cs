using System.Collections.Generic;
using UnityEngine;

public class Chain : MonoBehaviour
{    
    [SerializeField] private HingeJoint chainLink = null;    
    [SerializeField] private GameObject hand = null;

    public List<HingeJoint> joints = new();

    public bool swing;

    private void Start()
    {
        swing = false;
        chainLink.gameObject.SetActive(false);
    }

    private void Update()
    {
        if (swing && Input.GetKeyDown(KeyCode.Space))
            SwingChange(null);
    }

    public void SwingChange(Rigidbody targetObj)
    { 
        swing = !swing;  

        if(joints.Count > 0)
        {
            for (int i = 0; i < joints.Count; i++)
            {
                Destroy(joints[i].gameObject);
            }
        }       

        joints.Clear();       

        if (swing && targetObj)
        {
            float dist = Vector3.Distance(targetObj.transform.position, hand.transform.position);

            for (int i = 0; i < dist - 2; i++)
            {
                HingeJoint newJoint = Instantiate(chainLink);

                if(i== 0)
                {
                    newJoint.connectedBody = targetObj;
                    newJoint.transform.position = targetObj.transform.position - Vector3.up;
                }
                else
                {
                    newJoint.connectedBody = joints[i - 1].GetComponent<Rigidbody>();
                    newJoint.transform.position = joints[i - 1].transform.position - (targetObj.transform.position - hand.transform.position) / dist;
                }

                newJoint.gameObject.SetActive(true);
                joints.Add(newJoint);
            }

            HingeJoint joint = hand.GetComponent<HingeJoint>();

            if (!joint)
                joint = hand.AddComponent<HingeJoint>();

            joint.anchor = Vector3.up;
            joint.autoConfigureConnectedAnchor = false;

            joint.connectedBody = joints[joints.Count - 1].GetComponent<Rigidbody>();
        }       
    }   
}
