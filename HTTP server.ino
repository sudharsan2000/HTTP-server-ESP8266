#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
int led=LED_BUILTIN;
int state=HIGH;
void start();
void tgl();
String sendhtml();
 ESP8266WebServer server(80);
void setup() 
{
  char* ssid="Sudhar..!";
  char* pass="ni6ga2rd";
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  while( WiFi.status() != WL_CONNECTED)
  {
    Serial.println('.');
    delay(1000);
  }
  Serial.println("Connected. IP:"); Serial.print( WiFi.localIP() );
  server.on("/",start);
  server.on("/tgl" ,tgl);
  server.on("/sudhar",sudhar);
  server.begin();
    server.onNotFound([](){
    server.send(404, "text/plain", "404: Not found");
    
    } );
//    server.println("Welcome to LED toogle");
}

void loop() 
{
  
server.handleClient();
digitalWrite(led,state);
}
void start()
{
  Serial.println( state );
   server.send( 200,"text/html", sendhtml() );     ///////////////sendig to code server
}
void sudhar()
{
  String vtr;
  vtr= "<html>\n";
  vtr  +=     " <body> <H1> Sudhar is gr8 </H1>\n";
  vtr  +=     " </body>";
  vtr  +=     "</html>";
  Serial.println( "sudhar" );
    server.send(200,"text/html", vtr ) ;
}
void tgl()
{
  if(state)
  {
    state=LOW;
  }
  else
  {
    state=HIGH;
  }
  Serial.println( "tgl" );
  server.send(200,"text/html", sendhtml() ) ;
}
int fg=0;
String sendhtml( )
{
  String vtr;
  if(fg)
  {
   vtr= "<html xmlns='http:http://192.168.43.50/'>\n";
  vtr  +=     " <body> <H1> Press button to toogle </H1>\n";
  vtr  +=     " <a href='tgl'>  <input type = 'button' value= 'toogle'>   </a> \n";
  vtr  +=     " </body>";
  vtr  +=     "</html>";
  }
  else
  {
     vtr= "<html>\n";
  vtr  +=     " <body> <H1> Press button to toogle </H1>  <p id='p1'> This is a simple para </p>\n";
  vtr  +=     "  <button type='button' onclick='myFunction()'> TOOGLE </button> \n";
  vtr += "<script>function myFunction() { document.getElementById('p1').innerHTML='New content';}</script>"  ;
  vtr  +=     " </body>";
  vtr  +=     "</html>";
  }
  fg++;
  return vtr;
}
