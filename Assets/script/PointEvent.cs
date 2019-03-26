using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.Events;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System;
using System.Text;
using System.IO;
public class PointEvent :
 MonoBehaviour,
 IPointerEnterHandler,
 IPointerExitHandler{
	// Use this for initialization
	private int socketConnectState = -1;
	private int SOCKET_CONNET_SUCCESS = 1;
	private int SOCKET_CONNET_FAILED = 0;
	private int SOCKET_CONNET_CONNECTTING = 2;
	private ArrayList stringList = new ArrayList();
	private ArrayList messageList = new ArrayList();
	private ArrayList sendMessageList = new ArrayList();
	private Socket clientSocket;
	private TcpClient tcpClient;
	private int[] brainData;
	private bool isProcess = false;
	string recvStr = "";
	char[] tem = {'\r','\n'};
	private Thread sendMessageThread;
	private StreamWriter wr;
	private NetworkStream stream;
	private bool isReceiveFinish = false;
	
    private AndroidJavaObject currentActivity;

	private AndroidJavaObject flowtimeBleManager;
	private bool isRead = false;

	private string request_id;
	void Start () {
        //获得位于com.unity3d.player包下的UnityPlayer类
        AndroidJavaClass jc = new AndroidJavaClass("com.htc.vr.unity.WVRUnityVRActivity");
        //获得jc所代表的类下的mInstance
        currentActivity = jc.GetStatic<AndroidJavaObject>("mInstance");
		GameObject.Find("ShowText").GetComponent<Text>().text = "start";
		Thread connectThread = new Thread(connectSocket);
		connectThread.Start();
	}
	
	// Update is called once per frame
	void Update () {
        // GameObject.Find("ShowText").GetComponent<Text>().text = "Update";
		if(socketConnectState == SOCKET_CONNET_SUCCESS){
            GameObject.Find("ShowText").GetComponent<Text>().text = "连接服务器成功";
		}else if(socketConnectState == SOCKET_CONNET_FAILED){
            GameObject.Find("ShowText").GetComponent<Text>().text = "连接服务器失败，请按回车键退出！";
		}else if(socketConnectState == SOCKET_CONNET_CONNECTTING){
            GameObject.Find("ShowText").GetComponent<Text>().text = "正在连接IP端口";
		}
        socketConnectState = -1;
		if(stringList.Count>0){
			 GameObject.Find("ShowText").GetComponent<Text>().text = stringList[0].ToString();
		}
		// if(sendMessageList.Count > 0){
		// 	 GameObject.Find("SendText").GetComponent<Text>().text = sendMessageList[0].ToString();
		// 	 if(sendMessageList.Count>1){
		// 	 	sendMessageList.RemoveAt(0);
		// 	 }
		// }
		if(messageList.Count>0){
			 GameObject.Find("ShowText").GetComponent<Text>().text = messageList[0].ToString();
			 messageList.RemoveAt(0);
		}
	}
	public void OnPointerEnter(PointerEventData eventData){
		Debug.Log("image OnPointerEnter");
		GameObject.Find("ShowText").GetComponent<Text>().text = "OnPointerEnter";
	}

	public void OnPointerExit(PointerEventData eventData){
		GameObject.Find("ShowText").GetComponent<Text>().text = "OnPointerExit";
	}
	public void onShowTextChange (string msg){
        Text text = GameObject.Find ("ShowText").GetComponent<Text> ();
        text.text = msg;
    }
	public class BleScanSuccessCallback : AndroidJavaProxy {

		ArrayList messageList;
		public BleScanSuccessCallback(ArrayList list):base("kotlin.jvm.functions.Function0"){
			messageList = list;
		}
		public void invoke(){
			messageList.Add("正在扫描...");
		}
	}

	public class ConnectSucessCallback : AndroidJavaProxy {

		ArrayList messageList;
		public ConnectSucessCallback(ArrayList list):base("kotlin.jvm.functions.Function1"){
			messageList = list;
		}
		public void invoke(string result){
			messageList.Add(result);
		}
	}

	public class ConnectFailedCallback : AndroidJavaProxy {

		ArrayList messageList;
		public ConnectFailedCallback(ArrayList list):base("kotlin.jvm.functions.Function1"){
			messageList = list;
		}
		public void invoke(string result){
			messageList.Add(result);
		}
	}


	class RawBrainDataCallback : AndroidJavaProxy {

		ArrayList messageList;
		ArrayList socketBuffer = new ArrayList();
		StreamWriter streamWriter;
		string request_id;
		public RawBrainDataCallback(ArrayList list,StreamWriter sw,string requestId):base("kotlin.jvm.functions.Function1"){
			messageList = list;
			streamWriter = sw;
			request_id = requestId;
		}
		public void invoke(AndroidJavaObject jo){
			AndroidJavaObject bufferObject = jo.Get<AndroidJavaObject>("Buffer");
			byte[] buffer = AndroidJNIHelper.ConvertFromJNIArray<byte[]>(bufferObject.GetRawObject());
			for(int i = 0;i<buffer.Length;i++){
				socketBuffer.Add(buffer[i]&0xff);
				if(socketBuffer.Count >= 600){
					ProcessDataEntity processDataEntity = new ProcessDataEntity();
					processDataEntity.command = "process";
					processDataEntity.request_id = request_id;
					processDataEntity.data = (int[])socketBuffer.ToArray(typeof(Int32));
					string processJson = JsonUtility.ToJson(processDataEntity);
					streamWriter.Write(processJson+"\r\n");
					streamWriter.Flush();
					socketBuffer.Clear();
				}
			}
		}
	}
	public void onBleConnect(){
		BleScanSuccessCallback bleScanSuccessCallback = new BleScanSuccessCallback(messageList);
		ConnectSucessCallback connectSucessCallback = new ConnectSucessCallback(messageList);
		ConnectFailedCallback connectFailedCallback = new ConnectFailedCallback(messageList);
		try{
			AndroidJavaClass flowtimeBleManagerJc = new AndroidJavaClass("cn.entertech.ble.FlowtimeBleManager");
			var companion = flowtimeBleManagerJc.GetStatic<AndroidJavaObject>("Companion");
			flowtimeBleManager = companion.Call<AndroidJavaObject>("getInstance",currentActivity);
			if(flowtimeBleManager != null){
				flowtimeBleManager.Call("scanNearDeviceAndConnect",bleScanSuccessCallback,connectSucessCallback,connectFailedCallback);
			}
		}catch(Exception e){
			stringList.Add(e.ToString());
			socketConnectState = SOCKET_CONNET_FAILED; 
		}
	}

	public void onBleDisconnect(){
		flowtimeBleManager.Call("disConnect");
	}

	public void onStartButtonClick(){
		start();
		// process();
	}

	public void onProcessButtonClick(){
		process();
	}

	public void onEndButtonClick(){
		flowtimeBleManager.Call("stopBrainCollection");
		finish();
		// stopRead();
		// Thread connectThread = new Thread(connectSocket);
		// connectThread.Start();
	}

	public void onExitButtonClick(){
		Application.Quit();
	}

	public void start(){
		request_id = DateTime.Now.ToString();
		StartDataEntity data = new StartDataEntity();
		data.command = "start";
		data.device_id = "A0";
		data.request_id = request_id;
		string json = JsonUtility.ToJson(data);
		Thread startThread = new Thread(()=>sendMessage(json));
		startThread.Start();
	}

	public void process(){
		RawBrainDataCallback rawBrainDataCallback = new RawBrainDataCallback(messageList,wr,request_id);
		flowtimeBleManager.Call("addRawDataListener4CSharp",rawBrainDataCallback);
		flowtimeBleManager.Call("startBrainCollection");
	}

	public void finish(){
		EndDataEntity data = new EndDataEntity();
		data.request_id = request_id;
		data.command = "finish";
		string json = JsonUtility.ToJson(data);
		Thread startThread = new Thread(()=>sendMessage(json));
		startThread.Start();
	}

	public void sendMessage(string json){
		// sendMessageList.Add(json);
		wr.Write(json+"\r\n");
		wr.Flush();
	}

	public void receiveMessage(){
		try{
			StreamReader sr = new StreamReader(stream);
			while(true){
				string result = sr.ReadLine();
				messageList.Add(result);
				Thread.Sleep(300);
			}
		}catch(Exception e){
			stringList.Add(e.ToString());
			socketConnectState = SOCKET_CONNET_FAILED; 
            return;
		}
	}

	public void stopRead(){
		isRead = false;
	}
	public void connectSocket(){
		Debug.Log("子线程已开启。。。");
        try{
            socketConnectState = SOCKET_CONNET_CONNECTTING;
			IPHostEntry hostInfo = Dns.GetHostEntry("api.affectivecloud.com");
			IPAddress ipAddress = hostInfo.AddressList[0]; 
			clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			IPEndPoint iPEndPoint = new IPEndPoint(ipAddress,8080);
			tcpClient = new TcpClient();
			tcpClient.Connect(iPEndPoint);
			stream = tcpClient.GetStream();
			wr = new StreamWriter(stream);
            // clientSocket.Connect(iPEndPoint); //配置服务器IP与端口 
			socketConnectState = SOCKET_CONNET_SUCCESS; 
			isRead = true;
			receiveMessage();
        }catch(Exception e){
			stringList.Add(e.ToString());
			socketConnectState = SOCKET_CONNET_FAILED; 
            return;
        }
	}

	[Serializable]class StartDataEntity{
		 public string command;
		 public string request_id;
		 public string device_id;
	}

	[Serializable]class ProcessDataEntity{
		 public string command;
		 public string request_id;
		 public int[] data;
	}
	[Serializable]class EndDataEntity{
		 public string command;
		 public string request_id;
	}
}
