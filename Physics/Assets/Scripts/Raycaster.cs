using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Camera))]
public class Raycaster : MonoBehaviour
{
    Camera camera = null;
    public float force = 10;
    public int layerMask;

    private void Awake()
    {
        camera = GetComponent<Camera>();
        string[] layers = { "Ragdoll" };
        layerMask = LayerMask.GetMask(layers);
    }

    private void Update()
    {
        if(Input.GetMouseButtonDown(0))
        {
            RaycastHit hit;
            Ray ray = camera.ScreenPointToRay(Input.mousePosition);

            if(Physics.Raycast(ray, out hit, 500, layerMask))
            {
                Rigidbody rb = hit.collider.GetComponent<Rigidbody>();

                if(rb)
                {
                    rb.AddForce(ray.direction * force);
                }
            }
        }
    }
}
