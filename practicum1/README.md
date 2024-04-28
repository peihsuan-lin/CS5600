# Practicum I - Cache Management System

## Overview

This program is a cache management system designed to evaluate different caching strategies, Least Recently Used (LRU) and Random Replacement. It simulates the storing and retrieving of messages from a cache before accessing a SQLite database, aiming to reduce database access times and improve overall performance.

## Features

- **Message Creation**: Dynamically creates messages with specified sender, receiver, and content.
- **Cache Management**: Implements a cache system to store messages temporarily in memory.
- **Database Interaction**: Stores messages persistently in a SQLite database and retrieves them when not found in the cache.
- **Caching Strategies**: Supports LRU and Random Replacement strategies for cache management.
- **Performance Evaluation**: Evaluates cache performance based on cache hits, misses, and hit ratio.

## Structure and Components

- **`cache.c`**: Implements the caching mechanism using page replacement algorithms. Manages the in-memory storage of messages and decides which message to cache or evict based on the selected strategy.

- **`database.c`**: Handles basic database operations, including storing and retrieving messages using SQLite. This file ensures persistent storage of messages beyond the application's lifecycle.

- **`message.c`**: Responsible for creating, storing, and retrieving message objects. This includes allocating memory for new messages, populating message fields, and managing their lifecycle.

- **`types.h`**: Defines the basic data structures used throughout the program, including `Message` and `CacheManager` structs, and the `ReplacementStrategy` enum.

- **`main.c`**: Serves as the entry point for the application, integrating the cache mechanism and database operations. Evaluates the performance of the two caching algorithms by simulating message accesses and reporting cache statistics.
## How to Run

This project uses a Makefile for easy compilation and execution.
- Enter `make` in terminal to build the program. 
- Enter `./main` to start the program.