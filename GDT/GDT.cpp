#include "GDT.h"

__attribute__((aligned(0x1000)))
GDT DefaultGDT = {
    {0, 0, 0, 0x00, 0x00, 0}, // non-défini
    {0, 0, 0, 0x9a, 0xa0, 0}, // segment de code
    {0, 0, 0, 0x92, 0xa0, 0}, // segment de données
    {0, 0, 0, 0x00, 0x00, 0}, // (user) non-défini
    {0, 0, 0, 0x9a, 0xa0, 0}, // (user) segment de code
    {0, 0, 0, 0x92, 0xa0, 0}, // (user) segment de données
};