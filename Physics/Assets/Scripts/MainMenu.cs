using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    [SerializeField] private Button play;
    [SerializeField] private Button quit;
    [SerializeField] private Camera gameCamera;
    [SerializeField] private GameObject targetLocation;
    [SerializeField] private ParticleSystem fireworks;

    [SerializeField] private Player player;
    [SerializeField] private AnimationCurve tweenCurve = AnimationCurve.EaseInOut(0, 0, 1, 1);

    // Start is called before the first frame update
    void Start()
    {
        gameCamera.GetComponent<TransformCopy>().enabled = false;

        quit.onClick.AddListener(Application.Quit);
        play.onClick.AddListener(PlayGame);
    }


    private void PlayGame()
    {
        Instantiate(fireworks);
        play.gameObject.SetActive(false);
        quit.gameObject.SetActive(false);

        player.animator.SetBool("Play", true);
        player.rb.isKinematic = false;
        StartCoroutine(CameraMove_CR());
    }

    public IEnumerator CameraMove_CR()
    {
        float timer = 0;
        float timeMax = 1;

        while (timer < timeMax)
        {
            Vector3 startCamPos = gameCamera.transform.position;
            Quaternion startCamRot = gameCamera.transform.rotation;

            Vector3 endCamPos = targetLocation.transform.position;
            Quaternion endCamRot = targetLocation.transform.rotation;


            while (timer < timeMax)
            {
                float factor = Mathf.Clamp01(timer / timeMax);
                float t = tweenCurve.Evaluate(factor);

                gameCamera.transform.position = Vector3.Lerp(startCamPos, endCamPos, t);
                gameCamera.transform.rotation = Quaternion.Lerp(startCamRot, endCamRot, t);

                yield return null;

                timer += Time.deltaTime;
            }

            gameCamera.GetComponent<TransformCopy>().enabled = true;

            yield return null;
        }
    }
}
