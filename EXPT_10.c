#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

// Structure for message
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = 1234;

    // Create message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;

    if (fork() == 0) {
        // Child Process (Receiver)
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Child received message: %s\n", message.msg_text);
    } else {
        // Parent Process (Sender)
        message.msg_type = 1;
        printf("Parent sending message...\n");
        strcpy(message.msg_text, "Hello from Parent!");
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Message sent.\n");
    }

    return 0;
}