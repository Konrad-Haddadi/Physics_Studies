using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TransformCopy : MonoBehaviour
{
    [SerializeField] private Transform other;

    [SerializeField] private bool x = false;
    [SerializeField] private bool y = false;
    [SerializeField] private bool z = false;

    void Update()
    {
        Vector3 pos = transform.position;

        if(x)
            pos = new Vector3(other.position.x, pos.y, pos.z);

        if(y)
            pos = new Vector3(pos.x, other.position.y, pos.z);

        if(z)
            pos = new Vector3(pos.x, pos.y, other.position.z);

        transform.position = Vector3.Lerp(transform.position,pos, Time.deltaTime * 5);
    }
}
