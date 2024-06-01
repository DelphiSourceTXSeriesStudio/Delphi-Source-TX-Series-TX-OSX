#include <stdio.h>

// Функция обработки программных событий
void handle_event(int event_id) {
    switch (event_id) {
        case 1:
            printf("Received event 1\n");
            break;
        case 2:
            printf("Received event 2\n");
            break;
        default:
            printf("Unknown event\n");
    }
}

int main() {
    // Симуляция генерации программных событий
    int event1 = 1;
    int event2 = 2;

    handle_event(event1);
    handle_event(event2);

    return 0;
}