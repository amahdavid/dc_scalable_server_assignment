#include <arpa/inet.h>
#include <dc_c/dc_ctype.h>
#include <dc_c/dc_signal.h>
#include <dc_c/dc_stdio.h>
#include <dc_c/dc_stdlib.h>
#include <dc_c/dc_string.h>
#include <dc_env/env.h>
#include <dc_error/error.h>
#include <dc_posix/dc_unistd.h>
#include <dc_posix/sys/dc_select.h>
#include <dc_posix/sys/dc_socket.h>
#include <netinet/in.h>
#include <signal.h>


#define SERVER_PORT 4981
#define MAX_PENDING 5
#define MAX_CLIENTS 10
#define BUF_SIZE 256


static void ctrl_c_handler(int signum);
static int setup_server(struct dc_env *env, struct dc_error *err);
static int run_server(struct dc_env *env, struct dc_error *err, int listener, int *clients, fd_set *read_fds, int *max_fd);
static int wait_for_data(struct dc_env *env, struct dc_error *err, int listener, const int *clients, fd_set *read_fds, const int *max_fd);
static void handle_new_connections(struct dc_env *env, struct dc_error *err, int listener, int *clients, fd_set *read_fds, int *max_fd);
static void handle_client_data(struct dc_env *env, struct dc_error *err, int *clients, fd_set* read_fds);


static volatile sig_atomic_t done = false;   // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)


