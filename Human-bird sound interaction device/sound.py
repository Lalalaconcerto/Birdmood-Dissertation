import pygame
from pygame.locals import * 
from time import sleep 
from gpiozero import Button
from gpiozero import LED


#define GPI for Button
button1 = Button(4)
led = LED(17)


pygame.mixer.init()

contact = pygame.mixer.Sound("/home/pi/contact_show/tweet2.wav")
# contact2 = pygame.mixer.Sound("/home/pi/contact_show/contact2.wav")

# btn_contact1 = Button(4)
# btn_contact2 = Button(17)


# def playmusic():
#     contact1.play()
#     if btn_contact2.when_pressed:
#         contact2.play()
#         print("contact2 play")
#         sleep(10)
    

while True:
    # playmusic()
    if button1.is_pressed:
        contact.play()
        # led.on()
        # print("contact1 play")
        sleep(1)
    else: 
        print("button is not pressed")
        # sleep(1)

    



