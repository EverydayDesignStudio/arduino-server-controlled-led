# Arduino Server Controlled LED
> Control an LED (or anything connected to a GPIO pin on your Arduino ESP 8266) from a website. This turns your ESP into a server, which hosts a website to receive user input.

## Helpful Links To Get Started
* [ESP8266 First Web Server](https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html)
* [Control ESP8266 Over the Internet (from Anywhere)](https://www.instructables.com/id/Control-ESP8266-Over-the-Internet-from-Anywhere/)
* [ESP8266: Get MAC address](https://techtutorialsx.com/2017/04/09/esp8266-get-mac-address/)
* [Not Sure What Your Router's Public IP Is?](https://www.whatsmyip.org)

## Making the Server/Website Public
The hardest part of this whole project was making it publicly viewable to the rest of the internet. It's quite easy to host it on your local network.

### Set an IP Address
In order to get the rest of the internet to see your website on your ESP 8266 you'll need to tell your **router to always** assign a specific IP Address to your ESP 8266. This is due to how routers occassionally will need to switch IP addresses of a device. Bind the MAC Address of your Arduino to an IP address of your choosing. For this step you'll need to look at some tutorials for your specific router.

### Making it Public
You'll also need to figure out how to make a device on your local network public to the rest of the internet. Every router has different steps to achieve this.

### Domain Name
You don't actually need a domain name. You could just point people to an IP address such as: [http://69.172.169.8:801](http://69.172.169.8:801) <br>
`69.172.169.8` is the public IP address for my router. <br>
`801` is the port I specified in the Arduino sketch. <br>

However, it is cleaner if you have a domain name. I recommend [Name Cheap](https://www.namecheap.com) for buying a domain name.

Once you have a domain you'll need to point it to the public `IPaddress:port`

### Security
It is not good practice to store your WiFi Password in plaintext like it is shown in the Sketch, but this is another whole topic. You can look up separate tutorials on Arduino server security.
