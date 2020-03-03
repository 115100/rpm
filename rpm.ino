#define FAN_PIN               2
#define HEADER_PIN            3
#define MIN_FAN_RPM           600
#define DEFAULT_TACH_DELAY_MS 60e3 / MIN_FAN_RPM / 2

volatile unsigned long last_interrupt;
volatile unsigned long tach_delay = DEFAULT_TACH_DELAY_MS;

void setup()
{
	pinMode(FAN_PIN, INPUT_PULLUP);
	pinMode(HEADER_PIN, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(FAN_PIN), set_delay, CHANGE);
}

void loop()
{
	digitalWrite(FAN_PIN, HIGH);
	delay(tach_delay);
	digitalWrite(FAN_PIN, LOW);
	delay(tach_delay);
}

void set_delay()
{
	unsigned long cur = millis();

	unsigned long diff = cur - last_interrupt;
	if (diff > DEFAULT_TACH_DELAY_MS)
		tach_delay = DEFAULT_TACH_DELAY_MS;
	else
		tach_delay = diff;

	last_interrupt = cur;
}
