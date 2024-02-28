using System.Collections;
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

    private AnimationCurve tweenCurve = AnimationCurve.EaseInOut(0, 0, 1, 1);
    private CheckPointManager checkPointManager;


    // Start is called before the first frame update
    void Start()
    {
        gameCamera.GetComponent<TransformCopy>().enabled = false;

        quit.onClick.AddListener(Application.Quit);
        play.onClick.AddListener(PlayGame);

        checkPointManager = FindObjectOfType<CheckPointManager>();
    }


    private void PlayGame()
    {
        checkPointManager.ResetGame();

        play.gameObject.SetActive(false);
        quit.gameObject.SetActive(false);

        Instantiate(fireworks);

        player.animator.SetBool("Play", true);
        player.rb.isKinematic = false;

        player.transform.position = spawnPoint.transform.position;

        StartCoroutine(CameraMove_CR(gameLocation));

    }

    public void ReturnToMenu()
    {
        play.gameObject.SetActive(true);
        quit.gameObject.SetActive(true);

        player.animator.SetBool("Play", false);
        player.rb.isKinematic = true;       

        StartCoroutine(CameraMove_CR(menuLocation));
    }

    public IEnumerator CameraMove_CR(GameObject _targetPos)
    {
        float timer = 0;
        float timeMax = 1;

        while (timer < timeMax)
        {
            Vector3 startCamPos = gameCamera.transform.position;
            Quaternion startCamRot = gameCamera.transform.rotation;

            Vector3 endCamPos = _targetPos.transform.position;
            Quaternion endCamRot = _targetPos.transform.rotation;


            while (timer < timeMax)
            {
                float factor = Mathf.Clamp01(timer / timeMax);
                float t = tweenCurve.Evaluate(factor);

                gameCamera.transform.position = Vector3.Lerp(startCamPos, endCamPos, t);
                gameCamera.transform.rotation = Quaternion.Lerp(startCamRot, endCamRot, t);

                yield return null;

                timer += Time.deltaTime;
            }

            gameCamera.GetComponent<TransformCopy>().enabled = !gameCamera.GetComponent<TransformCopy>().enabled;
            yield return null;
        }
    }
}
