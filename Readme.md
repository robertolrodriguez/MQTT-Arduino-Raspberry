# MQTT-Arduino-Raspberry
make IOT with Arduino,Raspberry. use MQTT

by Nam Ki Hyun, sophomore , start project on 16/03/11.

#1. you have to make MQTT broker on raspberry pi.

   Link: https://rasspberrypi.wordpress.com/2012/09/16/mosquitto-mqtt-on-raspberry-pi-broker-publish-and-subscribe-client/

   follow to install MQTT broker on raspberry pi.

    wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
   
    sudo apt-key add mosquitto-repo.gpg.key
   
    cd /etc/apt/sources.list.d/
   
    sudo wget http://repo.mosquitto.org/debian/mosquitto-wheezy.list
   
    sudo apt-get install mosquitto

   if you followed all, you are complete to make MQTT broker on raspberry pi.


#2. you have to build MQTT client on PC(window or Linux or Mac). I has built 'MQTT.fx'
  
      MQTT.fx
      - http://www.jensd.de/apps/mqttfx/1.1.0/
  
   But you can choose other clients.

   you can check famous clients here.
  
      - http://www.hivemq.com/blog/seven-best-mqtt-client-tools
  
#3. you have to set up MQTT client.
  
####(1). MQTT broker url: the URL of the server on which you installed MQTT broker. (ex. ip: 192.168.xxx.xxx)

####(2). Port: Mosquiito brokers earlier installation uses the default port [1883].

####(3). Username / Password : Now you do not need to set.
      
   Do set up MQTT client on all device.
      
   you can check MQTT client on Raspberrypi.
     
    apt-get install mosquitto-clients 

   Then, you can pub message on terminal.
   
    mosquitto_pub -d -t Topic(your topic's name) -m "hellow world"
   
   or you can sub message on terminal.
   
    mosquitto_sub -d -t Topic(your topic's name)
   
   when you want to stop, press Ctrl+C.
   
   On raspberrypi, also you can pub or sub by python script. you can see souce code in my github-MQTT-Arduino-Raspberry.
   
#4. make IOT with arduino.
   
   Look MQTT-Arduino-Raspberry/IOT Arduino Circuit.docx
