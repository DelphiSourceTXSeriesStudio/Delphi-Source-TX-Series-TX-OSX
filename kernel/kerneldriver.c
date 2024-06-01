// Драйвер для управления аппаратным обеспечением
#include <stdio.h>

void control_hardware(int action) {
    if (action == 1) {
        printf("Turning on hardware\n");
    } else if (action == 0) {
        printf("Turning off hardware\n");
    } else {
        printf("Invalid action\n");
    }
}

int main() {
    // Симуляция управления аппаратным обеспечением
    control_hardware(1); // Включение оборудования
    control_hardware(0); // Выключение оборудования

    return 0;
}