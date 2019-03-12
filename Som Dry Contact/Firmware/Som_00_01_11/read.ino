void read_value()
{
  for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
  {
    if(sensorName_[adcSensor_[adc]] == "SHT31T")
    {
      adcValue_[adc] = digital_SHT31(0, 0x44); //0 for temperature
    }
    else if(sensorName_[adcSensor_[adc]] == "SHT31H")
    {
      adcValue_[adc] = digital_SHT31(1, 0x44); //1 for humidity
    }
    else if(sensorName_[adcSensor_[adc]] == "Dry Contact")
    {
      if(digitalRead(adcPinout_[adc]) == LOW)
      {
        adcValue_[adc] = 1;
      }
      else
      {
        adcValue_[adc] = 0;
      }
    }
    else
    {
      adcValue_[adc] = analogRead(adcPinout_[adc]);
    }
  }
}
