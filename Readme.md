# MQTT-Arduino-Raspberry
make IOT with Arduino,Raspberry. use MQTT

By Nam Ki Hyun, sophomore , start project on 16/03/11.

#1. Install MQTT broker on raspberry pi.

   Link: https://rasspberrypi.wordpress.com/2012/09/16/mosquitto-mqtt-on-raspberry-pi-broker-publish-and-subscribe-client/

   follow to install MQTT broker on raspberry pi.

    wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
   
    sudo apt-key add mosquitto-repo.gpg.key
   
    cd /etc/apt/sources.list.d/
   
    sudo wget http://repo.mosquitto.org/debian/mosquitto-wheezy.list
   
    sudo apt-get install mosquitto

   If you followed everyone, you made an MQTT broker in a raspberry pie.


#2. Build MQTT client on PC(window or Linux or Mac). I has built 'MQTT.fx'
  
   MQTT.fx:  http://www.jensd.de/apps/mqttfx/1.1.0/
  
   But you can choose other clients.

   you can check famous clients here.
  
   http://www.hivemq.com/blog/seven-best-mqtt-client-tools
  
#3. Set up MQTT client.
  
####(1). MQTT broker url: the URL of the server on which you installed MQTT broker. (ex. ip: 192.168.xxx.xxx)

####(2). Port: Mosquiito brokers earlier installation uses the default port [1883].

####(3). Username / Password : Now you do not need to set.
      
   Do set up MQTT client on all device.
      
   you can check MQTT client on Raspberrypi.
     
    apt-get install mosquitto-clients 

   Then, you can pub message on terminal.
   
    mosquitto_pub -d -t your topic's name -m "hellow world"
   
   or you can sub message on terminal.
   
    mosquitto_sub -d -t your topic's name
   
   when you want to stop, press Ctrl+C.
   
   On raspberrypi, also you can pub or sub by python script. you can see souce code in my github-MQTT-Arduino-Raspberry.
   
#4. Make IOT with arduino.
   ![alt tag](https://github.com/DevKiHyun/MQTT-Arduino-Raspberry/blob/master/Image/DHT.PNG)
   ![alt tag](https://github.com/DevKiHyun/MQTT-Arduino-Raspberry/blob/master/Image/Heat%20Sensor.PNG)
   ![alt tag](https://github.com/DevKiHyun/MQTT-Arduino-Raspberry/blob/master/Image/Air-condition.PNG)
   
   And you want to use wifi, then you have to use arduino wifi shield.(for arduino uno)
   
   ![alt tag](https://github.com/DevKiHyun/MQTT-Arduino-Raspberry/blob/master/Image/arduino%20wifi%20shield.PNG)

#5. Check your IOT device
   When you finish to make IOT device, then you can check that it work well.
   
   Use codes in MQTT-Arduino-Raspberry/Test-arduino.
   
   If your IOT device's sensor was work well, next is to send data to sever.
   
   Use codes in MQTT-Air-arduino, DHT-arduino, Heat-arduino.
   
   But You must change a few things.
   
   'Wifi ID, Wifi password, your URL of the server, your topic's name.'
   
   Then, You have finished basic setup.
   
   You can see a message that send from IOT Device on Client. (I use client 'MQTT.fx')
   ![alt tag](https://github.com/DevKiHyun/MQTT-Arduino-Raspberry/blob/master/Image/check.PNG)
   
   
   
   
   
