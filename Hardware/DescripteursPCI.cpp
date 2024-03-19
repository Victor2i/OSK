#include <stdint.h>
#include "../Conversion.h"

namespace PCI {
    const char* DeviceClasses[] {
        "Non classifi�",
        "Contr�leur de stockage de masse",
        "Contr�leur de r�seau",
        "Contr�leur d'affichage",
        "Contr�leur multim�dia",
        "Contr�leur de m�moire",
        "P�riph�rique de pontage",
        "Contr�leur de communication simple",
        "P�riph�rique du syst�me de base",
        "Contr�leur de p�riph�rique d'entr�e",
        "Composant d'�nergie", 
        "Processeur",
        "Contr�leur de bus en s�rie",
        "Contr�leur sans fil",
        "Contr�leur intelligent",
        "Contr�leur de communication par satellite",
        "Contr�leur de chiffrement",
        "Contr�leur de traitement du signal",
        "Acc�l�rateur de traitement",
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
                        return "Contr�leur DRAM Express";
                    case 0x2918:
                        return "Contr�leur d'interface LPC";
                    case 0x2922:
                        return "Contr�leur SATA 6 ports [mode AHCI]";
                    case 0x2930:
                        return "Contr�leur SMBus";
                }
        }
        return ToHexString(DeviceID);
    }

    const char* MassStorageControllerSubclassName(uint8_t SubclassCode){
        switch (SubclassCode){
            case 0x00:
                return "Contr�leur de bus SCSI";
            case 0x01:
                return "Contr�leur IDE";
            case 0x02:
                return "Contr�leur de disquette";
            case 0x03:
                return "Contr�leur de bus IPI";
            case 0x04:
                return "Contr�leur RAID";
            case 0x05:
                return "Contr�leur ATA";
            case 0x06:
                return "ATA en s�rie";
            case 0x07:
                return "SCSI connect� en s�rie";
            case 0x08:
                return "Contr�leur de m�moire non volatile";
            case 0x80:
                return "Autre";
        }
        return ToHexString(SubclassCode);
    }

    const char* SerialBusControllerSubclassName(uint8_t SubclassCode){
        switch (SubclassCode){
            case 0x00:
                return "Contr�leur FireWire (IEEE 1394)";
            case 0x01:
                return "Bus ACCESS";
            case 0x02:
                return "SSA";
            case 0x03:
                return "Contr�leur USB";
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
                return "Contr�leur de bus en s�rie - Autre";
        }
        return ToHexString(SubclassCode);
    }

    const char* BridgeDeviceSubclassName(uint8_t SubclassCode){
        switch (SubclassCode){
            case 0x00:
                return "Pont h�te";
            case 0x01:
                return "Pont ISA";
            case 0x02:
                return "Pont EISA";
            case 0x03:
                return "Pont MCA";
            case 0x04:
                return "Pont PCI-�-PCI";
            case 0x05:
                return "Pont PCMCIA";
            case 0x06:
                return "Pont NuBus";
            case 0x07:
                return "Pont CardBus";
            case 0x08:
                return "Pont RACEway";
            case 0x09:
                return "Pont PCI-�-PCI";
            case 0x0A:
                return "Pont h�te InfiniBand vers PCI";
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
                        return "Contr�leur compatible VGA";
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
                                return "Interface sp�cifique au fournisseur";
                            case 0x01:
                                return "AHCI 1.0";
                            case 0x02:
                                return "Bus de stockage en s�rie";
                        }
                }
            case 0x03:
                switch (SubclassCode){
                    case 0x00:
                        switch (ProgIF){
                            case 0x00:
                                return "Contr�leur VGA";
                            case 0x01:
                                return "Contr�leur compatible 8514";
                        }
                }
            case 0x0C:
                switch (SubclassCode){
                    case 0x03:
                        switch (ProgIF){
                            case 0x00:
                                return "Contr�leur UHCI";
                            case 0x10:
                                return "Contr�leur OHCI";
                            case 0x20:
                                return "Contr�leur EHCI (USB2)";
                            case 0x30:
                                return "Contr�leur XHCI (USB3)";
                            case 0x80:
                                return "Non sp�cifi�";
                            case 0xFE:
                                return "P�riph�rique USB (pas un contr�leur h�te)";
                        }
                }    
        }
        return ToHexString(ProgIF);
    }
}