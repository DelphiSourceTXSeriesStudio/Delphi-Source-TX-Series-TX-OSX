#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
void kernel_main(void)
{
   #define MEMORY_SIZE 1024

typedef struct {
    void* start_address;
    int size;
} MemoryBlock;

void* memory_start;
MemoryBlock* memory_blocks;

void init_memory() {
    memory_start = malloc(MEMORY_SIZE);
    memory_blocks = malloc(sizeof(MemoryBlock));
    memory_blocks[0].start_address = memory_start;
    memory_blocks[0].size = MEMORY_SIZE;
}

void* allocate_memory(int size) {
    for (int i = 0; memory_blocks[i].start_address != NULL; i++) {
        if (memory_blocks[i].size >= size) {
            void* allocated_memory = memory_blocks[i].start_address;
            memory_blocks[i].start_address += size;
            memory_blocks[i].size -= size;
            return allocated_memory;
        }
    }
    return NULL;
}

void free_memory(void* address, int size) {
    for (int i = 0; memory_blocks[i].start_address != NULL; i++) {
        if (memory_blocks[i].start_address == address - size) {
            memory_blocks[i].start_address -= size;
            memory_blocks[i].size += size;
            return;
        }
    }
}

void cleanup_memory() {
    free(memory_start);
    free(memory_blocks);
}

int main() {
    init_memory();

    void* allocated_memory = allocate_memory(128);
    if (allocated_memory != NULL) {
        printf("Memory allocated at address: %p\n", allocated_memory);
        free_memory(allocated_memory, 128);
        printf("Memory freed\n");
    } else {
        printf("Failed to allocate memory\n");
    }

    cleanup_memory();

    return 0;
}
#define MAX_PROCESSES 5
#define MAX_THREADS 10

typedef struct {
    int pid;
    int num_threads;
    int thread_ids[MAX_THREADS];
} Process;

Process processes[MAX_PROCESSES];
int next_pid = 1;

int create_process() {
    if (next_pid < MAX_PROCESSES) {
        processes[next_pid].pid = next_pid;
        processes[next_pid].num_threads = 0;
        printf("Process created with PID: %d\n", next_pid);
        return next_pid++;
    } else {
        printf("Max number of processes reached\n");
        return -1;
    }
}

int create_thread(int pid) {
    if (pid < MAX_PROCESSES && processes[pid].num_threads < MAX_THREADS) {
        int tid = processes[pid].num_threads;
        processes[pid].thread_ids[tid] = tid;
        processes[pid].num_threads++;
        printf("Thread created with TID: %d for Process with PID: %d\n", tid, pid);
        return tid;
    } else {
        printf("Max number of threads reached for Process with PID: %d\n", pid);
        return -1;
    }
}

void terminate_process(int pid) {
    if (pid < MAX_PROCESSES) {
        processes[pid].pid = -1;
        processes[pid].num_threads = 0;
        printf("Process with PID: %d terminated\n", pid);
    } else {
        printf("Invalid PID\n");
    }
}

int main() {
    int pid1 = create_process();
    int pid2 = create_process();

    if (pid1 != -1) {
        create_thread(pid1);
        create_thread(pid1);
    }

    if (pid2 != -1) {
        create_thread(pid2);
        create_thread(pid2);
        create_thread(pid2);
    }

    // Terminating processes
    terminate_process(1);
    terminate_process(2);

    return 0;
}
#define NUM_TASKS 3

typedef struct {
    int task_id;
    int period;
    int execution_time;
} Task;

Task tasks[NUM_TASKS];

void init_tasks() {
    tasks[0].task_id = 1;
    tasks[0].period = 5;
    tasks[0].execution_time = 2;

    tasks[1].task_id = 2;
    tasks[1].period = 10;
    tasks[1].execution_time = 4;

    tasks[2].task_id = 3;
    tasks[2].period = 20;
    tasks[2].execution_time = 3;
}

void execute_task(int task_id) {
    printf("Executing Task %d\n", task_id);
}

int main() {
    init_tasks();

    int time = 0;

    while (1) {
        for (int i = 0; i < NUM_TASKS; i++) {
            if (time % tasks[i].period == 0) {
                for (int j = 0; j < tasks[i].execution_time; j++) {
                    execute_task(tasks[i].task_id);
                    sleep(1); // Симуляция выполнения задачи
                }
            }
        }
        time++;
    }

    return 0;
}
#define MAX_USERS 5

typedef struct {
    int user_id;
    char username[20];
    char password[20];
    bool is_admin;
} User;

User users[MAX_USERS];
int next_user_id = 1;

void create_user(char* username, char* password, bool is_admin) {
    if (next_user_id < MAX_USERS) {
        users[next_user_id].user_id = next_user_id;
        strcpy(users[next_user_id].username, username);
        strcpy(users[next_user_id].password, password);
        users[next_user_id].is_admin = is_admin;
        printf("User created with ID: %d\n", next_user_id);
        next_user_id++;
    } else {
        printf("Max number of users reached\n");
    }
}

void login(char* username, char* password) {
    for (int i = 1; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("User %s logged in\n", username);
            return;
        }
    }
    printf("Login failed for user %s\n", username);
}

void grant_admin_rights(int user_id) {
    if (user_id >= 1 && user_id < MAX_USERS) {
        users[user_id].is_admin = true;
    } else {
        printf("Invalid user ID\n");
    }
}

int main() {
    create_user("admin", "adminpass", true);
    create_user("user1", "userpass", false);
    create_user("user2", "userpass", false);

    login("admin", "adminpass");
    login("user1", "password123");

    grant_admin_rights(2); // Assign admin rights to user2

    return 0;
}
typedef struct {
    int device_id;
    char device_name[20];
    void (*read_function)(int);
    void (*write_function)(int);
} IODevice;

// Функции чтения и записи для устройства 1
void read_func1(int data) {
    printf("Device 1 - Reading data: %d\n", data);
}

void write_func1(int data) {
    printf("Device 1 - Writing data: %d\n", data);
}

// Функции чтения и записи для устройства 2
void read_func2(int data) {
    printf("Device 2 - Reading data: %d\n", data);
}

void write_func2(int data) {
    printf("Device 2 - Writing data: %d\n", data);
}

int main() {
    // Инициализация устройств ввода/вывода
    IODevice device1 = {1, "Device 1", read_func1, write_func1};
    IODevice device2 = {2, "Device 2", read_func2, write_func2};

    // Пример работы с устройствами ввода/вывода
    int data1 = 123;
    device1.write_function(data1);

    int data2 = 456;
    device2.read_function(data2);

    return 0;
    // Структура для представления события клавиатуры
typedef struct {
    int key_code;
} KeyboardEvent;

// Структура для представления события мыши
typedef struct {
    int x;
    int y;
    int button_code;
} MouseEvent;

// Функция для обработки событий клавиатуры
void handle_keyboard_event(KeyboardEvent event) {
    printf("Keyboard Event - Key Code: %d\n", event.key_code);
}

// Функция для обработки событий мыши
void handle_mouse_event(MouseEvent event) {
    printf("Mouse Event - X: %d, Y: %d, Button Code: %d\n", event.x, event.y, event.button_code);
}

int main() {
    // Пример получения событий от клавиатуры и мыши и их обработки
    KeyboardEvent keyboard_event = {10};
    handle_keyboard_event(keyboard_event);

    MouseEvent mouse_event = {100, 200, 1};
    handle_mouse_event(mouse_event);

    return 0;

}
void main() {
    int x = 10;
    printf("Value of x: %d\n", x);
}