#include "database.h"

sqlite3_stmt *insert_stmt;
sqlite3_stmt *select_stmt;
sqlite3_stmt *update_stmt;

// Prepares SQL statements for inserting and selecting messages from the database.
int prepare_statements(sqlite3 *db) {
    const char *insert_sql = "INSERT INTO Messages (timeSent, sender, receiver, content, flag) VALUES (?, ?, ?, ?, ?)";
    const char *select_sql = "SELECT * FROM Messages WHERE id = ?";
    int rc;

    rc = sqlite3_prepare_v2(db, insert_sql, -1, &insert_stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare insert statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = sqlite3_prepare_v2(db, select_sql, -1, &select_stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare select statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    return 0;
}

// Cleans up the prepared statements.
void finalize_statements() {
    sqlite3_finalize(insert_stmt);
    sqlite3_finalize(select_stmt);
    sqlite3_finalize(update_stmt);
}

// Inserts a message into the database and returns the newly created message's ID.
int insert(sqlite3 *db, Message *msg) {
    int rc;
    sqlite3_bind_int64(insert_stmt, 1, (sqlite3_int64) msg->timeSent);
    sqlite3_bind_text(insert_stmt, 2, msg->sender, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 3, msg->receiver, -1, SQLITE_STATIC);
    sqlite3_bind_text(insert_stmt, 4, msg->content, -1, SQLITE_STATIC);
    sqlite3_bind_int(insert_stmt, 5, msg->flag);

    rc = sqlite3_step(insert_stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute insert: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    int id = sqlite3_last_insert_rowid(db);
    sqlite3_reset(insert_stmt);
    return id;
}

// Retrieves a message by ID from the database.
Message *select(sqlite3 *db, int id) {
    int rc;
    Message *msg = malloc(sizeof(Message));

    rc = sqlite3_bind_int(select_stmt, 1, id);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameter: %s\n", sqlite3_errmsg(db));
        free(msg);
        return NULL;
    }
    if ((rc = sqlite3_step(select_stmt)) == SQLITE_ROW) {
        msg = malloc(sizeof(Message));
        if (msg) {
            msg->id = id;
            msg->timeSent = sqlite3_column_int64(select_stmt, 1);
            strncpy(msg->sender, (char *) sqlite3_column_text(select_stmt, 2), sizeof(msg->sender));
            strncpy(msg->receiver, (char *) sqlite3_column_text(select_stmt, 3), sizeof(msg->receiver));
            strncpy(msg->content, (char *) sqlite3_column_text(select_stmt, 4), sizeof(msg->content));
            msg->flag = sqlite3_column_int(select_stmt, 5);
        }
    }
    sqlite3_reset(select_stmt);
    return msg;
}

// Initializes the database table for messages, creating it if it doesn't exist.
int init_tb(sqlite3 *db, char *errMsg) {
    const char *drop_table_sql = "DROP TABLE IF EXISTS Messages;";
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS Messages (id INTEGER PRIMARY KEY, timeSent INT, sender TEXT, receiver TEXT, content TEXT, flag INT);";
    sqlite3_exec(db, drop_table_sql, 0, 0, &errMsg);
    int rc = sqlite3_exec(db, create_table_sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return -1;
    }
    return 0;
}

// Clears all messages from the database.
void clear_db(sqlite3 *db) {
    char *errMsg = NULL;
    const char *sql = "DELETE FROM Messages;";
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }
}
