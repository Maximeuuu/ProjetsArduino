#include <iostream>
#include <string>
#include <Windows.h> // Inclure cet en-tête si vous êtes sous Windows
// #include <unistd.h> // Utiliser cette ligne à la place si vous êtes sous macOS ou Linux

int main()
{
    HANDLE hSerial;
    hSerial = CreateFile("\\\\.\\COM9", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        std::cout << "Impossible d'ouvrir le port série." << std::endl;
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        std::cout << "Impossible de lire la configuration du port série." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Assurez-vous que le débit binaire est correct (9600 dans cet exemple)
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        std::cout << "Impossible de configurer le port série." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    char szBuff[64];
    DWORD bytesRead;
    std::string receivedData;

    while (true)
    {
		std::cout << "test" << std::endl;
        if (ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &bytesRead, NULL))
        {
            szBuff[bytesRead] = '\0';
            receivedData += szBuff;

            // Recherche du caractère de fin de ligne pour savoir si une commande complète a été reçue
            size_t pos = receivedData.find('\n');
            if (pos != std::string::npos)
            {
                std::string hexValue = receivedData.substr(0, pos);
                // Traitez la valeur hexadécimale ici
                std::cout << "Valeur hexadécimale reçue : " << hexValue << std::endl;
                receivedData.erase(0, pos + 1);
            }
        }
        else
        {
            std::cout << "Erreur lors de la lecture du port série." << std::endl;
            break;
        }
    }

    CloseHandle(hSerial);
    return 0;
}
