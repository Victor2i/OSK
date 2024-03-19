#include <stdint.h>
#include "../Conversion.h"

namespace PCI {
    const char* DeviceClasses[] {
        "Non classifié",
        "Contrôleur de stockage de masse",
        "Contrôleur de réseau",
        "Contrôleur d'affichage",
        "Contrôleur multimédia",
        "Contrôleur de mémoire",
        "Périphérique de pontage",
        "Contrôleur de communication simple",
        "Périphérique du système de base",
        "Contrôleur de périphérique d'entrée",
        "Composant d'énergie", 
        "Processeur",
        "Contrôleur de bus en série",
        "Contrôleur sans fil",
        "Contrôleur intelligent",
        "Contrôleur de communication par satellite",
        "Contrôleur de chiffrement",
        "Contrôleur de traitement du signal",
        "Accélérateur de traitement",
        "Instrumentation non essentielle"
    };

    const char* GetVendorName(uint16_t VendorID){
        switch (VendorID){
            case 0x8086:
                return "Intel Corporation";
            case 0x1022:
                return "AMD";
            case 0x10DE:
                return "NVIDIA Corporation";
        }
        return ToHexString(VendorID);
    }

    const char* GetDeviceName(uint16_t VendorID, uint16_t DeviceID){
        switch (VendorID){
            case 0x8086: // Intel
                switch(DeviceID){
                    case 0x29C0:
                        return "Contrôleur DRAM Express";
                    case 0x2918:
                        return "Contrôleur d'interface LPC";
                    case 0x2922:
                        return "Contrôleur SATA 6 ports [mode AHCI]";
                    case 0x2930:
                        return "Contrôleur SMBus";
                }
        }
        return ToHexString(DeviceID);
    }

    const char* MassStorageControllerSubclassName(uint8_t SubclassCode){
        switch (SubclassCode){
            case 0x00:
                return "Contrôleur de bus SCSI";
            case 0x01:
                return "Contrôleur IDE";
            case 0x02:
                return "Contrôleur de disquette";
            case 0x03:
                return "Contrôleur de bus IPI";
            case 0x04:
                return "Contrôleur RAID";
            case 0x05:
                return "Contrôleur ATA";
            case 0x06:
                return "ATA en série";
            case 0x07:
                return "SCSI connecté en série";
            case 0x08:
                return "Contrôleur de mémoire non volatile";
            case 0x80:
                return "Autre";
        }
        return ToHexString(SubclassCode);
    }

    const char* SerialBusControllerSubclassName(uint8_t SubclassCode){
        switch (SubclassCode){
            case 0x00:
                return "Contrôleur FireWire (IEEE 1394)";
            case 0x01:
                return "Bus ACCESS";
            case 0x02:
                return "SSA";
            case 0x03:
                return "Contrôleur USB";
            case 0x04:
                return "Canal fibre";
            case 0x05:
                return "SMBus";
            case 0x06:
                return "Infiniband";
            case 0x07:
                return "Interface IPMI";
            case 0x08:
                return "Interface SERCOS (IEC 61491)";
            case 0x09:
                return "CANbus";
            case 0x80:
                return "Contrôleur de bus en série - Autre";
        }
        return ToHexString(SubclassCode);
    }

    const char* BridgeDeviceSubclassName(uint8_t SubclassCode){
        switch (SubclassCode){
            case 0x00:
                return "Pont hôte";
            case 0x01:
                return "Pont ISA";
            case 0x02:
                return "Pont EISA";
            case 0x03:
                return "Pont MCA";
            case 0x04:
                return "Pont PCI-à-PCI";
            case 0x05:
                return "Pont PCMCIA";
            case 0x06:
                return "Pont NuBus";
            case 0x07:
                return "Pont CardBus";
            case 0x08:
                return "Pont RACEway";
            case 0x09:
                return "Pont PCI-à-PCI";
            case 0x0A:
                return "Pont hôte InfiniBand vers PCI";
            case 0x80:
                return "Autre";
        }
        return ToHexString(SubclassCode);
    }

    const char* GetSubclassName(uint8_t ClassCode, uint8_t SubclassCode){
        switch (ClassCode){
            case 0x01:
                return MassStorageControllerSubclassName(SubclassCode);
            case 0x03:
                switch (SubclassCode){
                    case 0x00:
                        return "Contrôleur compatible VGA";
                }
            case 0x06:
                return BridgeDeviceSubclassName(SubclassCode);
            case 0x0C:
                return SerialBusControllerSubclassName(SubclassCode);
        }
        return ToHexString(SubclassCode);
    }

    const char* GetProgIFName(uint8_t ClassCode, uint8_t SubclassCode, uint8_t ProgIF){
        switch (ClassCode){
            case 0x01:
                switch (SubclassCode){
                    case 0x06:
                        switch (ProgIF){
                            case 0x00:
                                return "Interface spécifique au fournisseur";
                            case 0x01:
                                return "AHCI 1.0";
                            case 0x02:
                                return "Bus de stockage en série";
                        }
                }
            case 0x03:
                switch (SubclassCode){
                    case 0x00:
                        switch (ProgIF){
                            case 0x00:
                                return "Contrôleur VGA";
                            case 0x01:
                                return "Contrôleur compatible 8514";
                        }
                }
            case 0x0C:
                switch (SubclassCode){
                    case 0x03:
                        switch (ProgIF){
                            case 0x00:
                                return "Contrôleur UHCI";
                            case 0x10:
                                return "Contrôleur OHCI";
                            case 0x20:
                                return "Contrôleur EHCI (USB2)";
                            case 0x30:
                                return "Contrôleur XHCI (USB3)";
                            case 0x80:
                                return "Non spécifié";
                            case 0xFE:
                                return "Périphérique USB (pas un contrôleur hôte)";
                        }
                }    
        }
        return ToHexString(ProgIF);
    }
}