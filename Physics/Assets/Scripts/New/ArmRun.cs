using UnityEngine;

class ArmRun : StateMachineBehaviour
{
    [SerializeField] float timer = 0;
    [SerializeField, Range(0, 1)] private float animationReset;
    public override void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
         float move = Input.GetAxis("Horizontal");

        if (move != 0)
        {
            if (timer < 1)
                timer += Time.deltaTime * Mathf.Abs(move);
        }
        else
            timer = Mathf.Lerp(timer,0, animationReset);

        animator.SetFloat("RunningArm", timer);
    }
}