int main(void)
{
    struct dc_env *env;
    struct dc_error *err;
    int listener;
    fd_set read_fds;
    int max_fd;
    // all the file descriptor we are interested in
    int client_sockets[MAX_CLIENTS];

    // this shows if a function call failed
    err = dc_error_create(true);
    // this helps to show the functions called in main
    //env = dc_env_create(err, true, dc_env_default_tracer);
    listener = setup_server(env, err);

    if(listener < 0)
    {
        return EXIT_FAILURE;
    }

    max_fd = listener;
    dc_memset(env, client_sockets, 0, sizeof(client_sockets));
    dc_signal(env, err, SIGINT, ctrl_c_handler);
    run_server(env, err, listener, client_sockets, &read_fds, &max_fd);
    dc_close(env, err, listener);

    return EXIT_SUCCESS;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static void ctrl_c_handler(int signum)
{
    done = true;
}
#pragma GCC diagnostic pop

/**
 * this function sets up a server using the socket API
 * */
static int setup_server(struct dc_env *env, struct dc_error *err)
{
    int listener;
    int optval;
    struct sockaddr_in server_addr;

    DC_TRACE(env);
    /*creates a socket using the dc_socket*/
    listener = dc_socket(env, err, AF_INET, SOCK_STREAM, 0);

    if (listener < 0)
    {
        dc_perror(env, "socket");
        return -1;
    }

    optval = 1;
    /*sets the SO_REUSEADDR option to allow for reuse of the socket address*/
    dc_setsockopt(env, err, listener, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    /*sets up the server address using the sockaddr_in struct*/
    dc_memset(env, &server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    /*it binds the socket using dc_bind*/
    if(dc_bind(env, err, listener, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)
    {
        dc_perror(env, "bind");
        dc_close(env, err, listener);
        return -1;
    }

    /*it listens for incoming connections here with a max number of MAX_PENDING using dc_listen*/
    if(dc_listen(env, err, listener, MAX_PENDING) < 0)
    {
        dc_perror(env, "listen");
        dc_close(env, err, listener);
        return -1;
    }

    return listener;
}

/**
 * this code is the main loop of the server program, it runs until "done" flag is set
 * inside the loop it waits for data using the wait_for_data() function
 * if the select() function returns any data, the handle_new_connection() function is called to handle new
   incoming connections and the client data
 * */
static int run_server(struct dc_env *env, struct dc_error *err, int listener, int *clients, fd_set *read_fds, int *max_fd)
{
    DC_TRACE(env);

    /*main loop that runs until the flag is set*/
    while(!(done))
    {
        int ready;

        /*waits for data*/
        ready = wait_for_data(env, err, listener, clients, read_fds, max_fd);

        /*error handling*/
        if(ready < 0)
        {
            dc_perror(env, "select");
            continue;
        }

        /*handles new connection*/
        handle_new_connections(env, err, listener, clients, read_fds, max_fd);
        /*handles clients data*/
        handle_client_data(env, err, clients, read_fds);
    }

    return EXIT_SUCCESS;
}

/**
 * this code uses the select function to wait for data from either the listener socket or one of the connected clients
 * it first clears the file descriptor sets read_fds using FD_ZERO
 * it then sets the listener socket and all connected clients in the read_fds set using FD_SET
 * the select() function is then called with the highest file descriptor value plus 1 as the last parameter
 * it returns the number of file descriptors that file descriptors that have data ready to read
 * the final result of this code is a file descriptor set that keeps track of which sockets have data available to be read
 * */
static int wait_for_data(struct dc_env *env, struct dc_error *err, int listener, const int *clients, fd_set *read_fds, const int *max_fd)
{
    DC_TRACE(env);
    FD_ZERO(read_fds);
    FD_SET(listener, read_fds);

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i] > 0)
        {
            FD_SET(clients[i], read_fds);
        }
    }

    return dc_select(env, err, *max_fd + 1, read_fds, NULL, NULL, NULL);
}

/**
 * this function handles new incoming connections from clients to the server
 * if the listener socket has new data to be read, it means that a new client has connected to the server
 * the function then accepts the connection using the dc_accept() and stores the clients fd in the clients array
 * it also updates the value of max_fd if the new clients file descriptor is larger than the current value of max_fd
 * the function also prints a message to the console indicating a new connection has been established
 * */
static void handle_new_connections(struct dc_env *env, struct dc_error *err, int listener, int *clients, fd_set *read_fds, int *max_fd)
{
    DC_TRACE(env);

    if (FD_ISSET(listener, read_fds))
    {
        struct sockaddr_in client_addr;
        socklen_t client_len;
        int client_fd;

        dc_memset(env, &client_addr, 0, sizeof(client_addr));
        client_len = sizeof(client_addr);
        client_fd = dc_accept(env, err, listener, (struct sockaddr*) &client_addr, &client_len);

        if(client_fd < 0)
        {
            dc_perror(env, "accept");
            return;
        }

        printf("New connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));    // NOLINT(concurrency-mt-unsafe)

        for(int i = 0; i < MAX_CLIENTS; i++)
        {
            if(clients[i] == 0)
            {
                clients[i] = client_fd;
                break;
            }
        }

        if (client_fd > *max_fd)
        {
            *max_fd = client_fd;
        }
    }
}

static void handle_client_data(struct dc_env *env, struct dc_error *err, int *clients, fd_set* read_fds)
{
    char buffer[BUF_SIZE];

    DC_TRACE(env);

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i] > 0 && FD_ISSET(clients[i], read_fds))
        {
            ssize_t bytes_read;

            bytes_read = dc_read(env, err, clients[i], buffer, BUF_SIZE);

            if(bytes_read <= 0)
            {
                printf("Client disconnected\n");
                dc_close(env, err, clients[i]);
                clients[i] = 0;
                continue;
            }

            // chat gpt initialized this to 1
            int word_count = 0;

            printf("Read from client\n");
            dc_write(env, err, STDOUT_FILENO, buffer, bytes_read);

            for(int j = 0; j < bytes_read; j++)
            {
                //buffer[j] = (char)dc_toupper(env, buffer[j]);

                if (buffer[j] == ' ' || buffer[j] == '\n' || buffer[j] == '\t')
                    word_count++;
            }

            printf("Writing to client\n");
            printf("word count: %d\n", word_count);
            char count_buffer[BUF_SIZE];
            snprintf(count_buffer, BUF_SIZE, "%d", word_count);
            dc_write(env, err, STDOUT_FILENO, buffer, bytes_read);
            dc_write(env, err, clients[i], count_buffer, dc_strlen(env, count_buffer));
            //dc_write(env, err, clients[i], buffer, bytes_read);
            dc_write(env, err, clients[i], &word_count, sizeof(word_count));
        }
    }
}
