using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundDestroy : MonoBehaviour
{
    AudioSource m_Source;

    private void Start()
    {
        m_Source= GetComponent<AudioSource>();
    }

    void Update()
    {
        if (!m_Source.isPlaying)
            Destroy(gameObject);
    }
}
