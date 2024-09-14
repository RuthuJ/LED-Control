#include <stdio.h>
#include <stdint.h>

// Structure to represent individual LED settings
typedef struct {
    uint8_t state;       // LED ON or OFF state (1 = ON, 0 = OFF)
    uint8_t brightness;  // LED brightness level (0 - 255)
    uint32_t color;      // LED color in RGB format
} LED_settings;

// Structure to represent a group of LEDs
typedef struct {
    LED_settings single_LED;   // Individual LED settings
    uint8_t group_state;      // Group ON or OFF state (1 = all ON, 0 = all OFF)
    uint8_t group_brightness; // Group brightness adjustment (0 - 255)
} LED_group;

// Function to initialize an LED group with default values
void initLED_group(LED_group *group) {
    group->single_LED.state = 0;               // Set individual LED to OFF
    group->single_LED.brightness = 0;          // Set brightness to minimum
    group->single_LED.color = 0x000000;        // Set color default
    group->group_state = 0;                    // Set group to OFF
    group->group_brightness = 0;               // Set group brightness to minimum
}

// Function to update individual and group LED settings
void updateLED_groupSettings(LED_group *group, uint8_t group_state, uint8_t group_brightness, 
                            uint8_t state, uint8_t brightness, uint32_t color) {
    // Update individual LED settings
    group->single_LED.state = state;
    group->single_LED.brightness = brightness;
    group->single_LED.color = color;

    // Update group settings
    group->group_state = group_state;
    group->group_brightness = group_brightness;
}

// Function to display the current status of the LED group
void displayLEDGroupStatus(const LED_group *group) {
    printf("Individual LED State: %s\n", group->single_LED.state ? "ON" : "OFF");
    printf("Individual LED Brightness: %u\n", group->single_LED.brightness);
    printf("Individual LED Color (RGB): 0x%06X\n", group->single_LED.color);
    printf("Group State: %s\n", group->group_state ? "ALL ON" : "ALL OFF");
    printf("Group Brightness: %u\n", group->group_brightness);
}

// Main function for testing the LED control system
int main() {
    LED_group led_group;
    uint8_t group_state, state, group_brightness, brightness;
    uint32_t color;

    // Initialize the LED group with default values
    initLED_group(&led_group);
    
    // Display initial status
    printf("Initial LED Group Status:\n");
    displayLED_groupStatus(&led_group);
    
    // Get user input
    printf("\nEnter group state (1 for ALL ON, 0 for ALL OFF): ");
    scanf("%hhu", &group_state);

    printf("Enter group brightness (0 - 255): ");
    scanf("%hhu", &group_brightness);

    printf("Enter individual LED state (1 for ON, 0 for OFF): ");
    scanf("%hhu", &state);

    printf("Enter individual LED brightness (0 - 255): ");
    scanf("%hhu", &brightness);

    printf("Enter individual LED color in RGB format (hexadecimal, e.g., 0x1200FF): ");
    scanf("%x", &color);

    // Update the LED group settings with user input
    updateLED_groupSettings(&led_group, group_state, group_brightness, state, brightness, color);
    
    // Display updated status
    printf("\nUpdated LED Group Status:\n");
    displayLED_groupStatus(&led_group);

    return 0;
}
