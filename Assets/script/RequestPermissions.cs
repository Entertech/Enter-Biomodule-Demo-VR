using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using wvr;
using System;

/// <summary>
/// Request Android permissions
/// </summary>
public class RequestPermissions : MonoBehaviour
{
    /// <summary>
    /// Instance of the permissions manager
    /// </summary>
    private WaveVR_PermissionManager pmInstance = null;

    private void Start()
    {
 
            pmInstance = WaveVR_PermissionManager.instance;//get the permission manger
            StartCoroutine(PermissionManagerWait());
    
    }

    /// <summary>
    /// Waits the permission manager to be ready and then asks for a permission
    /// </summary>
    /// <returns></returns>
    private IEnumerator PermissionManagerWait()
    {       
        //list of the permissions necessary for this application. Here i just need the microphone
        string[] tmpStr =
        {
            "android.permission.ACCESS_COARSE_LOCATION"
        };

        //wait for the permissions manager to be initialized, without blocking the app
        while (!pmInstance.isInitialized())
        {
            yield return new WaitForSeconds(0.33f);
        }

        //Major function to request permission
        pmInstance.requestPermissions(tmpStr, requestDoneCallback);
    }

    /// <summary>
    /// Callback called when the permissions manager has had the results of its requests
    /// </summary>
    /// <param name="results"></param>
    private void requestDoneCallback(List<WaveVR_PermissionManager.RequestResult> results)
    {
        //if the user has granted the mic request, go to main scene, otherwise log the failure
        // if (results[0].Granted)
        //     UnityMainThreadDispatcher.Instance().Enqueue(() => { GoToMainScene(); });
        // else
        //     UnityMainThreadDispatcher.Instance().Enqueue(() => { Debug.Log("WTF user"); });
    }
}