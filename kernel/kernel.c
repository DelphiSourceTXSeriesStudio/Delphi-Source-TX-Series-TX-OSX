#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <pthread.h>
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("/tmp", 'A');
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.msg_type = 1;
    printf("Enter message: ");
    fgets(message.msg_text, 100, stdin);

    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Message sent: %s\n", message.msg_text);

    return 0;
}
// Структура для управления памятью
struct MemoryManager {
    int memory;
};

// Структура для задачи
struct Task {
    int pid;
    char name[256];
};
void allocateMemory(struct MemoryManager *mm, int size) {
    mm->memory -= size;
}
void scheduleTask(struct Task *tasks, int numTasks) {
    for (int i = 0; i < numTasks; i++) {
        printf("Scheduled task %d: %s\n", tasks[i].pid, tasks[i].name);
    }
}
void *thread_func(void *arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d is executing\n", thread_id);
    return NULL;
}
struct File {
    char name[256];
    char data[1024];
};

void createFile(struct File *file, char *name) {
    strcpy(file->name, name);
    file->data[0] = '\0';
    printf("Created file: %s\n", name);
}

void writeFile(struct File *file, char *data) {
    strcpy(file->data, data);
    printf("Data written to file %s: %s\n", file->name, data);
}

int main() 
    struct File myFile;
    createFile(&myFile, "example.txt");
    writeFile(&myFile, "Hello, World!");

    return 0;
int main() 
    pthread_t threads[3];
    int thread_ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
int main() 
    
    struct MemoryManager mm = { 1024 }; // Выделение памяти 1024 байта
    allocateMemory(&mm, 256); // Выделение 256 байт памяти

    struct Task tasks[] = { {1, "Task 1"}, {2, "Task 2"}, {3, "Task 3"} };
    scheduleTask(tasks, 3); // Планирование задач

    return 0;
    