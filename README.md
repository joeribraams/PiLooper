# PiLooper
Audio Looper for Raspberry Pi

Demo: https://www.youtube.com/watch?v=o57Znnf2OC8&feature=youtu.be

Concept:

Een looperpedaal voor gitaar, waarmee je handsfree kan opnemen en afspelen. De gebruiker moet opnemen, opname stoppen, loop stoppen en een nieuwe loop beginnen allemaal met een voetschakelaar kunnen bedienen. Hiervoor ga ik een debouncealgoritme voor de schakelaar moeten gaan ontwerpen. Opnemen en loopen lijkt me een vrij triviale stap, het zal vooral de controle zijn waar veel denkwerk in gaat moeten. Mogelijk ga ik nog andere opties, bijvoorbeeld om de loops te gaan omvormen, implementeren, maar dat zie ik als optioneel. Ik denk dat ik alles in C++ ga programmeren voor de lage latency.

Componenten:

-	Raspberry Pi
Ik ga een rPI Zero WL gebruiken omdat ik die nog heb liggen, zou ook met een andere	versie kunnen. Ik heb wel een USB OTG kabel nodig omdat ik de Zero gebruik.

-	Audio IO
Ik ga in the interest of time een simpele USB ADAC gebruiken, maar het liefst zou ik losse ADC en DAC chipjes via I2C ofzo op de rPI aansluiten, om meer grip te hebben op wat er daadwerkelijk under the hood gebeurt. Waarschijnlijk is dit het enige wat ik voor dit project aan moet schaffen.

-	IO buffers
Waarschijnlijk werkt de ADAC op lijnniveau, dit is niet heel optimaal voor de hoge impedantie van een gitaarsignaal, om tijd te besparen ga ik kijken of de resultaten acceptabel genoeg zijn als ik het zonder doe, maar zo nodig bouw ik een simpel buffertje met een TL072 en wat overige passives.

-	Voetschakelaar
Ik heb nog hoogwaardige effectenpedaal voetschakelaars liggen, maar dit zou ook met een simpele momentary NO schakelaar of zelfs een tactile switch kunnen, maar ik wil wel voor een beetje betrouwbaar gaan

-	Aansluitbussen
Afhankelijk aan de bronnen die je er mee wilt gebruiken zou je dit anders kunnen doen, maar voor gitaareffecten zijn 6.35mm audio jacks en 2.1mm dc jacks standaard. Wederom materiaal wat ik nog heb liggen. Ook zal een voltage regulator nodig zijn om de (voor effectenpedalen standaard) 9v om te vormen naar 3v3 voor de rPI

-	Led
Handig voor indicatie van het effect, kan mogelijk ook voor wat debugging helpen.

-	Behuizing
Hier kan je heel creatief mee worden, maar ik denk dat ik gewoon een oude behuizing van een vorig project hergebruik.

Wiring:
- Footswitch between 3.3v and GPIO17 with a 470k resistor between GPIO17 and ground
- LED between GPIO18 and GND with a +- 1k current limiting resistor
- Power off button between GPIO22 and GND
- 9v to a 78l05 to the 5v input and GND of the pi.

Steps:

1.  Install fresh copy of raspbian lite.

2.  Setup connection via SSH or monitor and keyboard.

3.  Connect and install USB sound card like so: https://www.raspberrypi-spy.co.uk/2019/06/using-a-usb-audio-device-with-the-raspberry-pi/

4.  Install and set up jack on the PI.

5.  Install git on rpi and clone this directory on the root folder.

6.  install pyton3 and move shutdown.py to the home directory.

7.  move rc.local to /etc/ and reboot.
