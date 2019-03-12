#define LINELENGTH 400
#define WIFI 1

const String myNameIs = "Eho";
const String myFWIs = "00.01.11";

byte gatewayAddress_[4] = {192, 168, 61, 254};
byte dnsAddress_[4] = {192, 168, 61, 254};

const String netEndChar = "&";

IPAddress ipAddress_(192, 168, 61, 115);

//String SSIDName = "NOS_Internet_Movel_D760";
//String SSIDName = "IGC";
//String SSIDName = "IGCUSR";
//String SSIDName = "CATS60";
//String SSIDName = "Connectify-me";
const String SSIDName = "SensorFellowship";

//String SSIDPass = "1rjq8eht";
//String SSIDPass = "chemokine";
//String SSIDPass = "pertussis";
//String SSIDPass = "Zabofes7";
//String SSIDPass = "Pimbas12";
const String SSIDPass = "Sensing1";

byte mac[6];

int status = WL_IDLE_STATUS;

WiFiServer server(80);

String getSearchStr = "GET /";
String postSearchStr = "POST /";
String httpSearchStr = " HTTP";
