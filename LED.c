#include <lpc21xx.h>  // LPC2129 specific hardware definitions

// Define LED settings structure
typedef struct {
    uint8_t state;      // LED ON or OFF state (1 for ON, 0 for OFF)
    uint8_t brightness; // Brightness level (0 to 255)
    uint32_t color;     // Color in RGB format  
} LED_settings;

// Define LED group structure
typedef struct {
    LED_settings single_LED;    // Individual LED settings
    uint8_t group_state;       // Collective state of the group (1 for all ON, 0 for all OFF)
    uint8_t group_brightness;  // Collective brightness adjustment for the group
} LED_group;

// Function prototypes
void init_LED_group(LED_group *group);
void update_LED_group_settings(LED_group *group, uint8_t group_state, uint8_t group_brightness, uint8_t state, uint8_t brightness, uint32_t color);
void delay(unsigned int ms);

// Initialize LED Group with default values
void init_LED_group(LED_group *group) {
    if (group != NULL) {
        group->single_LED.state = 0;        // LEDs OFF
        group->single_LED.brightness = 0;   // Minimum brightness
        group->single_LED.color = 0x000000; // No color (0xRRGGBB)
        group->group_state = 0;             // All LEDs OFF in the group
        group->group_brightness = 0;        // Minimum brightness for the group

        // Set up GPIO pins for LEDs (assuming Port 1 Pins 17,18,19)
        IODIR1 |= (1 << 17) | (1 << 18) | (1 << 19);  // Set P1.17, P1.18, P1.19 as output (for 3 LEDs)
    }
}

// Function to update LED Group Settings and control the hardware
void update_LED_group_settings(LED_group *group, uint8_t group_state, uint8_t group_brightness, uint8_t state, uint8_t brightness, uint32_t color) {
    if (group != NULL) {
        // Update individual LED settings
        group->single_LED.state = state;
        group->single_LED.brightness = brightness;
        group->single_LED.color = color;

        // Update group settings
        group->group_state = group_state;
        group->group_brightness = group_brightness;

        // Control hardware
        if (group->single_LED.state) {
            IOSET1 = (1 << 17);   // Turn ON LED at P1.17
        } else {
            IOCLR1 = (1 << 17);   // Turn OFF LED at P1.17
        }

        // If group state is ON, turn on additional LEDs (e.g., P1.18, P1.19)
        if (group->group_state) {
            IOSET1 = (1 << 18) | (1 << 19);   // Turn ON LEDs at P1.18 and P1.19
        } 
        else {
            IOCLR1 = (1 << 18) | (1 << 19);   // Turn OFF LEDs at P1.18 and P1.19
        }
    }
}

// Simple delay function
void delay(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++);  // Approximate delay for 1 ms
    }
}

// Main function for LED control
int main(void) {
    LED_group led_group;

    // Initialize the LED group
    init_LED_group(&led_group);

    while (1) {
        // Turn ON individual LED, group ON, brightness 255
        update_LED_groups_settings(&led_group, 1, 255, 1, 255, 0x1257FF);  // Example update
        delay(1000);  // Delay for 1 second

        // Turn OFF all LEDs
        update_LED_group_settings(&led_group, 0, 0, 0, 0, 0x000000);  // Turn off LEDs
        delay(1000);  // Delay for 1 second
    }

    return 0;
}
// In order to execute or run the code in Keil built the code choose appropriate Flash magi use HEX file, set the baud rate JTAG it to the hardware and verify.
