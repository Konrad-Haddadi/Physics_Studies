using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClearBackground : MonoBehaviour
{
    Camera cam;
    void Start()
    {
        cam = GetComponent<Camera>();
        cam.backgroundColor = Color.clear;
    }   
}
