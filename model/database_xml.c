/**
 * @author Mateus Coutinho
 * Work in progress.
 */

#include "database_xml.h"

static int xml_open(Table table) {
    return 0;
}

static int xml_close(Table table) {
    return 0;
}

static int xml_rewind(Table table) {
    return 0;
}

static int xml_next(Table table, void *ptr) {
    return 0;
}

static int xml_delete(Table table) {
    return 0;
}

static int xml_update(Table table, const void *ptr) {
    return 0;
}

static int xml_insert(Table table, void *ptr) {
    return 0;
}

Database *XML_DATABASE = &(Database) {
        .open   = xml_open,
        .close  = xml_close,
        .rewind = xml_rewind,
        .next   = xml_next,
        .delete = xml_delete,
        .update = xml_update,
        .insert = xml_insert,
};