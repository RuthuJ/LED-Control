#include <stdio.h>
#include <stdint.h>

// Structure to represent individual LED settings
typedef struct {
    uint8_t state;         // 1 for ON, 0 for OFF
    uint8_t brightness;    // Brightness level (0-255)
    uint32_t color;        // RGB color value (24-bit format)
} LEDSettings;

// Structure to represent a group of LEDs
typedef struct {
    LEDSettings singleLED; // Individual LED settings
    uint8_t groupState;    // Collective state of the group (1 for ON, 0 for OFF)
    uint8_t groupBrightness; // Collective brightness adjustment (0-255)
} LEDGroup;

// Function to initialize the LED group with default values
void initLEDGroup(LEDGroup *group) {
    group->singleLED.state = 0;            // Turn off the individual LED
    group->singleLED.brightness = 0;       // Set brightness to minimum
    group->singleLED.color = 0x000000;     // Set color to black (RGB: 0x000000)
    group->groupState = 0;                 // Turn off the group
    group->groupBrightness = 0;            // Set group brightness to minimum
}

// Function to update the LED group settings
void updateLEDGroupSettings(LEDGroup *group, uint8_t groupState, uint8_t groupBrightness, uint8_t state, uint8_t brightness, uint32_t color) {
    // Update individual LED settings
    group->singleLED.state = state;
    group->singleLED.brightness = brightness;
    group->singleLED.color = color;
    
    // Update group settings
    group->groupState = groupState;
    group->groupBrightness = groupBrightness;
}

// Function to display the current LED group status
void displayLEDGroupStatus(const LEDGroup *group) {
    printf("Individual LED Status:\n");
    printf("State: %s\n", group->singleLED.state ? "ON" : "OFF");
    printf("Brightness: %u\n", group->singleLED.brightness);
    printf("Color (RGB): #%06X\n", group->singleLED.color);
    
    printf("\nGroup LED Status:\n");
    printf("Group State: %s\n", group->groupState ? "ON" : "OFF");
    printf("Group Brightness: %u\n", group->groupBrightness);
}

int main() {
    LEDGroup ledGroup;

    // Initialize the LED group
    initLEDGroup(&ledGroup);

    // Display the initial status
    printf("Initial LED Group Status:\n");
    displayLEDGroupStatus(&ledGroup);

    // Update the LED group with new settings
    updateLEDGroupSettings(&ledGroup, 1, 150, 1, 200, 0xFF5733);

    // Display the updated status
    printf("\nUpdated LED Group Status:\n");
    displayLEDGroupStatus(&ledGroup);

    return 0;
}
