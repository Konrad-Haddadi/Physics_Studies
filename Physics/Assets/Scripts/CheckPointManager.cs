using System.Collections.Generic;
using UnityEngine;

public class CheckPointManager : MonoBehaviour
{
    public List<CheckPoint> CheckPoints = new();

    public void ResetGame()
    {
        foreach (CheckPoint checkPoint in CheckPoints)
        {
            checkPoint.Restart();
        }            
    }
}
