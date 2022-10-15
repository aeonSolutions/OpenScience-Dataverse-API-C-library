/*
   Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
   2022 Miguel Tomas
   https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode

    You are free to:
        Share — copy and redistribute the material in any medium or format
        Adapt — remix, transform, and build upon the material

    The licensor cannot revoke these freedoms as long as you follow the license terms.
    Under the following terms:
        Attribution                —  You must give appropriate credit, provide a link to the license, and indicate if 
                                      changes were made.You may do so in any reasonable manner, but not in any way that 
                                      suggests the licensor endorses you or your use.
        NonCommercial              —  You may not use the material for commercial purposes.
        ShareAlike                 —  If you remix, transform, or build upon the material, you must distribute your contributions
                                      under the same license as the original.

        No additional restrictions —  You may not apply legal terms or technological measures that legally restrict
                                      others from doing anything the license permits.

*/



#include "Dataverse.h"

/*! @brief  Constructor for Dataverse */
Dataverse::Dataverse(){}


// *********************************************************
//      Upload a file to a Dataset on a Dataverse
// *********************************************************
void Dataverse::UploadToDataverse(byte counter) {
  Dataverse::UploadToDataverse(0);
}
// *********************************************************
void Dataverse::UploadToDataverse(byte counter) {
  if(counter> THIS->MAX_ATTEMPT_REQUESTS)
    return;
    
  //Check WiFi connection status
  if(WiFi.status() != WL_CONNECTED){
    mserial.printStrln("WiFi Disconnected");
    if (connect2WIFInetowrk()){
      UploadToDataverse(counter+1);
    }
  }

  bool uploadStatusNotOK=true;
  if(datasetInfoJson["data"].containsKey("id")){
    if(datasetInfoJson["data"]["id"] !=""){
      String rawResponse = GetInfoFromDataverse("/api/datasets/"+ datasetInfoJson["data"]["id"] +"/locks");
      const size_t capacity =2*rawResponse.length() + JSON_ARRAY_SIZE(1) + 7*JSON_OBJECT_SIZE(1);
      DynamicJsonDocument datasetLocksJson(capacity);  
      // Parse JSON object
      DeserializationError error = deserializeJson(datasetLocksJson, rawResponse);
      if (error) {
        mserial.printStr("unable to retrive dataset lock status. Upload not possible. ERR: "+error.f_str());
        //mserial.printStrln(rawResponse);
        return;
      }else{
         String stat = datasetInfoJson["status"];
         if(datasetInfoJson.containsKey("lockType")){

           String locktype = datasetInfoJson["data"]["lockType"];           
           mserial.printStrln("There is a Lock on the dataset: "+ locktype); 
           mserial.printStrln("Upload of most recent data is not possible without removal of the lock.");  
           // Do unlocking 
                
         }else{
            mserial.printStrln("The dataset is unlocked. Upload possible.");
            uploadStatusNotOK=false;     
         }
      }
    }else{
      mserial.printStrln("dataset ID is empty. Upload not possible. "); 
    }
  }else{
    mserial.printStrln("dataset metadata not loaded. Upload not possible. "); 
  }
  
  if(uploadStatusNotOK){
    return;
  }

  // Open the dataset file and prepare for binary upload
  File datasetFile = FFat.open("/"+EXPERIMENTAL_DATA_FILENAME, FILE_READ);
  if (!datasetFile){
    mserial.printStrln("Dataset file not found");
    return;
  }
    
  String boundary = "7MA4YWxkTrZu0gW";
  String contentType = "text/csv";
  DATASET_REPOSITORY_URL =  "/api/datasets/:persistentId/add?persistentId="+PERSISTENT_ID;
  
  String datasetFileName = datasetFile.name();
  String datasetFileSize = String(datasetFile.size());
  mserial.printStrln("Dataset File Details:");
  mserial.printStrln("Filename:" + datasetFileName);
  mserial.printStrln("size (bytes): "+ datasetFileSize);
  mserial.printStrln("");
    
  int str_len = SERVER_URL.length() + 1; // Length (with one extra character for the null terminator)
  char SERVER_URL_char [str_len];    // Prepare the character array (the buffer) 
  SERVER_URL.toCharArray(SERVER_URL_char, str_len);    // Copy it over 
    
  client.stop();
  client.setCACert(HARVARD_ROOT_CA_RSA_SHA1);
  if (!client.connect(SERVER_URL_char, SERVER_PORT)) {
      mserial.printStrln("Cloud server URL connection FAILED!");
      mserial.printStrln(SERVER_URL_char);
      int server_status = client.connected();
      mserial.printStrln("Server status code: " + String(server_status));
      return;
  }
  mserial.printStrln("Connected to the dataverse of Harvard University"); 
  mserial.printStrln("");

  mserial.printStr("Requesting URL: " + DATASET_REPOSITORY_URL);

  // Make a HTTP request and add HTTP headers    
  String postHeader = "POST " + DATASET_REPOSITORY_URL + " HTTP/1.1\r\n";
  postHeader += "Host: " + SERVER_URL + ":" + String(SERVER_PORT) + "\r\n";
  postHeader += "X-Dataverse-key: " + API_TOKEN + "\r\n";
  postHeader += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
  postHeader += "Accept: text/html,application/xhtml+xml,application/xml,application/json;q=0.9,*/*;q=0.8\r\n";
  postHeader += "Accept-Encoding: gzip,deflate\r\n";
  postHeader += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n";
  postHeader += "User-Agent: AeonLabs LDAD Smart DAQ device\r\n";
  postHeader += "Keep-Alive: 300\r\n";
  postHeader += "Connection: keep-alive\r\n";
  postHeader += "Accept-Language: en-us\r\n";

  // jsonData header
  String jsonData = "{\"description\":\"LIVE Experimental data upload from LDAD Smart 12bit DAQ \",\"categories\":[\"Data\"], \"restrict\":\"false\", \"tabIngest\":\"false\"}";     
  String jsonDataHeader = "--" + boundary + "\r\n";
  jsonDataHeader += "Content-Disposition: form-data; name=\"jsonData\"\r\n\r\n";
  jsonDataHeader += jsonData+"\r\n";

  // dataset header
  String datasetHead = "--" + boundary + "\r\n";
  datasetHead += "Content-Disposition: form-data; name=\"file\"; filename=\"" + datasetFileName + "\"\r\n";
  datasetHead += "Content-Type: " + contentType + "\r\n\r\n";

  // request tail
  String tail = "\r\n--" + boundary + "--\r\n\r\n";

  // content length
  int contentLength = jsonDataHeader.length() + datasetHead.length() + datasetFile.size() + tail.length();
  postHeader += "Content-Length: " + String(contentLength, DEC) + "\n\n";
  
  // send post header
  int postHeader_len=postHeader.length() + 1; 
  char charBuf0[postHeader_len];
  postHeader.toCharArray(charBuf0, postHeader_len);
  client.print(charBuf0);
  mserial.printStr(charBuf0);

  // send key header
  char charBufKey[jsonDataHeader.length() + 1];
  jsonDataHeader.toCharArray(charBufKey, jsonDataHeader.length() + 1);
  client.print(charBufKey);
  mserial.printStr(charBufKey);

  // send request buffer
  char charBuf1[datasetHead.length() + 1];
  datasetHead.toCharArray(charBuf1, datasetHead.length() + 1);
  client.print(charBuf1);
  mserial.printStr(charBuf1);

  // create buffer
  const int bufSize = 2048;
  byte clientBuf[bufSize];
  int clientCount = 0;

  while (datasetFile.available()) {
    clientBuf[clientCount] = datasetFile.read();
    clientCount++;
    if (clientCount > (bufSize - 1)) {
        client.write((const uint8_t *)clientBuf, bufSize);
        clientCount = 0;
    }
  }
  datasetFile.close();
  if (clientCount > 0) {
      client.write((const uint8_t *)clientBuf, clientCount);
      mserial.printStrln("[binary data]");
  }

  // send tail
  char charBuf3[tail.length() + 1];
  tail.toCharArray(charBuf3, tail.length() + 1);
  client.print(charBuf3);
  mserial.printStr(charBuf3);

  // Read all the lines on reply back from server and print them to mserial
  mserial.printStrln("");
  mserial.printStrln("Response Headers:");
  String responseHeaders = "";

  while (client.connected()) {
    // mserial.printStrln("while client connected");
    responseHeaders = client.readStringUntil('\n');
    mserial.printStrln(responseHeaders);
    if (responseHeaders == "\r") {
      mserial.printStrln("======   end of headers ======");
      break;
    }
  }

  String responseContent = client.readStringUntil('\n');
  mserial.printStrln("Harvard University's Dataverse reply was:");
  mserial.printStrln("==========");
  mserial.printStrln(responseContent);
  mserial.printStrln("==========");
  mserial.printStrln("closing connection");
  client.stop();
}

