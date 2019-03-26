using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using wvr;
using UnityEngine.EventSystems;
using UnityEngine.UI;


public class StartButton : MonoBehaviour,IPointerEnterHandler,IPointerDownHandler {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void OnPointerEnter(PointerEventData eventData){ 
		Text text = GameObject.Find("StartText").GetComponent<Text>();
		text.text = "OnPointerEnter";
		Debug.Log("OnPointerEnter");
	}

	public void OnPointerDown(PointerEventData eventData){
		Text text = GameObject.Find("StartText").GetComponent<Text>();
		text.text = "OnPointerDown";
		Debug.Log("OnPointerDown");
	}
}
