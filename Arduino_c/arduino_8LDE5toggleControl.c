/* DATA PIN AREA*/
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

//////////////////////////////////////////////////////////
///////////////////////////TOGGLES////////////////////////
int p5 = 3;
int p4 = 4;
int p3 = 5;
int p2 = 6;
int p1 = 7;
int rep = 0;

byte leds = 0;

void setup()
{
    // put your setup code here, to run once:
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    //inputs
    pinMode(p5, INPUT_PULLUP);
    pinMode(p4, INPUT_PULLUP);
    pinMode(p3, INPUT_PULLUP);
    pinMode(p2, INPUT_PULLUP);
    pinMode(p1, INPUT_PULLUP);
}

void loop()
{
    ReadMode();

    switch (rep)
    {
        //////////////////////////////////////////////
    case 00001:
    {
        b_Flashing(200);
    }
    break;

    case 00011:
    {
        b_Flashing(120);
    }
    break;

    case 00111:
    {
        b_Flashing(60);
    }
    break;

    case 01111:
    {
        b_Flashing(20);
    }
    break;

    case 11111:
    {
        // always on.
        for (int i = 0; i < 8; i++)
        {
            bitSet(leds, i);
            updateShiftRegister();
            delay(30);
        }
    }
    break;

    //////////////////////////////////////////////
    case 00010:
    {
        b_Flowing(200, false, false);
    }
    break;

    case 00110:
    {
        b_Flowing(200, false, true);
        delay(200);
    }
    break;

    case 01110:
    {
        b_Flowing(200, true, true);
        delay(200);
    }
    break;

    case 11110:
    {
        b_Flowing(80, false, false);
    }
    break;

    //////////////////////////////////////////////
    case 00100:
    {
        b_Random(120, 0);
    }
    break;

    case 01100:
    {
        b_Random(120, 120);
    }
    break;

    case 11100:
    {
        b_Random(50, 0);
    }
    break;

    //////////////////////////////////////////////
    case 01000:
    {
        b_Random(50, 50);
    }
    break;

    case 11000:
    {
        b_Flowing(40, false, true);
        delay(500);
    }
    break;

    //////////////////////////////////////////////
    case 10000:
    {
        b_Flowing(200, false, true);
        b_Flowing(200, true, true);
    }
    break;

    //////////////////////////////////////////////
    case 00000:
    {
        // all lights off
        leds = 0;
        updateShiftRegister();
        delay(10);
    }
    break;

    default:
        break;
    }
}

// mode reading
void ReadMode()
{
    rep = read(p1) * 1;
    rep += read(p2) * 10;
    rep += read(p3) * 100;
    rep += read(p4) * 1000;
    rep += read(p5) * 10000;
}

// help reading digits
int read(int pin)
{
    if (digitalRead(pin) == LOW)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// [FUNCTION 1]
void b_Flashing(int mseconds)
{
    leds = 0;
    updateShiftRegister();
    delay(mseconds);

    for (int i = 0; i < 8; i++)
    {
        bitSet(leds, i);
        updateShiftRegister();
    }
    delay(mseconds);
}

// [FUNCTION 2]
void b_Flowing(int mseconds, bool reverse, bool single)
{
    leds = 0;
    updateShiftRegister();
    delay(3);
    if (reverse)
    {
        for (int i = 7; i >= 0; i--)
        {
            bitSet(leds, i);
            updateShiftRegister();
            delay(mseconds);
            if (single)
            {
                leds = 0;
                updateShiftRegister();
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            bitSet(leds, i);
            updateShiftRegister();
            delay(mseconds);
            if (single)
            {
                leds = 0;
                updateShiftRegister();
            }
        }
    }
}

// [FUNCTION 3]
void b_Random(int mseconds, int dim_delay)
{
    static int last_pin = -1;
    int now_pin = -1;
    while (now_pin == last_pin)
    {
        now_pin = rand() % 8;
    }
    bitSet(leds, now_pin);
    updateShiftRegister();
    delay(mseconds);
    //clear to 0
    leds = 0;
    updateShiftRegister();
    last_pin = now_pin;
    delay(dim_delay);
}

void updateShiftRegister()
{
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
    digitalWrite(latchPin, HIGH);
}