// *********************************************************
//            Make data request to Dataverse (GET)
// *********************************************************
void Dataverse::GetInfoFromDataverse(String url) {
  Dataverse::GetInfoFromDataverse(url,0);
}

// *********************************************************
String Dataverse::GetInfoFromDataverse(String url, byte counter) {
    if(counter> THIS->MAX_ATTEMPT_REQUESTS)
        return;

    //Check WiFi connection status
    if(WiFi.status() != WL_CONNECTED){
        mserial.printStrln("WiFi Disconnected");
        if (connect2WIFInetowrk()){
            GetInfoFromDataverse(url, counter+1);
        }
    }
            
  int str_len = SERVER_URL.length() + 1; // Length (with one extra character for the null terminator)
  char SERVER_URL_char [str_len];    // Prepare the character array (the buffer) 
  SERVER_URL.toCharArray(SERVER_URL_char, str_len);    // Copy it over 
    
  client.stop();
  client.setCACert(HARVARD_ROOT_CA_RSA_SHA1);
    
  if (!client.connect(SERVER_URL_char, SERVER_PORT)) {
      mserial.printStrln("Cloud server URL connection FAILED!");
      mserial.printStrln(SERVER_URL_char);
      int server_status = client.connected();
      mserial.printStrln("Server status code: " + String(server_status));
      return "";
  }
  
  mserial.printStrln("Connected to the dataverse of Harvard University"); 
  mserial.printStrln("");
  
  // We now create a URI for the request
  mserial.printStr("Requesting URL: ");
  mserial.printStrln(url);

  // Make a HTTP request and add HTTP headers    
  // post header
  String postHeader = "GET " + url + " HTTP/1.1\r\n";
  postHeader += "Host: " + SERVER_URL + ":" + String(SERVER_PORT) + "\r\n";
  //postHeader += "X-Dataverse-key: " + API_TOKEN + "\r\n";
  postHeader += "Content-Type: text/json\r\n";
  postHeader += "Accept: text/html,application/xhtml+xml,application/xml,application/json,text/json;q=0.9,*/*;q=0.8\r\n";
  postHeader += "Accept-Encoding: gzip,deflate\r\n";
  postHeader += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n";
  postHeader += "User-Agent: AeonLabs LDAD Smart DAQ device\r\n";
  //postHeader += "Keep-Alive: 300\r\n";
  postHeader += "Accept-Language: en-us\r\n";
  postHeader += "Connection: close\r\n\r\n";

  // request tail
  String boundary = "7MA4YWxkTrZu0gW";
  String tail = "\r\n--" + boundary + "--\r\n\r\n";

  // content length
  int contentLength = tail.length();
  //postHeader += "Content-Length: " + String(contentLength, DEC) + "\n\n";
  
  // send post header
  int postHeader_len=postHeader.length() + 1; 
  char charBuf0[postHeader_len];
  postHeader.toCharArray(charBuf0, postHeader_len);
  client.print(charBuf0);
  
  mserial.printStrln("======= Headers =======");
  mserial.printStrln(charBuf0);
  mserial.printStrln("======= End of Headers =======");
  
  // Read all the lines of the reply from server and print them to mserial
  String responseHeaders = "";

  mserial.printStr("Waiting for server response...");
  long timeout= millis();
  long ttl=millis()-timeout;
  while (client.connected() && abs(ttl) < HTTP_TTL) {
    ttl=millis()-timeout;      
    responseHeaders = client.readStringUntil('\n');
    if (responseHeaders == "\r") {
      break;
    }
  }
  if (abs(ttl) < 10000){
    mserial.printStrln("OK");
  }else{
    mserial.printStrln("timed out.");  
  }
  
  String responseContent = client.readStringUntil('\n');
  client.stop();

  return responseContent;
  }