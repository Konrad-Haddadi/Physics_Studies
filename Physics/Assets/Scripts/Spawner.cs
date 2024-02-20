using UnityEngine;

public class Spawner : MonoBehaviour
{
    public Transform prefab;
    public float _timer = 0;

    private void Update()
    {
        if (_timer >= 0.1f)
        {
            _timer = 0;
        }

            Instantiate(prefab, transform.position, Quaternion.identity);
        _timer += Time.deltaTime;
    }

}
