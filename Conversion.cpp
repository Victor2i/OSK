#include "Conversion.h"

char UIntToStringOutput[32];
const char* ToString(uint64_t Value){ // Renvoie un entier non-signé sous forme de string
    uint8_t Size = 0;
    uint64_t SizeTest = Value;
    while (SizeTest / 10 > 0){ // Test avec des divisions successives pour déterminer la taille de la string
        SizeTest /= 10;
        Size++;
    }

    uint8_t Index = 0;
    while(Value / 10 > 0){
        uint8_t Remainder = Value % 10;
        Value /= 10;
        UIntToStringOutput[Size - Index] = Remainder + '0'; // On convertit le digit en char
        Index++;
    }
    uint8_t Remainder = Value % 10;
    UIntToStringOutput[Size - Index] = Remainder + '0'; // On convertit le digit en char
    UIntToStringOutput[Size + 1] = 0; // octet nul
    return UIntToStringOutput;
}

const char* ToString(uint32_t Value){
    return ToString((uint64_t)Value);
}

const char* ToString(uint16_t Value){
    return ToString((uint64_t)Value);
}

const char* ToString(uint8_t Value){
    return ToString((uint64_t)Value);
}

char HexToStringOutput[20];
const char* ToHexString(uint64_t Value){ // Renvoie un entier hexadécimal non-signé sous forme de string
    uint64_t* ValuePtr = &Value;
    uint8_t* Ptr;
    uint8_t Temp;
    uint8_t Size = 15;
    for (uint8_t i = 0; i < Size; i++){
        Ptr = ((uint8_t*)ValuePtr + i);
        Temp = ((*Ptr & 0xF0) >> 4); // Premier digit
        HexToStringOutput[Size - (i * 2 + 1)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
        Temp = ((*Ptr & 0x0F)); // Deuxième digit
        HexToStringOutput[Size - (i * 2)] = Temp + (Temp > 9 ? 55 : '0'); // On refait une conversion
    }
    HexToStringOutput[Size + 1] = 0; // octet nul
    return HexToStringOutput;
}

const char* ToHexString(int64_t Value){
    return ToHexString((uint64_t)Value);
}

char HexToStringOutput32[16];
const char* ToHexString(uint32_t Value){ // Renvoie un entier hexadécimal non-signé codé sur 32-bits sous forme de string
    uint32_t* ValuePtr = &Value;
    uint8_t* Ptr;
    uint8_t Temp;
    uint8_t Size = 7;
    for (uint8_t i = 0; i < Size; i++){
        Ptr = ((uint8_t*)ValuePtr + i);
        Temp = ((*Ptr & 0xF0) >> 4);
        HexToStringOutput32[Size - (i * 2 + 1)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
        Temp = ((*Ptr & 0x0F));
        HexToStringOutput32[Size - (i * 2)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
    }
    HexToStringOutput32[Size + 1] = 0; // octet nul
    return HexToStringOutput32;
}

const char* ToHexString(int32_t Value){
    return ToHexString((uint32_t)Value);
}

char HexToStringOutput16[8];
const char* ToHexString(uint16_t Value){ // Renvoie un entier hexadécimal non-signé codé sur 16-bits sous forme de string
    uint16_t* ValuePtr = &Value;
    uint8_t* Ptr;
    uint8_t Temp;
    uint8_t Size = 3;
    for (uint8_t i = 0; i < Size; i++){
        Ptr = ((uint8_t*)ValuePtr + i);
        Temp = ((*Ptr & 0xF0) >> 4);
        HexToStringOutput16[Size - (i * 2 + 1)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
        Temp = ((*Ptr & 0x0F));
        HexToStringOutput16[Size - (i * 2)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
    }
    HexToStringOutput16[Size + 1] = 0; // octet nul
    return HexToStringOutput16;
}

const char* ToHexString(int16_t Value){
    return ToHexString((uint16_t)Value);
}

char HexToStringOutput8[8];
const char* ToHexString(uint8_t Value){ // Renvoie un entier hexadécimal non-signé codé sur 8-bits sous forme de string
    uint8_t* ValuePtr = &Value;
    uint8_t* Ptr;
    uint8_t Temp;
    uint8_t Size = 1;
    for (uint8_t i = 0; i < Size; i++){
        Ptr = ((uint8_t*)ValuePtr + i);
        Temp = ((*Ptr & 0xF0) >> 4);
        HexToStringOutput8[Size - (i * 2 + 1)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
        Temp = ((*Ptr & 0x0F));
        HexToStringOutput8[Size - (i * 2)] = Temp + (Temp > 9 ? 55 : '0'); // On convertit le digit en char
    }
    HexToStringOutput8[Size + 1] = 0; // octet nul
    return HexToStringOutput8;
}

const char* ToHexString(int8_t Value){
    return ToHexString((uint8_t)Value);
}

char IntToStringOutput[24];
const char* ToString(int64_t Value){ // Renvoie un entier signé sous forme de string
    if (Value == 0x8000000000000000) return "-9223372036854775808"; // Cas isolé

    uint8_t IsNegative = 0; // La variable doit être un nombre et non un booléen pour des raisons d'optimisation

    if (Value < 0){ // On vérifie si le nombre est négatif
        IsNegative = 1; // Décalera la partie entière de 1 caractère
        Value *= -1; // On ne garde que la partie entière pour les calculs
        IntToStringOutput[0] = '-'; // Le premier caractère sera un signe
    }

    uint8_t Size = 0; // Variable donnant la longueur du nombre en caractères
    uint64_t SizeTest = Value;
    while (SizeTest / 10 > 0){ // Test avec des divisions successives pour déterminer la taille de la string
        SizeTest /= 10;
        Size++;
    }

    uint8_t Index = 0;
    while(Value / 10 > 0){
        uint8_t Remainder = Value % 10;
        Value /= 10;
        IntToStringOutput[IsNegative + Size - Index] = Remainder + '0'; // On convertit le digit en char
        Index++;
    }
    uint8_t Remainder = Value % 10;
    IntToStringOutput[IsNegative + Size - Index] = Remainder + '0'; // On convertit le digit en char
    IntToStringOutput[IsNegative + Size + 1] = 0; 
    return IntToStringOutput;
}

const char* ToString(int32_t Value){
    return ToString((int64_t)Value);
}

const char* ToString(int16_t Value){
    return ToString((int64_t)Value);
}

const char* ToString(int8_t Value){
    return ToString((int64_t)Value);
}

char DoubleToStringOutput[64];
const char* ToString(double Value, uint8_t DecimalPlaces) {
    if (DecimalPlaces > 16 || DecimalPlaces == 0) DecimalPlaces = 16; // On définit une limite de chiffres après la virgule
    uint8_t SignificantDigits = DecimalPlaces + 1; // Chiffres significatifs (pour les nombres affichés en notation scientifique)

    // Cas particuliers

    uint64_t x;
    x = *(uint64_t*)&Value; // Hack qui permet de lire les flottants en tant que entiers

    switch (x) {
        case 0x0000000000000000: // Zéro
            return "0.0";
        case 0x8000000000000000: // Moins zéro
            return "-0.0";
        case 0x7FF0000000000000: // Infini
            return "inf";
        case 0xFFF0000000000000: // Moins l'infini
            return "-inf";
    }

    if (x > 0x7FF0000000000000 && x <= 0x7FFFFFFFFFFFFFFF) {
        return "nan";
    }
    else if (x > 0xFFF0000000000000 && x <= 0xFFFFFFFFFFFFFFFF) {
        return "-nan";
    }

    // Cas généraux

    uint8_t IsNegative = 0; // Cette variable doit être un nombre et non un booléen pour des raisons d'optimisation

    if (Value < 0.0) { // On vérifie si le nombre est négatif
        IsNegative = 1; // Décalera la partie entière de 1 caractère
        Value *= -1.0; // On ne garde que la partie entière pour les calculs
        DoubleToStringOutput[0] = '-'; // Le premier caractère sera un signe
    }

    char* DoublePtr = DoubleToStringOutput + IsNegative; // On crée un pointeur se trouvant à la position du premier charactère de la string

    uint16_t Size = 0;
    double SizeTest = Value;
    uint8_t Index = 0;
    bool NzTest = true;
    uint8_t Remainder;
    double SizeTestD = 0.1;
    double ValueEx;
    uint64_t ValueExInt;
    if (Value >= 1.0) { // Dans ce cas on compte le nombre de chiffres avant la virgule
        while (SizeTest >= 1.0) { // On vérifie la taille du nombre
            SizeTest /= 10.0;
            SizeTestD *= 10.0;
            Size++;
        }
        if (Size > DecimalPlaces) { // Le nombre est trop grand pour être affiché
            // Phase 1: Nombre a

            for (uint8_t i = 1; i < SignificantDigits; i++) {
                SizeTestD /= 10.0;
            }
            ValueEx = Value / SizeTestD;
            ValueExInt = (uint64_t)ValueEx;
            while (ValueExInt > 0) {
                Remainder = ValueExInt % 10;
                ValueExInt /= 10;
                if (Index == SignificantDigits - 1) {
                    DoubleToStringOutput[IsNegative + SignificantDigits - Index] = '.'; // On place la virgule
                    Index++;
                }
                DoubleToStringOutput[IsNegative + SignificantDigits - Index] = Remainder + '0'; // On convertit le digit en char
                Index++;
            }

            // Phase 2: Exposant

            Index = 0;
            DoubleToStringOutput[IsNegative + SignificantDigits + 1] = 'E'; // On place le symbole de puissance de dix
            const char* PowStrPtr = ToString((uint64_t)Size - 1);
            while (PowStrPtr[Index] != 0) {
                DoubleToStringOutput[IsNegative + SignificantDigits + 2 + Index] = PowStrPtr[Index]; // On place le digit
                Index++;
            }

            DoubleToStringOutput[IsNegative + SignificantDigits + 2 + Index] = 0; // Null
        }
        else {
            // Phase 1: Partie entière

            ValueEx = Value;
            ValueExInt = (uint64_t)ValueEx;
            Index = 1;
            while (ValueExInt > 0) {
                Remainder = ValueExInt % 10;
                ValueExInt /= 10;
                DoubleToStringOutput[IsNegative + Size - Index] = Remainder + '0'; // On convertit le digit en char
                Index++;
            }
            DoubleToStringOutput[IsNegative + Size] = '.'; // On place la virgule

            // Phase 2: Partie non-entière

            ValueExInt = (uint64_t)ValueEx;
            ValueEx -= ValueExInt;
            Index = SignificantDigits;
            for (uint8_t i = 1; i <= SignificantDigits; i++) {
                ValueEx *= 10.0;
                ValueExInt = (uint64_t)ValueEx;
                ValueEx -= ValueExInt;
                if (ValueExInt == 0) {
                    if (i > 1 && NzTest) { 
                        Index = i - 1;
                        NzTest = false;
                    }
                }
                else {
                    Index = i - 1;
                    NzTest = true;
                }
                DoubleToStringOutput[IsNegative + Size + i] = ValueExInt + '0'; // On convertit le digit en char
            }

            DoubleToStringOutput[IsNegative + Size + Index + 1] = 0; // Null
        }
    }
    else if (Value < 1.0) { // Dans ce cas on compte le nombre de zéros avant le premier chiffre n'étant pas un zéro
        SizeTestD = 10.0;
        while (SizeTest < 1.0) { // On vérifie la taille du nombre
            SizeTest *= 10.0;
            SizeTestD /= 10.0;
            Size++;
        }
        if (Size > DecimalPlaces) { // Le nombre est trop grand pour être affiché
            // Phase 1: Nombre a

            ValueEx = Value / SizeTestD;
            ValueExInt = (uint64_t)ValueEx;
            for (uint8_t i = 0; i < SignificantDigits; i++) {
                ValueEx *= 10;
                ValueExInt = (uint64_t)ValueEx;
                Remainder = ValueExInt % 10;
                if (i == 1) {
                    DoubleToStringOutput[IsNegative + Index] = '.'; // On place la virgule
                    Index++;
                }
                DoubleToStringOutput[IsNegative + Index] = Remainder + '0'; // On convertit le digit en char
                Index++;
            }

            // Phase 2: Exposant

            Index = 0;
            DoubleToStringOutput[IsNegative + SignificantDigits + 1] = 'E'; // On place le symbole de puissance de dix
            const char* PowStrPtr = ToString((uint64_t)Size);
            DoubleToStringOutput[IsNegative + SignificantDigits + 2] = '-'; // On place le signe
            while (PowStrPtr[Index] != 0) {
                DoubleToStringOutput[IsNegative + SignificantDigits + 3 + Index] = PowStrPtr[Index]; // On place le digit
                Index++;
            }

            DoubleToStringOutput[IsNegative + SignificantDigits + 3 + Index] = 0; // Null
        }
        else {
            ValueEx = Value;
            ValueExInt = (uint64_t)ValueEx;
            for (uint8_t i = 0; i < SignificantDigits; i++) {
                Remainder = ValueExInt % 10;
                ValueEx *= 10;
                ValueExInt = (uint64_t)ValueEx;
                ValueEx -= ValueExInt;
                if (i == 1) {
                    DoubleToStringOutput[IsNegative + Index] = '.'; // On place la virgule
                    Index++;
                }
                DoubleToStringOutput[IsNegative + Index] = Remainder + '0'; // On convertit le digit en char
                Index++;
            }

            DoubleToStringOutput[IsNegative + Index] = 0; // Null
        }
    }

	return DoubleToStringOutput;
}

const char* ToString(double Value){ // Renvoie un réel sous forme de string
    return ToString(Value, 2); // DecimalPlaces n'est pas spécifié, et donc par défaut on met 2 chiffres après la virgule.
}

const char* ToString(float Value, uint8_t DecimalPlaces){ // Renvoie un réel sous forme de string
    return ToString((double)Value, DecimalPlaces);
}

const char* ToString(float Value){ // Renvoie un réel sous forme de string
    return ToString((double)Value, 2); // DecimalPlaces n'est pas spécifié, et donc par défaut on met 2 chiffres après la virgule.
}