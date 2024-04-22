using UnityEngine;

class SprintTacker : StateMachineBehaviour
{
    float currentExcitement = 0;
    [Range(1,100)] public float speedReduce;

    public override void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        if (Input.GetAxis("Horizontal") != 0)
        {
            if (currentExcitement < 1)
                currentExcitement += Time.deltaTime;
        }
        else if (currentExcitement > 0)
            currentExcitement -= Time.deltaTime * speedReduce;
        else
            currentExcitement = 0;

        animator.SetFloat("Excitement", currentExcitement);
    }
}

