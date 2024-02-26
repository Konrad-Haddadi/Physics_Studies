using UnityEngine;

public class AwakeRandomTime : MonoBehaviour
{
    Animator animator;
    float timer = 0;
    float timerMax = 0;

    private void Start()
    {
        animator = GetComponent<Animator>();
        animator.enabled = false;

        timerMax = Random.RandomRange(0, 3);
    }

    private void Update()
    {
        timer += Time.deltaTime;

        if(timer >= timerMax)
        {
            animator.enabled = true;
            Destroy(this);
        }
    }
}
