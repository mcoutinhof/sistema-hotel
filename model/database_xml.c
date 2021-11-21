/**
 * Work in progress.
 */

#include "database_xml.h"
#include "database_local.h"

static int xml_open(const Table table) {
    return 0;
}

static int xml_close(const Table table) {
    return 0;
}

static int xml_rewind(const Table table) {
    return 0;
}

static int xml_next(const Table table, void *ptr) {
    return 0;
}

static int xml_delete(const Table table) {
    return 0;
}

static int xml_update(const Table table, const void *ptr) {
    return 0;
}

static int xml_insert(const Table table, const void *ptr) {
    return 0;
}

const Database *XML_DATABASE = &(Database) {
        .open = xml_open,
        .close = xml_close,
        .rewind = xml_rewind,
        .next = xml_next,
        .delete = xml_delete,
        .update = xml_update,
        .insert = xml_insert,
};