using UnityEngine;

class LayerWeight : StateMachineBehaviour
{
    [SerializeField, Range(0,1)] private float targetWeightMax;

    public override void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        animator.SetLayerWeight(layerIndex, targetWeightMax);
    }

   
}

