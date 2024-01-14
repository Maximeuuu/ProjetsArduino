# Lemoine Maxime
# 17/07/23
# windows 11 + python 3.11
# nécessite imports + arduino nano + module IR + télécommande DVD video

import serial
import pyautogui

class KeycodeProcessor:
    BIOSTEK_ID_HEX = '807F'
    NULL_HEX = 'FFFFFFFF'
	ARDUINO_PORT = 'COM9'  # port série de l'Arduino
	BAUD_RATE = 9600

    def __init__(self):

        self.ser = serial.Serial(ARDUINO_PORT, BAUD_RATE)
        self.vol_up_active = False
        self.vol_down_active = False

		self.keycode_commands = {
    		'807FC03F': ['alt', 'f4'],  # standby
		    '807F40BF': ['volumemute'],  # mute
		    '807FE01F': ['f10'],  # 1
		    '807F609F': ['f11'],  # 2
		    '807FC837': ['alt', 'shift', 'b'],  # fav
		    '807F8877': ['home'],  # 0
		    '807F48B7': ['tab'],  # recall
		    '807F18E7': ['win', 's'],  # menu : barre de recherche
		    '807F20DF': ['esc'],  # exit
		    '807F10EF': ['nexttrack'],  # haut
		    '807F38C7': ['volumedown'],  # gauche
			'807F30CF': ['enter'],  # ok
		    '807F00FF': ['volumeup'],  # droite
		    '807F08F7': ['prevtrack'],  # bas
		    '807FD827': ['win', 'h'],  # text : saisie vocale
		    '807F9867': ['f'],  # rouge
		    '807F58A7': ['ctrl', 'l'],  # vert
		    '807FF807': ['playpause'],  # pause
		    '807FB847': ['left'],  # jaune
		    '807F7887': ['right']  # bleu
		}

"""if data in commands:
    keys = commands[data]
    for key in keys:
        pyautogui.press(key)
    if 'volumedown' in keys:
        volDownActive = True
    if 'volumeup' in keys:
        volUpActive = True
    if 'left' in keys:
        ser.write('255,255,0\n'.encode())
    if 'right' in keys:
        ser.write('0,0,255\n'.encode())

        }"""

    def process_keycode(self, keycode):
        if not (keycode.startswith(self.BIOSTEK_ID_HEX) and len(keycode) == 8) or keycode == self.NULL_HEX:
            return

        if keycode == self.NULL_HEX:
            self.vol_up_active = False
            self.vol_down_active = False

        # Commandes associées aux touches
        if keycode in self.keycode_commands:
            commands = self.keycode_commands[keycode]
            for command in commands:
                pyautogui.hotkey(command)

        if keycode == '807F38C7' or self.vol_down_active:
            pyautogui.press('volumedown')
            self.vol_down_active = True
        elif keycode == '807F00FF' or self.vol_up_active:
            pyautogui.press('volumeup')
            self.vol_up_active = True

    def start(self):
        print("Programme de contrôle IR.")
        print("=========================\n")
        print("Connexion à l'Arduino nano au port : COM9 - 9600.")
        self.ser.readline()  # Lecture en boucle des données de l'Arduino
        while True:
            data = self.ser.readline().decode().strip()
            self.process_keycode(data)

# Utilisation de la classe KeycodeProcessor
if __name__ == "__main__":
    keycode_processor = KeycodeProcessor()
    keycode_processor.start()
