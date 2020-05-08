# MOTION-BASED-MESSAGE-CONVEYER-FOR-PARALYTIC-PATIENTS
We got inspired from the late Stephan Hawking on how he communicated to everyone though he was paralyzed. Our project would work more efficiently for those paralytic people who cannot communicate using their voice and can at least move their limbs to an extent. We place a sensor on one of their moving limbs, and for each movement, a message would be displayed on the LCD and different sounds would be transmitted from the buzzer for different movements. First the sensor reads the signal and since the signal is analog, we convert this signal to digital using Arduino Nano. This Arduino Nano acts like an Analog to Digital convertor and this is connected to a microcontroller viz a decoder. This decoder decodes the digital output and sends it to the LCD and buzzer via the microcontroller. The LCD then displays the message for a movement and the buzzer transmits a sound for that movement. 