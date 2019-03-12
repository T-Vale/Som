void html_interface()
{
  // listen for incoming clients
  read_value();

  WiFiClient client = server.available();
  if (client)
  {
    ////Serial.println("HTML Communication Started");
    boolean currentLineIsBlank = true;

    receivedLine = "";
    receivedPost = "";
    boolean thereIsAPost = false;

    boolean statusxml = false;
    boolean statusjson = false;
    boolean statusreset = false;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        ////Serial.print(c);
        if (receivedLine.length() < LINELENGTH)
        {
          receivedLine = receivedLine + c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        if (c == '\n' && currentLineIsBlank)
        {
          while (client.available())
          {
            char d = client.read();
            if (receivedPost.length() < LINELENGTH)
            {
              receivedPost = receivedPost + d;
            }
            else
            {
              client.flush();
            }
          }

          if ((receivedPost.length() > 0) && thereIsAPost)
          {
            receivedPost += "&";
            boolean thepostisfine = false;
          }
          thereIsAPost = false;
          
          if (statusxml)
          {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/xml"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println();
            client.println(F("<?xml version=\"1.0\" encoding=\"windows-1252\"?>"));
            client.println(F("<Equipment>"));
            client.print(F("<Device>"));
            client.print(myNameIs);
            client.println(F("</Device>"));
            client.print(F("<ID>"));
            client.print(mac[0], HEX);
            client.print(F(":"));
            client.print(mac[1], HEX);
            client.print(F(":"));
            client.print(mac[2], HEX);
            client.print(F(":"));
            client.print(mac[3], HEX);
            client.print(F(":"));
            client.print(mac[4], HEX);
            client.print(F(":"));
            client.print(mac[5], HEX);
            client.println(F("</ID>"));
            client.print(F("<FW>"));
            client.print(myFWIs);
            client.println(F("</FW>"));
            long rssi = WiFi.RSSI();
            client.print(F("<RSSI>"));
            client.print(rssi);
            client.println(F(" dBm</RSSI>"));
            client.print(F("<TimeToReset>"));
            client.print((SYSTEMRESTARTINTERVAL - (millis() - systemStarting))/3600000);
            client.println(F(" hours</TimeToReset>"));
            for (int adcnum = 0; adcnum < MAXIMUMNUMBEROFADCS; adcnum++)
            {
              client.print(F("<ADC"));
              client.print(adcnum);
              client.println(F(">"));
              if(adcSensor_[adcnum] != -1)
              {
                client.print(F("<Value>"));
                client.print(adcValue_[adcnum] * sensorEqM_[adcSensor_[adcnum]] + sensorEqB_[adcSensor_[adcnum]]);
                client.println(F("</Value>"));
                client.print(F("<Unit>"));
                client.print(sensorUnit_[adcSensor_[adcnum]]);
                client.println(F("</Unit>"));
                client.print(F("<Type>"));
                client.print(sensorType_[adcSensor_[adcnum]]);
                client.println(F("</Type>"));
                client.print(F("<Name>"));
                client.print(sensorName_[adcSensor_[adcnum]]);
                client.println(F("</Name>"));
              }
              else
              {
                client.print(F("<Value>-1</Value>"));
                client.print(F("<Unit>na</Unit>"));
                client.print(F("<Type>na</Type>"));
                client.print(F("<Name>na</Name>"));
              }
              client.print(F("</ADC"));
              client.print(adcnum);
              client.println(F(">"));
            }
            client.println(F("</Equipment>"));
          }
          else if (statusjson)
          {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/json"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println();
            client.println(F("{"));
            client.println(F("\t\"Equipment\": {"));
            client.print(F("\t\t\"Device\": \""));
            client.print(myNameIs);
            client.println(F("\","));
            client.print(F("\t\t\"ID\": \""));
            client.print(mac[0], HEX);
            client.print(F(":"));
            client.print(mac[1], HEX);
            client.print(F(":"));
            client.print(mac[2], HEX);
            client.print(F(":"));
            client.print(mac[3], HEX);
            client.print(F(":"));
            client.print(mac[4], HEX);
            client.print(F(":"));
            client.print(mac[5], HEX);
            client.println(F("\","));
            client.print(F("\t\t\"FW\": \""));
            client.print(myFWIs);
            client.println(F("\","));
            long rssi = WiFi.RSSI();
            client.print(F("\t\t\"RSSI\": \""));
            client.print(rssi);
            client.println(F(" dBm\","));
            client.print(F("\t\t\"TimeToReset\": \""));
            client.print((SYSTEMRESTARTINTERVAL - (millis() - systemStarting))/3600000);
            client.println(F(" hours\","));
            for (int adcnum = 0; adcnum < MAXIMUMNUMBEROFADCS; adcnum++)
            {
              client.print(F("\t\t\"ADC"));
              client.print(adcnum);
              client.println(F("\": {"));
              if(adcSensor_[adcnum] != -1)
              {
                client.print(F("\t\t\t\"Value\": \""));
                client.print(adcValue_[adcnum] * sensorEqM_[adcSensor_[adcnum]] + sensorEqB_[adcSensor_[adcnum]]);
                client.println(F("\","));
                client.print(F("\t\t\t\"Unit\": \""));
                client.print(sensorUnit_[adcSensor_[adcnum]]);
                client.println(F("\","));
                client.print(F("\t\t\t\"Type\": \""));
                client.print(sensorType_[adcSensor_[adcnum]]);
                client.println(F("\","));
                client.print(F("\t\t\t\"Name\": \""));
                client.print(sensorName_[adcSensor_[adcnum]]);
                client.println(F("\""));
              }
              else
              {
                client.println(F("\t\t\t\"Value\": \"-1\","));
                client.println(F("\t\t\t\"Unit\": \"na\","));
                client.println(F("\t\t\t\"Type\": \"na\","));
                client.println(F("\t\t\t\"Name\": \"na\""));
              }
              client.print(F("\t\t}"));
              if(adcnum == MAXIMUMNUMBEROFADCS - 1)
              {
                client.println();
              }
              else
              {
                client.println(F(","));
              }
            }
            client.println(F("\t}"));
            client.println(F("}"));
          }
          else if (statusreset)
          {
            digitalWrite(resetPin, LOW); //hard resets Arduino
          }
          else
          {
            // send a standard http response header
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println();
            client.println(F("<!DOCTYPE HTML>"));
            client.println(F("<html>"));
            client.println(F("<style>"));

            client.println(F("\t#rcorners {"));
            client.println(F("\t\tborder-radius: 15px 50px;"));
            client.println(F ("\t\tbackground: #000080;"));
            client.println(F("\t\tpadding: 25px 50px;"));
            client.println(F("\t\twidth: 65px;"));
            client.println(F("\t\theight: 25px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 35px;"));
            client.println(F("\t\ttext-shadow: 1% 1% #f2f2f2;"));
            client.println(F("\t\tcolor: white;"));
            client.println(F("\t}"));

            client.println(F("\t#titles {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\ttext-shadow: 1% 1% #f2f2f2;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));

            client.println(F("\t#buttons {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\t#fillin {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));

            client.println(F("\t#textbox {"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t\twidth: 40px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\t#hovertable {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tborder-collapse: collapse;"));
            client.println(F("\t\twidth: 400px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));

            client.println(F("\t#hovertr:hover{background-color:#f5f5f5}"));

            client.println(F("\t#invisibletable {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tborder-collapse: collapse;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));

            client.println(F("\tth, td {"));
            client.println(F("\t\tpadding: 8px 10px;"));
            client.println(F("\t\ttext-align: left;"));
            client.println(F("\t\tborder-bottom: 1px solid #ddd;"));
            client.println(F("\t}"));

            client.println(F("\ta {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\ttext-decoration:none;"));
            //client.println(F("\t\tfont-family: verdana;"));
            //client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\tp {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));

            client.println(F("\tcode {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-size: 14px;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));

            client.println(F("</style>"));
            client.print(F("<a href=\"http://"));
            client.print(ipAddress_[0]);
            client.print(F("."));
            client.print(ipAddress_[1]);
            client.print(F("."));
            client.print(ipAddress_[2]);
            client.print(F("."));
            client.print(ipAddress_[3]);
            client.println(F("\">"));
            client.println(F("<h3 id=\"rcorners\">"));
            client.print(F("\t"));
            client.println(myNameIs);
            client.println(F("</h3>"));
            client.println(F("</a>"));

            client.println(F("<body>"));
            client.println(F("<table id=\"hovertable\">"));
            client.println(F("\t<tr>"));
            client.println(F("\t\t<th>ADC</th>"));
            client.println(F("\t\t<th>Name</th>"));
            client.println(F("\t\t<th>Type</th>"));
            client.println(F("\t\t<th>Units</th>"));
            client.println(F("\t\t<th>Value</th>"));
            client.println(F("\t</tr>"));

            for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
            {
              client.println(F("\t<tr id=\"hovertr\">"));
              client.print(F("\t\t<td>"));
              client.print(adc);
              client.println(F("</td>"));
              if (adcSensor_[adc] >= 0 && adcSensor_[adc] <= MAXIMUMNUMBEROFSENSORS)
              {
                client.print(F("\t\t<td>"));
                client.print(sensorName_[adcSensor_[adc]]);
                client.println(F("</td>"));
                client.print(F("\t\t<td>"));
                client.print(sensorType_[adcSensor_[adc]]);
                client.println(F("</td>"));
                client.print(F("\t\t<td>"));
                client.print(sensorUnit_[adcSensor_[adc]]);
                client.println(F("</td>"));
                client.print(F("\t\t<td>"));
                client.print(adcValue_[adc] * sensorEqM_[adcSensor_[adc]] + sensorEqB_[adcSensor_[adc]]);
                client.println(F("</td>"));
                client.println(F("\t</tr>"));
              }
              else
              {
                client.print(F("\t\t<td>"));
                client.print(F("Not Assigned"));
                client.println(F("</td>"));
                client.print(F("\t\t<td>"));
                client.print(F("-"));
                client.println(F("</td>"));
                client.print(F("\t\t<td>"));
                client.print(F("-"));
                client.println(F("</td>"));
                client.print(F("\t\t<td>"));
                client.print(F("-"));
                client.println(F("</td>"));
                client.println(F("\t</tr>"));
              }
            }
            client.println(F("</table>"));
            client.println(F("</body>"));
            client.println(F("</html>"));
          }
          break;
        }

        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
          String buffLine = "";

          if (parse_parameterReader(receivedLine, getSearchStr, buffLine, httpSearchStr))
          {
            if ((buffLine.length() > 0))
            {
              statusxml = (buffLine == "status.xml");
              statusjson = (buffLine == "status.json");
              statusreset = (buffLine == "doprincipio");
            }
          }
          else if (parse_parameterReader(receivedLine, postSearchStr, buffLine, httpSearchStr))
          {
            thereIsAPost = true;
          }
          receivedLine = "";
        }

        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(10);
    // close the connection:
    client.stop();
    delay(1000);
  }
  else
  {
    ////Serial.println("No connection");
  }
}
