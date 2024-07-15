# Practicum II: Server-Based File Storage System

## Overview
This project implements a server-based file storage system that allows programs to manage files over a TCP connection. This practicum focuses on creating a multi-threaded client/server file system that is fault tolerant. The functionality includes reading, writing, creating, and deleting files and folders on a remote server via TCP sockets.


## Features
- **Write File**: Send a file from the client to the server.
- **Read File**: Fetch a file from the server to a local machine.
- **Delete File/Folder**: Remove files or folders in the remote file system.
- **Multi-threading**: Handle multiple clients simultaneously without data corruption.
- **File Permissions**: Set file permissions (read-only or read-write) upon creation.
- **File Encryption**: Optional encryption and decryption of files during transfer.

## Commands
```bash
# Write a file to the server
% rfs WRITE [local-file-path] [remote-file-path]

# Retrieve a file from the server
% rfs GET [remote-file-path] [local-file-path]

# Delete a file or folder on the server
% rfs RM [remote-file-path]

# Check file permissions
% rfs LS [file-path]
```

## Installation
1. Clone the repository:
   ```bash
   git clone [repository-url]
   ```
2. Compile the server and client programs:
   ```bash
   gcc server.c -o server -lpthread
   gcc client.c -o client
   ```

## Usage
Start the server:
```bash
./server &
```
Run client commands as shown in the commands section.