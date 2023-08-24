#define BUTTON_PIN_BITMASK 0x14  // 2^2 + 2^4 in hex
RTC_DATA_ATTR int bootCount = 0;  // Number of reboots
void print_GPIO_wake_up()  // Function for determining the GPIO that caused the wake-up
{
  uint64_t GPIO_number = esp_sleep_get_ext1_wakeup_status();
  Serial.print("Wake up caused because of GPIO: ");
  Serial.println((log(GPIO_number))/log(2), 0);
}
void setup()
{
  Serial.begin(115200);  // Start serial port at 115200 baud rate
  bootCount++;  // Increment the number of boots by 1
  Serial.println("Boot number: " + String(bootCount));  // Print the boot number
  print_GPIO_wake_up();  // Determine which GPIO caused the wake-up
  Serial.println("I'm going to sleep now.");  // Print a statement before entering deep sleep
  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);  // Configure external wake-up
  delay(1000);  // Adding a 1 second delay to avoid multiple presses
  esp_deep_sleep_start();  // Enter deep sleep mode
}
void loop()
{
}
