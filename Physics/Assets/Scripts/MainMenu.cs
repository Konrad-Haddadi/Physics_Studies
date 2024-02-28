using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    [Header("Menu Buttons")]
    [SerializeField] private Button play;
    [SerializeField] private Button quit;

    [Header("Camera Position")]
    [SerializeField] private Camera gameCamera;
    [SerializeField] private GameObject gameLocation;
    [SerializeField] private GameObject menuLocation;

    [Header("Player Reset Point")]
    [SerializeField] private GameObject spawnPoint;
    [SerializeField] private Player player;

    [SerializeField] private ParticleSystem fireworks;

    [Header("Time Starter")]
    [SerializeField] private TMP_Text textTimer;
    [SerializeField] private GameObject countDownSound;
    [SerializeField] private Image loopTimer;
    [SerializeField] private GameObject timerGroup;
    
    private AnimationCurve tweenCurve = AnimationCurve.EaseInOut(0, 0, 1, 1);
    private CheckPointManager checkPointManager;


    // Start is called before the first frame update
    void Start()
    {
        gameCamera.GetComponent<TransformCopy>().enabled = false;

        quit.onClick.AddListener(Application.Quit);
        play.onClick.AddListener(PlayGame);

        checkPointManager = FindObjectOfType<CheckPointManager>();
        timerGroup.gameObject.SetActive(false);
        
    }


    private void PlayGame()
    {
        checkPointManager.ResetGame();

        play.gameObject.SetActive(false);
        quit.gameObject.SetActive(false);

        player.rb.isKinematic = false;

        player.transform.position = spawnPoint.transform.position;

        timerGroup.gameObject.SetActive(true);
        StartCoroutine(CameraMove_CR(gameLocation));

    }

    public void ReturnToMenu()
    {
        play.gameObject.SetActive(true);
        quit.gameObject.SetActive(true);

        player.rb.isKinematic = true;       

        StartCoroutine(CameraMove_CR(menuLocation));
    }

    public IEnumerator CameraMove_CR(GameObject _targetPos)
    {
        float timer = 0;
        float timeMax = 3;

        while (timer < timeMax)
        {            
            Vector3 startCamPos = gameCamera.transform.position;
            Quaternion startCamRot = gameCamera.transform.rotation;

            Vector3 endCamPos = _targetPos.transform.position;
            Quaternion endCamRot = _targetPos.transform.rotation;


            while (timer < timeMax)
            {
                int text = (int)(timeMax + .9f - timer);

                if (timer <= 1)
                    loopTimer.fillAmount = timer / (timeMax - 2);
                else if (timer <= 2)
                    loopTimer.fillAmount = timer - 1/ (timeMax - 2);
                else if (timer <= 3)
                    loopTimer.fillAmount = timer - 2 / (timeMax - 2);

                textTimer.text = text.ToString();

                float factor = Mathf.Clamp01(timer / timeMax);
                float t = tweenCurve.Evaluate(factor);

                gameCamera.transform.position = Vector3.Lerp(startCamPos, endCamPos, t);
                gameCamera.transform.rotation = Quaternion.Lerp(startCamRot, endCamRot, t);

                yield return null;

                timer += Time.deltaTime;
            }


            player.animator.SetBool("Play", !player.animator.GetBool("Play"));

            if(player.animator.GetBool("Play"))
                Instantiate(fireworks);

            timerGroup.gameObject.SetActive(false);
            gameCamera.GetComponent<TransformCopy>().enabled = !gameCamera.GetComponent<TransformCopy>().enabled;
            yield return null;
        }
    }
}
