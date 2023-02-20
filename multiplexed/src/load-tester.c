#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <dc_posix/dc_unistd.h>

#define BUFFER_SIZE 1024
#define NUM_THREADS 10

void *test_thread(void *arg);

//global variables
char *server_ip;
int server_port;
char *data_file;
int test_duration;
time_t start_time;

int main(int argc, char *argv[]) {
    // Check if all required arguments are provided
    if (argc < 5) {
        printf("Usage: %s <server IP> <server port> <data file> <test duration>\n", argv[0]);
        return -1;
    }

    // Parse command line arguments
    server_ip = argv[1];
    server_port = atoi(argv[2]);
    data_file = argv[3];
    test_duration = atoi(argv[4]);

    //checks if server port is valid
    if (server_port < 1024 || server_port > 65535){
        printf("Error: invalid server port number\n");
        return -1;
    }

    // Open the data file
    FILE *fp = fopen(data_file, "rb");
    if (fp == NULL) {
        perror("Unable to open data file");
        return -1;
    }

    // Read the contents of the data file into a buffer
    char buffer[BUFFER_SIZE];
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, fp);
    fclose(fp);

    // Create an infinite loop that runs for the test duration
    start_time = time(NULL);
    while (difftime(time(NULL), start_time) < test_duration) {
        // Create a thread to send data to the server

        // chatgpt suggest we create a fixed number of threads to the server
        /*pthread_t threads[NUM_THREADS];
        for (int i = 0; i < NUM_THREADS; ++i) {
            if (pthread_create(&threads[i], NULL, test_thread, (void *)fp) != 0){
                perror("Unable to create test thread");
                fclose(fp);
                return -1;
            }
        }
        // wait for all threads to finish
        for (int i = 0; i < NUM_THREADS; ++i) {
            pthread_join(threads[i], NULL);
        }

        fclose(fp);*/

        pthread_t thread;
        if (pthread_create(&thread, NULL, test_thread, (void *) buffer) != 0) {
            perror("Unable to create test thread");
            return -1;
        }

        pthread_join(thread, NULL);
    }
    return 0;
}

void *test_thread(void *arg) {
    // Get the data buffer from the argument
    char *data = (char *) arg;

    // Open a socket and connect to the server
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Unable to create socket");
        pthread_exit(NULL);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Unable to convert server IP");
        close(sockfd);
        pthread_exit(NULL);
    }

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Unable to connect to server");
        close(sockfd);
        pthread_exit(NULL);
    }

    // Send the data to the server
    ssize_t bytes_sent = send(sockfd, data, strlen(data), 0);
    if (bytes_sent < 0) {
        perror("Unable to send data to server");
        close(sockfd);
        pthread_exit(NULL);
    }

    // Receive the response from the server
    char response[BUFFER_SIZE];
    ssize_t bytes_recv = recv(sockfd, response, BUFFER_SIZE, 0);
    if (bytes_recv < 0) {
        perror("Unable to receive data from server");
        close(sockfd);
        pthread_exit(NULL);
    }

    close(sockfd);

    // Log the time taken to send and receive data to a CSV file
    FILE *fp = fopen("results.csv", "a");
    if (fp == NULL) {
        perror("Unable to open results file");
        pthread_exit(NULL);
    }

    time_t current_time = time(NULL);
    double time_taken = difftime(current_time, start_time);
    fprintf(fp, "%.0f,%ld\n", time_taken, bytes_recv);

    fclose(fp);
    pthread_exit(NULL);
}
