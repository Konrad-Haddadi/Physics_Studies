using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundDestroy : MonoBehaviour
{
    AudioSource m_Source;
    private float timer = 0;

    [SerializeField] private bool useTimer;
    [SerializeField] private bool loop;
    [SerializeField] private float audioLength;
    [SerializeField] private float startTimer;

    private void Start()
    {
        m_Source= GetComponent<AudioSource>();
        m_Source.time = startTimer;
        timer = 0;

        m_Source.loop = loop;   
    }

    void Update()
    {
        if(useTimer)
        {
            timer += Time.deltaTime;

            if(timer > audioLength)
            {
                if(loop)
                {
                    m_Source.Play();
                    timer = 0;
                }
                else
                    Destroy(gameObject);
            }
        }
        else if (!m_Source.isPlaying)
            Destroy(gameObject);
    }
}
