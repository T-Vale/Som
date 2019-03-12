float digital_SHT31(int type, int commport)
{
  if(type == 0) //temperature
  {
    return sht31.readTemperature();
  }
  else if(type == 1)
  {
    return sht31.readHumidity();
  }
  return 0;
}

