#define MAXIMUMNUMBEROFADCS 6
#define MAXIMUMNUMBEROFSENSORS 20

float adcValue_[MAXIMUMNUMBEROFADCS];
int adcPinout_[MAXIMUMNUMBEROFADCS] = {A0, A1, A2, A3, A4, A5};

int adcSensor_[MAXIMUMNUMBEROFADCS] = {7, 6, -1, -1, 1, -1};

int sensorNumber = 10;
const String sensorName_[]={"BLANK", "Gas CO2", "HIH-4010-001", "HIH-5030", "Gas O2", "GEMS3100B0010", "SHT31H", "SHT31T", "MCP9700ETO", "30K6A1A", "Dry Contact"};
const String sensorType_[]={"raw", "CO2", "humidity", "humidity", "oxygen", "pressure", "humidity", "temperature", "temperature", "temperature", "state"};
const String sensorUnit_[]={"na", "ppm", "%", "%", "%", "mbar", "%", "oC", "oC", "oC", "on/off"};
const int sensorEqGrade_[]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
const float sensorEqM_[]={1.0, 10.0708, 0.15767, 0.1537, 0.024156, 12.032258, 1.0, 1.0, 0.3223, 0.09188, 1.0};
const float sensorEqB_[]={0.0, -1250.0, -25.81, -23.8208, 0.0, -1200.0, 0.0, 0.0, -50.0, -14.8511, 0.0};
const float sensorGraphMin_[]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -5.0, 0.0, 0.0, -1.0};
const float sensorGraphMax_[]={1023.0, 5000.0, 100.0, 100.0, 30.0, 10000.0, 100.0, 40.0, 40.0, 40.0, 2.0};

Adafruit_SHT31 sht31 = Adafruit_SHT31();
