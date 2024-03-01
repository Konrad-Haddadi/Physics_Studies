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
    [SerializeField] private GameObject countDownSoundEnd;
    [SerializeField] private Image loopTimer;
    [SerializeField] private GameObject timerGroup;

    [Header("Cheering")]
    [SerializeField] private GameObject cheering;

    private AnimationCurve tweenCurve = AnimationCurve.EaseInOut(0, 0, 1, 1);
    private CheckPointManager checkPointManager;

    bool startingGame = false;
    int spawnCounterVal = 0;

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
        startingGame = true;

        Instantiate(cheering);
        StartCoroutine(CameraMove_CR(gameLocation, true));

    }

    public void ReturnToMenu()
    {
        player.animator.SetBool("Play", !player.animator.GetBool("Play"));


        play.gameObject.SetActive(true);
        quit.gameObject.SetActive(true);

        player.rb.isKinematic = true;       

        StartCoroutine(CameraMove_CR(menuLocation, false));
    }

    public IEnumerator CameraMove_CR(GameObject _targetPos, bool _reset)
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
                if(startingGame)
                {
                    int text = (int)(timeMax + .9f - timer);

                    if(timer > spawnCounterVal)
                    {
                        spawnCounterVal++;
                        Instantiate(countDownSound);
                    }

                    if (timer <= 1)
                        loopTimer.fillAmount = timer / (timeMax - 2);
                    else if (timer <= 2)
                        loopTimer.fillAmount = timer - 1 / (timeMax - 2);
                    else if (timer <= 3)
                        loopTimer.fillAmount = timer - 2 / (timeMax - 2);

                    textTimer.text = text.ToString();
                }
               

                float factor = Mathf.Clamp01(timer / timeMax);
                float t = tweenCurve.Evaluate(factor);

                gameCamera.transform.position = Vector3.Lerp(startCamPos, endCamPos, t);
                gameCamera.transform.rotation = Quaternion.Lerp(startCamRot, endCamRot, t);

                yield return null;

                timer += Time.deltaTime;
            }


            if(_reset)
            {
                player.animator.SetBool("Play", !player.animator.GetBool("Play"));

                if (player.animator.GetBool("Play"))
                {
                    Instantiate(countDownSoundEnd);
                    Instantiate(fireworks);
                    startingGame = false;
                }
            }

            spawnCounterVal= 0;
                      
            
            timerGroup.gameObject.SetActive(false);
            gameCamera.GetComponent<TransformCopy>().enabled = !gameCamera.GetComponent<TransformCopy>().enabled;
            yield return null;
        }
    }
}
