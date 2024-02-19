using UnityEngine;

public class Car : MonoBehaviour
{
    [SerializeField] private HingeJoint fontLeft;
    [SerializeField] private HingeJoint fontRight;
    [SerializeField] private HingeJoint backLeft;
    [SerializeField] private HingeJoint backRight;

    public float rotSpeed;

    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.A))
        {
            fontLeft.axis += new Vector3(0,0, Time.deltaTime * rotSpeed);
            fontRight.axis += new Vector3(0,0, Time.deltaTime * rotSpeed);
        }

        if(Input.GetKeyDown(KeyCode.D))
        {
            fontLeft.axis -= new Vector3(0, 0, Time.deltaTime * rotSpeed);
            fontRight.axis -= new Vector3(0, 0, Time.deltaTime * rotSpeed);
        }
            
        if(Input.GetKeyDown(KeyCode.W))
        {

        }
            
        if(Input.GetKeyDown(KeyCode.S))
        {

        }
    }
}
