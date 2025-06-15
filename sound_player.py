import serial
import pygame
import time

# pygame mixer for sound
pygame.mixer.init()

# upload sounds
sound1 = pygame.mixer.Sound("/Users/laulanassimoldina/Desktop/UAL CCI/UAL CCI/Year 1/OYU DJ Deck/python/data/aliya.mp3")
# For sound2, we'll use pygame.mixer.music
pygame.mixer.music.load("/Users/laulanassimoldina/Desktop/UAL CCI/UAL CCI/Year 1/OYU DJ Deck/python/data/kazakh.mp3")

# Create channels for better control (channel1 for sound1)
channel1 = pygame.mixer.Channel(0)

# track sound states
sound1_playing = False
sound2_playing = False
sound2_paused = False # New state to track if music is paused

# arduino connection
try:
    arduino = serial.Serial('/dev/cu.usbmodem14101', 9600)  # match port
    time.sleep(2)

    print("Listening for touch events...")

    while True:
        if arduino.in_waiting > 0:
            message = arduino.readline().decode().strip()
            print(f"Received: '{message}'")

            if message == "TOUCH1":
                if not sound1_playing:
                    print("Touch 1 detected! Playing sound 1...")
                    channel1.play(sound1, loops=-1)
                    sound1_playing = True

            elif message == "RELEASE1":
                if sound1_playing:
                    print("Touch 1 released! Stopping sound 1...")
                    channel1.stop()
                    sound1_playing = False

            elif message == "TOUCH2":
                if not sound2_playing:
                    print("Touch 2 detected! Playing sound 2 (music)...")
                    if sound2_paused: # If it was paused, unpause it
                        pygame.mixer.music.unpause()
                        sound2_paused = False
                    else: # Otherwise, start from beginning (or last actual stop point)
                        pygame.mixer.music.play(loops=-1)
                    sound2_playing = True

            elif message == "RELEASE2":
                if sound2_playing:
                    print("Touch 2 released! Pausing sound 2 (music)...")
                    pygame.mixer.music.pause()
                    sound2_paused = True # Mark as paused
                    sound2_playing = False # Not actively playing (but paused)

            elif message.startswith("Value:"):
                print(f"Sensor value: {message}")

except KeyboardInterrupt:
    print("Stopping...")
except Exception as e:
    print(f"Error: {e}")
finally:
    # stop all sounds and close connections
    if 'channel1' in locals():
        channel1.stop()
    pygame.mixer.music.stop() # Stop music
    if 'arduino' in locals():
        arduino.close()
    pygame.mixer.quit()