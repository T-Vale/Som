boolean parse_parameterReader(String &receivedString, String &parameterName, String &parameterStringValue, String &breakChar)
{
  parameterStringValue = ""; //protege de repeticoes
  if (receivedString.indexOf(parameterName) >= 0)
  {
    for (int x = (receivedString.indexOf(parameterName) + parameterName.length()); x < receivedString.indexOf(breakChar, receivedString.indexOf(parameterName) + parameterName.length()); x++)
    {
      parameterStringValue += receivedString[x];
    }
    return true;
  }
  else
  {
    return false;
  }
}
