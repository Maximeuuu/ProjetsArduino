# Lemoine Maxime
# 14/07/23
# windows 11 + python 3.11
# nécessite imports + arduino nano + module IR + télécommande BIOSTEK


"""
Importations
"""
import serial
import pyautogui #https://pyautogui.readthedocs.io/en/latest/keyboard.html


"""
Lancement
"""
print("Programme de controle IR.")
print("=========================\n")

# variables
epgActive = False
volUpActive = False
volDownActive = False


"""
Communication Arduino
"""
# Paramètres de communication avec l'Arduino
ARDUINO_PORT = 'COM5'  # port série de l'Arduino
BAUD_RATE = 9600
print("Connexion à l'arduino nano au port : "+str(ARDUINO_PORT)+" - "+str(BAUD_RATE)+".")

# Paramètres de la télécommande
BIOSTEK_ID_HEX = '807F'
NULL_HEX = 'FFFFFFFF'
print("Utilisation de la télécommande BIOSTEK "+str(BIOSTEK_ID_HEX)+".")

# Ouvrir la connexion série avec l'Arduino
ser = serial.Serial(ARDUINO_PORT, BAUD_RATE)
print("\nAppairage réussi.")

print("Commandes : ")
print(" - standby : alt+f4")
print(" - mute : volumemute")
print(" - 1 : f10")
print(" - 2 : f11")
print(" - fav : favoris (spotify)")
print(" - 0 : menu")
print(" - recall : tab")
print(" - menu : win+s - barre de recherche")
print(" - epg : ctrl+alt+tab")
print(" - exit : esc")
print(" - haut : nexttrack")
print(" - gauche : volumedown")
print(" - ok : enter")
print(" - droite : volumeup")
print(" - bas : prevtrack")
print(" - text : win+h - saisie vocale")
print(" - rouge : f - plein écran")
print(" - vert : ctrl+l - rechercher (spotify)")
print(" - pause : playpause")
print(" - jaune : left")
print(" - bleu : right")

"""
Programme
"""
# Lecture en boucle des données de l'Arduino
while True:
    # Lire une ligne de données depuis l'Arduino
    data = ser.readline().decode().strip()
    print(data)

    # tester si les valeurs sont abberantes
    if not(data.startswith( BIOSTEK_ID_HEX ) and len(data) == 8 or data == NULL_HEX):
        continue

    # verification des touches actives et reinitialisation
    if not(data == NULL_HEX):
        if volUpActive:
            volUpActive = False
        if volDownActive:
            volDownActive = False

    """
    Utilisation normale
    """
    # standby
    if data == '807FC03F':
        pyautogui.hotkey('alt','f4')

    # mute
    if data == '807F40BF':
        pyautogui.press('volumemute')

    # 1
    if data == '807FE01F':
        pyautogui.press('f10')

    # 2
    if data == '807F609F':
        pyautogui.press('f11')


    # fav
    if data == '807FC837':
        pyautogui.keyDown('alt')
        pyautogui.keyDown('shift')
        pyautogui.press('b')
        pyautogui.keyUp('shift')
        pyautogui.keyUp('alt')

    # 0
    if data == '807F8877':
        pyautogui.press('home')

    # recall
    if data == '807F48B7':
        pyautogui.press('tab')

    # menu : barre de recherche
    if data == '807F18E7':
        pyautogui.keyDown('win')
        pyautogui.press('s')
        pyautogui.keyUp('win')

    # exit
    if data == '807F20DF':
        pyautogui.press('esc')

    # haut
    if data == '807F10EF':
        pyautogui.press('nexttrack')

    # gauche
    if data == '807F38C7' or volDownActive:
        pyautogui.press('volumedown')
        volDownActive = True

    # ok
    if data == '807F30CF':
        pyautogui.press('enter')

    # droite
    if data == '807F00FF' or volUpActive:
        pyautogui.press('volumeup')
        volUpActive = True

    # bas
    if data == '807F08F7':
        pyautogui.press('prevtrack')

    # text : saisie vocale
    if data == '807FD827':
        pyautogui.keyDown('win')
        pyautogui.press('h')
        pyautogui.keyUp('win')

    # rouge
    if data == '807F9867':
        pyautogui.press('f')

    # vert
    if data == '807F58A7':
        pyautogui.hotkey('ctrl','l')

    # pause
    if data == '807FF807':
        pyautogui.press('playpause')

    # jaune
    if data == '807FB847':
        ser.write('255,255,0\n'.encode())
        pyautogui.press('left')

    # bleu
    if data == '807F7887':
        ser.write('0,0,255\n'.encode())
        pyautogui.press('right')


    """
    Utilisation sur plusieurs temps
    """
    # epg : ctrl+alt+tab
    if data == '807F28D7':
        pyautogui.keyDown('win')
        pyautogui.press('m')
        pyautogui.keyUp('win')
        pyautogui.hotkey('ctrl','alt','tab')
        epgActive = True
    else:
        if epgActive:
            if data == 'FFFFFFFF':
                pyautogui.press('tab')
            else:
                epgActive = False
            continue
