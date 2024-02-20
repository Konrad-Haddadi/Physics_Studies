using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

[RequireComponent(typeof(Camera))]
public class Raycaster : MonoBehaviour
{
    Camera camera = null;
    public int layerMask;
    public Chain grapple;

    private void Awake()
    {
        camera = GetComponent<Camera>();
        string[] layers = { "Grapple" };
        layerMask = LayerMask.GetMask(layers);        
    }

    private void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            RaycastHit hit;
            Ray ray = camera.ScreenPointToRay(Input.mousePosition);

            if(Physics.Raycast(ray, out hit, 1000, layerMask))
            {
                Rigidbody rb = hit.collider.GetComponent<Rigidbody>();

                if(rb)
                {
                    if (grapple.endChain.connectedBody == rb)
                    {
                        grapple.endChain.connectedBody = rb;
                        grapple.endChain.transform.position = rb.transform.position - Vector3.up;
                        grapple.SwingChange(true);
                    }
                    else
                    {
                        grapple.endChain.connectedBody = rb;
                        grapple.endChain.transform.position = rb.transform.position - Vector3.up;
                        grapple.SwingChange(false);
                    }
                                       
                }
            }
        }
    }
}
